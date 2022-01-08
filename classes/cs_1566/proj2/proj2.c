/*
 * proj2.c
 *
 * PLY Renderer
 * 
 * Shane Riley
 * 
 */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

#include "../mylib/initShader.h"
#include "../mylib/linalg.h"

#define BUFFER_OFFSET(offset) ((GLvoid *)(offset))

// double PI = 3.141592654;
int num_vertices;
GLfloat zoom = 1.02;
GLfloat ZOOM_START = 0.1;
GLfloat SCALING_FACTOR = 1.0;
char PLY_FILENAME[100];

GLfloat R1 = 10.0;
int VIEW_X = 512;
int VIEW_Y = 512;

int N1 = 20;

GLuint ctm_location;

GLuint texture_location;
GLuint color_location;

GLint is_color;

mat4 ctm = {{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}};

vec4 down_loc;
int down_success;

/*
 * Function: get_sphere_size
 * -------------------
 * Gets array of vertices to define a Sphere
 *
 * int n1: Number of sudivisions 1
 *
 * Returns: Size
 */

int get_sphere_size(int n1)
{
    return (n1 * (n1 / 2) * 6) + 6 * n1;
}

/*
 * Function: get_sphere_vertices
 * -------------------
 * Gets array of vertices to define a sphere
 *
 * int n1: Number of sudivisions 1
 *
 * int r1: large radius
 * 
 * Returns: vec4 vertices
 */

void get_sphere_vertices(int n1, int r1, vec4 *vertices)
{
    int v = 0;
    int i, j;
    GLfloat theta, phi, dtheta, dphi;
    dtheta = 2 * PI / n1;
    dphi = dtheta;

    // Build north pole and south pole
    phi = 0;
    for (i = 0; i < n1; i++)
    {
        theta = i * dtheta;
        vertices[v++] = (vec4){0.0, r1, 0.0, 1.0};
        vertices[v++] = (vec4){r1 * cos(theta + dtheta) * sin(phi + dphi),
                               r1 * cos(phi + dphi),
                               r1 * sin(theta + dtheta) * sin(phi + dphi),
                               1.0};
        vertices[v++] = (vec4){r1 * cos(theta) * sin(phi + dphi),
                               r1 * cos(phi + dphi),
                               r1 * sin(theta) * sin(phi + dphi),
                               1.0};
    }
    phi = PI;
    for (i = 0; i < n1; i++)
    {
        theta = i * dtheta;
        vertices[v++] = (vec4){0.0, -r1, 0.0, 1.0};
        vertices[v++] = (vec4){r1 * cos(theta) * sin(phi - dphi),
                               r1 * cos(phi - dphi),
                               r1 * sin(theta) * sin(phi - dphi),
                               1.0};
        vertices[v++] = (vec4){r1 * cos(theta + dtheta) * sin(phi - dphi),
                               r1 * cos(phi - dphi),
                               r1 * sin(theta + dtheta) * sin(phi - dphi),
                               1.0};
    }

    // Make the bulk
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n1 / 2; j++)
        {
            theta = i * dtheta;
            phi = j * dphi;

            vertices[v++] = (vec4){r1 * cos(theta) * sin(phi),
                                   r1 * cos(phi),
                                   r1 * sin(theta) * sin(phi),
                                   1.0};
            vertices[v++] = (vec4){r1 * cos(theta + dtheta) * sin(phi),
                                   r1 * cos(phi),
                                   r1 * sin(theta + dtheta) * sin(phi),
                                   1.0};
            vertices[v++] = (vec4){r1 * cos(theta) * sin(phi + dphi),
                                   r1 * cos(phi + dphi),
                                   r1 * sin(theta) * sin(phi + dphi),
                                   1.0};
            vertices[v++] = (vec4){r1 * cos(theta + dtheta) * sin(phi),
                                   r1 * cos(phi),
                                   r1 * sin(theta + dtheta) * sin(phi),
                                   1.0};
            vertices[v++] = (vec4){r1 * cos(theta + dtheta) * sin(phi + dphi),
                                   r1 * cos(phi + dphi),
                                   r1 * sin(theta + dtheta) * sin(phi + dphi),
                                   1.0};
            vertices[v++] = (vec4){r1 * cos(theta) * sin(phi + dphi),
                                   r1 * cos(phi + dphi),
                                   r1 * sin(theta) * sin(phi + dphi),
                                   1.0};
        }
    }
    // printf("%d\n", v);
}

