/*
 * lab03.c
 *
 * An OpenGL source code template.
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "../mylib/initShader.h"
#include "../mylib/linalg.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

// double PI = 3.141592654;
int num_vertices;
GLfloat zoom = 1.02;
GLfloat ZOOM_START = 0.01;
GLfloat SCALING_FACTOR = 0.01;

GLfloat R1 = 10.0;
GLfloat R2 = 2.0;
int N1 = 20;
int N2 = 20;
char *FILENAME = "bunny.txt";
int VIEW_X = 512;
int VIEW_Y = 512;

GLuint ctm_location;

mat4 ctm = {{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}};

mat4 rz = {{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}};

vec4 down_loc;
int down_success;

/*
 * Function: get_torus_size
 * -------------------
 * Gets array of vertices to define a torus
 *
 * int n1: Number of sudivisions 1
 * 
 * int n2: Number of sudivisions 2
 *
 * Returns: Size
 */

int get_torus_size(int n1, int n2) {
    return 6 * n1 * n2;
}



/*
 * Function: get_torus_vertices
 * -------------------
 * Gets array of vertices to define a torus
 *
 * int n1: Number of sudivisions 1
 * 
 * int n2: Number of sudivisions 2
 *
 * int r1: large radius
 * 
 * int r2: small radius
 * 
 * Returns: vec4 vertices
 */

void get_torus_vertices(int n1, int n2, int r1, int r2, vec4* vertices) {
    
    int i, j;
    GLfloat theta, n_theta, phi, n_phi;
    // n1 is number of discretized torus angles
    for (i = 0; i < n1; i++) {
        theta = i * 2 * PI / n1;
        n_theta = (i+1) * 2 * PI / n1;
        for (j = 0; j < n2; j++) {
            phi = j * 2 * PI / n2;
            n_phi = (j + 1) * 2 * PI / n2;

            // First triangle
            vertices[6*(n1*i + j) + 0].x = (r1 + r2 * cos(theta)) * cos(phi);
            vertices[6*(n1*i + j) + 0].y = (r1 + r2 * cos(theta)) * sin(phi);
            vertices[6*(n1*i + j) + 0].z = r2 * sin(theta);
            vertices[6*(n1*i + j) + 0].w = 1.0;

            vertices[6*(n1*i + j) + 2].x = (r1 + r2 * cos(n_theta)) * cos(phi);
            vertices[6*(n1*i + j) + 2].y = (r1 + r2 * cos(n_theta)) * sin(phi);
            vertices[6*(n1*i + j) + 2].z = r2 * sin(n_theta);
            vertices[6*(n1*i + j) + 2].w = 1.0;

            vertices[6*(n1*i + j) + 1].x = (r1 + r2 * cos(n_theta)) * cos(n_phi);
            vertices[6*(n1*i + j) + 1].y = (r1 + r2 * cos(n_theta)) * sin(n_phi);
            vertices[6*(n1*i + j) + 1].z = r2 * sin(n_theta);
            vertices[6*(n1*i + j) + 1].w = 1.0;

            // Second triangle
            vertices[6*(n1*i + j) + 4].x = (r1 + r2 * cos(n_theta)) * cos(n_phi);
            vertices[6*(n1*i + j) + 4].y = (r1 + r2 * cos(n_theta)) * sin(n_phi);
            vertices[6*(n1*i + j) + 4].z = r2 * sin(n_theta);
            vertices[6*(n1*i + j) + 4].w = 1.0;

            vertices[6*(n1*i + j) + 3].x = (r1 + r2 * cos(theta)) * cos(n_phi);
            vertices[6*(n1*i + j) + 3].y = (r1 + r2 * cos(theta)) * sin(n_phi);
            vertices[6*(n1*i + j) + 3].z = r2 * sin(theta);
            vertices[6*(n1*i + j) + 3].w = 1.0;

            vertices[6*(n1*i + j) + 5].x = (r1 + r2 * cos(theta)) * cos(phi);
            vertices[6*(n1*i + j) + 5].y = (r1 + r2 * cos(theta)) * sin(phi);
            vertices[6*(n1*i + j) + 5].z = r2 * sin(theta);
            vertices[6*(n1*i + j) + 5].w = 1.0;
            
        }
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

int get_file_size(char* filename) {
    int size;
    FILE *file;
    if ((file = fopen(filename, "r")) != NULL) {

        fscanf(file, "%d\n", &size);

        fclose(file);
    } else {
        printf("File not found");
        size = -1;
    }
    return size;
}

/*
 * Function: get_file_vertices
 * -------------------
 * Gets array of vertices from file
 *
 * char *filename: path to file
 * 
 * vec4 *vertices: pointer to array of vertices
 *
 * Returns: None
 */

void get_file_vertices(char* filename, vec4* vertices) {
    
    FILE *file;
    if ((file = fopen(filename, "r")) != NULL) {

        int size;
        fscanf(file, "%d\n", &size);

        float t1, t2, t3, t4;
        for (int i = 0; i < size; i++) {
            fscanf(file, "%f,%f,%f,%f\n", &t1, &t2, &t3, &t4);
            (vertices)[i].x = t1;
            (vertices)[i].y = t2;
            (vertices)[i].z = t3;
            (vertices)[i].w = t4;
        }

        fclose(file);
    } else {
        printf("File not found");
    }
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
void get_colors(int size, vec4* colors) {


    // Triangles, n should be divisible by 3
    GLfloat color_1, color_2, color_3;

    int i, j;
    for (i = 0; i < size/3; i++) {

        // Get random color
        color_1 = (((GLfloat) rand()) / RAND_MAX);
        color_2 = (((GLfloat) rand()) / RAND_MAX);
        color_3 = (((GLfloat) rand()) / RAND_MAX);

        // Apply color to triangle
        for (j = 0; j < 3; j++) {
            (colors)[3*i + j].x = color_1;
            (colors)[3*i + j].y = color_2;
            (colors)[3*i + j].z = color_3;
            (colors)[3*i + j].w = 1.0;
        }
    }
}



void init(void)
{
    GLuint n_bytes;
    int choice = 0;
    vec4 *vertices, *colors;


    while (choice < 1 || choice > 2) {
        printf("Which to display?\n1: Torus\n2: Bunny\n> ");
        scanf("%d", &choice);
    }

    if (choice == 1) {
        // Torus
        num_vertices = get_torus_size(N1, N2);
        n_bytes = num_vertices * sizeof(vec4);
        vertices = (vec4*) malloc(n_bytes);

        get_torus_vertices(N1, N2, R1, R2, vertices);

    } else {
        // File
        num_vertices = get_file_size(FILENAME);
        n_bytes = num_vertices * sizeof(vec4);
        vertices = (vec4*) malloc(n_bytes);
        
        get_file_vertices(FILENAME, vertices);
    }

    // Get colors
    colors = (vec4*) malloc(n_bytes);
    get_colors(num_vertices, colors);

    // Starting zoom
    ctm = prod_mat_mat(ctm, scale(ZOOM_START, ZOOM_START, ZOOM_START));

    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * n_bytes, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, n_bytes, vertices);
    glBufferSubData(GL_ARRAY_BUFFER, n_bytes, n_bytes, colors);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    ctm_location = glGetUniformLocation(program, "ctm");

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) (n_bytes));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);

    free(vertices);
    free(colors);
}