/*
 * Function: get_sphere_tex
 * -------------------
 * Gets array of tex to define a sphere
 *
 * vec4 *vertices: Pointer to filled-out vertices
 * 
 * int n_vert: Number of vertices
 * 
 * float r1: radius
 * 
 * Returns: vec2 vertices
 */

void get_sphere_tex(vec4 *vertices, int n_vertices, float r1, vec2 *tex)
{
    // Map based on x and y
    float max_u = 0.5, max_v = 0.5;

    // Mirror across xy
    for (int v = 0; v < n_vertices; v++)
    {
        tex[v].x = (vertices[v].x / r1) * max_u / 2 + max_u / 2;
        tex[v].y = (vertices[v].y / r1) * max_v / 2 + max_v / 2;
    }
}

/*
 * Function: get_file_size
 * -------------------
 * Gets number of vertices from file
 *
 * char *filename: path to file
 *
 * Returns: num_vertices
 */

int get_file_size(char *filename)
{
    int size;
    FILE *file;
    if ((file = fopen(filename, "r")) != NULL)
    {

        fscanf(file, "%d\n", &size);

        fclose(file);
    }
    else
    {
        printf("File not found");
        size = -1;
    }
    return size;
}

/*
 * Function: get_colors
 * -------------------
 * Gets array of colors
 * 
 * int size: size of desired color array
 * 
 * vec4* colors: the pointer to the color array
 * 
 * Returns: None
 */
void get_colors(int size, vec4 *colors)
{

    // Triangles, n should be divisible by 3
    GLfloat color_1, color_2, color_3;

    int i, j;
    for (i = 0; i < size / 3; i++)
    {

        // Get random color
        color_1 = (((GLfloat)rand()) / RAND_MAX);
        color_2 = (((GLfloat)rand()) / RAND_MAX);
        color_3 = (((GLfloat)rand()) / RAND_MAX);

        // Apply color to triangle
        for (j = 0; j < 3; j++)
        {
            (colors)[3 * i + j].x = color_1;
            (colors)[3 * i + j].y = color_2;
            (colors)[3 * i + j].z = color_3;
            (colors)[3 * i + j].w = 1.0;
        }
    }
}