void mouse(int button, int state, int x, int y) {
    
    if (button == GLUT_LEFT_BUTTON) {
        // Rotation
        if (state == GLUT_DOWN) {
            // printf("Click down @ %d, %d\n", x, y);
            down_success = get_ball(x, y, VIEW_X, VIEW_Y, (vec4 *) &down_loc); // , &down_loc
            if (down_success) {
                // printf("%f,%f,%f,%f\n", down_loc.x, down_loc.y, down_loc.z, down_loc.w);
            }
        } else if (state == GLUT_UP) {
            // printf("Click up @ %d, %d\n", x, y);
            vec4 up_loc;
            if (down_success && get_ball(x, y, VIEW_X, VIEW_Y, (vec4 *) &up_loc)) { //, &up_loc
                vec4 cross;
                vec4 origin = {0.0, 0.0, 0.0, 1.0};
                cross = normalize(cross_vec_vec(up_loc, down_loc));
                GLfloat theta = (magnitude(down_loc) * magnitude(up_loc))/dot_vec_vec(down_loc, up_loc);
                // printf("%f,%f,%f,%f,%f\n", cross.x, cross.y, cross.z, cross.w, theta);
                rz = rotate_v(cross, origin, theta * SCALING_FACTOR);
            }
        }
    } else if (button == 3) {
        // Scroll up, zoom out
        GLfloat z = zoom;
        ctm = prod_mat_mat(scale(z, z, z), ctm);
    } else if (button == 4) {
        // Scroll down, zoom in
        GLfloat z = 1.0/zoom;
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

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);

    glDrawArrays(GL_TRIANGLES, 0, num_vertices);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
    	glutLeaveMainLoop();

    //glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, VIEW_X, VIEW_Y);
}

void idle(void) {
    int now = glutGet(GLUT_ELAPSED_TIME);
    if (now % 20 == 0) {
        ctm = prod_mat_mat(rz, ctm);
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(VIEW_X, VIEW_Y);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Proj1");
    glewInit();
    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