void init(void)
{
    GLuint n_bytes;
    GLuint n_tex_bytes;
    int choice = 0;
    vec4 *vertices, *colors;
    vec2 *tex;
    int width, height;
    GLubyte *my_texels;
    printf("init");

    while (choice < 1 || choice > 2)
    {
        printf("Which to display?\n1: Sphere\n2: File\n> ");
        scanf("%d", &choice);
    }

    if (choice == 1)
    {
        // Sphere
        num_vertices = get_sphere_size(N1);

        n_bytes = num_vertices * sizeof(vec4);
        n_tex_bytes = num_vertices * sizeof(vec2);

        vertices = (vec4 *)malloc(n_bytes);
        colors = (vec4 *)malloc(n_bytes);
        tex = (vec2 *)malloc(n_tex_bytes);

        get_sphere_vertices(N1, R1, vertices);
        get_colors(num_vertices, colors);
        get_sphere_tex(vertices, num_vertices, R1, tex);
        is_color = 0;

        width = 320;
        height = 320;
        my_texels = malloc(width * height * 3 * sizeof(GLubyte));

        FILE *fp = fopen("texture01.raw", "r");
        fread(my_texels, width * height * 3, 1, fp);
        fclose(fp);
    }
    else
    {
        printf("Enter a filename: ");
        char filename[40];
        scanf("%s", filename);

        // File
        FILE *f;
        int n_vertex;
        int n_tex_vertex;
        int n_face;
        int n_tex_face;

        char *line = NULL;
        size_t line_buf_size = 0;
        ssize_t line_size;
        int is_binary = 0;
        is_color = 0;
        char file_to_open[50];

        strcpy(file_to_open, filename);
        strcat(file_to_open, ".ply");
        f = fopen(file_to_open, "r");
        while (!is_binary)
        {
            // Plaintext

            // Get line
            line_size = getline(&line, &line_buf_size, f);
            if (strstr(line, "element vertex") != NULL)
            {
                // Get element vertex
                sscanf(line, "element vertex %d\n", &n_vertex);
            }
            if (strstr(line, "element face") != NULL)
            {
                // Get element face
                sscanf(line, "element face %d\n", &n_face);
            }
            if (strstr(line, "element multi_texture_vertex") != NULL)
            {
                // Get element multi_texture_vertex
                sscanf(line, "element multi_texture_vertex %d\n", &n_tex_vertex);
            }
            if (strstr(line, "element multi_texture_face") != NULL)
            {
                // Get element multi_texture_face
                sscanf(line, "element multi_texture_face %d\n", &n_tex_face);
            }
            if (strstr(line, "end_header") != NULL)
            {
                is_binary = 1;
            }
            if (strstr(line, "red") != NULL)
            {
                is_color = 1;
            }
        }

        num_vertices = 3 * n_face;
        n_bytes = num_vertices * sizeof(vec4);
        n_tex_bytes = num_vertices * sizeof(vec2);
        vertices = (vec4 *)malloc(num_vertices * sizeof(vec4));
        colors = (vec4 *)malloc(num_vertices * sizeof(vec4));
        tex = malloc(3 * n_tex_face * sizeof(vec2));
        vec2 *f_tex = (vec2 *)malloc(n_tex_vertex * sizeof(vec2));
        vec4 *f_v = (vec4 *)malloc(n_vertex * sizeof(vec4));
        vec4 *f_c = (vec4 *)malloc(n_vertex * sizeof(vec4));
        u_char c[3];

        // Binary

        // Read vertices
        int v;
        for (v = 0; v < n_vertex; v++)
        {
            // Load 12 bytes
            fread(f_v + v, 12, 1, f);
            f_v[v].w = 1.0;

            if (is_color)
            {
                fread(c, 3, 1, f);
                f_c[v].x = (float)c[0] / 255.0;
                f_c[v].y = (float)c[1] / 255.0;
                f_c[v].z = (float)c[2] / 255.0;
                f_c[v].w = 1.0;
            }
        }

        // Build faces

        int loc[3];
        char temp[5];
        for (v = 0; v < n_face; v++)
        {
            // Skip one byte
            fread(temp, 1, 1, f);
            assert(temp[0] == '\003');

            // Load 12 bytes
            fread(loc, 12, 1, f);

            // Place vertices
            vertices[3 * v + 0] = f_v[loc[0]];
            vertices[3 * v + 1] = f_v[loc[1]];
            vertices[3 * v + 2] = f_v[loc[2]];

            if (is_color)
            {
                colors[3 * v + 0] = f_c[loc[0]];
                colors[3 * v + 1] = f_c[loc[1]];
                colors[3 * v + 2] = f_c[loc[2]];
            }
        }
        free(f_v);

        if (!is_color)
        {
            // Get tex vertices
            for (v = 0; v < n_tex_vertex; v++)
            {
                // Skip one byte
                fread(temp, 1, 1, f);
                // Load 8 bytes
                fread(f_tex + v, 8, 1, f);
            }

            // Get texture maps

            // Skip five bytes
            fread(temp, 1, 5, f);
            for (v = 0; v < n_tex_face; v++)
            {

                // Skip one byte
                fread(temp, 1, 1, f);

                // Read 12 bytes
                fread(loc, 4, 2, f);

                // Place vertices
                tex[3 * v + 0] = f_tex[loc[0]];
                tex[3 * v + 1] = f_tex[loc[1]];
                tex[3 * v + 2] = f_tex[loc[2]];
            }
            fclose(f);
            get_colors(num_vertices, colors);
            width = 1024;
            height = 1024;
            strcpy(file_to_open, filename);
            strcat(file_to_open, ".data");
            my_texels = malloc(width * height * 3 * sizeof(GLubyte));
            FILE *fp = fopen(file_to_open, "r");
            fread(my_texels, width * height * 3, 1, fp);
            fclose(fp);
        }
    }

    // Get colors

    // Starting zoom
    ctm = prod_mat_mat(ctm, scale(ZOOM_START, ZOOM_START, ZOOM_START));

    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    if (!is_color)
    {
        GLuint mytex[1];
        glGenTextures(1, mytex);
        glBindTexture(GL_TEXTURE_2D, mytex[0]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, my_texels);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        int param;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * n_bytes + n_tex_bytes, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, n_bytes, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, n_bytes, n_bytes, colors);
    if (!is_color)
    {
        glBufferSubData(GL_ARRAY_BUFFER, 2 * n_bytes, n_tex_bytes, tex);
    }

    GLint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0 + n_bytes);

    GLint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0 + (n_bytes + n_bytes));

    texture_location = glGetUniformLocation(program, "texture");
    ctm_location = glGetUniformLocation(program, "ctm");
    color_location = glGetUniformLocation(program, "is_color");
    glUniform1i(color_location, is_color);
    glUniform1i(texture_location, 0);

    printf("texture_location: %i\n", texture_location);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1, 0);

    free(vertices);
    free(colors);
    if (!is_color)
    {
        free(tex);
    }
}

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON)
    {
        // Rotation
        if (state == GLUT_DOWN)
        {
            // printf("Click down @ %d, %d\n", x, y);
            down_success = get_ball(x, y, VIEW_X, VIEW_Y, (vec4 *)&down_loc); // , &down_loc
            if (down_success)
            {
                // printf("%f,%f,%f,%f\n", down_loc.x, down_loc.y, down_loc.z, down_loc.w);
            }
        }
        else if (state == GLUT_UP)
        {
            // printf("Click up @ %d, %d\n", x, y);
            vec4 up_loc;
            if (down_success && get_ball(x, y, VIEW_X, VIEW_Y, (vec4 *)&up_loc))
            { //, &up_loc
                if (!equals_vec(down_loc, up_loc))
                {
                    vec4 cross;
                    mat4 rz;
                    vec4 origin = {0.0, 0.0, 0.0, 1.0};
                    cross = normalize(cross_vec_vec(up_loc, down_loc));
                    GLfloat theta = (magnitude(down_loc) * magnitude(up_loc)) / dot_vec_vec(down_loc, up_loc);
                    // printf("%f,%f,%f,%f,%f\n", cross.x, cross.y, cross.z, cross.w, theta);
                    rz = rotate_v(cross, origin, theta * SCALING_FACTOR);
                    ctm = prod_mat_mat(rz, ctm);
                }
            }
        }
    }
    else if (button == 3)
    {
        // Scroll up, zoom out
        GLfloat z = zoom;
        ctm = prod_mat_mat(scale(z, z, z), ctm);
    }
    else if (button == 4)
    {
        // Scroll down, zoom in
        GLfloat z = 1.0 / zoom;
        ctm = prod_mat_mat(ctm, scale(z, z, z));
    }
    // Rerender
    glutPostRedisplay();
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *)&ctm);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if (key == 'q')
        glutLeaveMainLoop();

    //glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, VIEW_X, VIEW_Y);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(VIEW_X, VIEW_Y);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Proj2");
    glewInit();
    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
