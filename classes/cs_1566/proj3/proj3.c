/*
 * proj3.c
 *
 * An OpenGL source code template.
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "../mylib/initShader.h"
#include "../mylib/linalg.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

// CONSTANTS
char VERTEX_FILE[10] = "city.obj";
char TEX_FILE[10] = "city.data";
int TEX_SIZE = 1024;
int NUM_EXTRA_TESSELS = 3;
vec4 EXTRA_TESSELS[3*3] = {
    // Floor 1
    {-50.0, 0.0, 50.0, 1.0},
    {300.0, 0.0, 50.0, 1.0},
    {-50.0, 0.0, -300.0, 1.0},

    // Floor 2
    {-50.0, 0.0, -300.0, 1.0},
    {300.0, 0.0, 50.0, 1.0},
    {300.0, 0.0, -300.0, 1.0},

    // View
    {5.0, 100.0, 0.0, 1.0},
    {0.0, 100.0, 0.0, 1.0},
    {0.0, 100.0, 10.0, 1.0}

};

vec2 EXTRA_TEX[3*3] = {
    // Floor 1
    {-1.0 , 0.0},
    {-1.0 , 0.0},
    {-1.0 , 0.0},

    // Floor 2
    {-1.0 , 0.0},
    {-1.0 , 0.0},
    {-1.0 , 0.0},

    // View
    {-2.0 , 0.0},
    {-2.0 , 0.0},
    {-2.0 , 0.0}
};

size_t n_total_vertices;

GLfloat zoom = 1.02;
GLfloat ZOOM_START = 0.01;
GLfloat SCALING_FACTOR = 0.1;

int VIEW_X = 512;
int VIEW_Y = 512;
vec4 down_loc;
int down_success;

// CTM
GLuint ctm_location;
mat4 ctm = {{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}};

vec4 vrp = {0.0, 1.0, 0.0, 1.0};
vec4 n = {0.0, 0.0, 1.0, 0.0};
vec4 vup = {0.0, 1.0, 0.0, 0.0};

GLfloat NEAR = -1.0;
GLfloat FAR = -1000.0;
RIGHT = 1;
LEFT = -1;
TOP = 1;
BOTTOM = -1;

// State
GLfloat azimuth = 0.0;
GLfloat azimuth_factor = .2;
vec4 p = {200.0, 1.0, -200.0, 1.0};
GLfloat p_factor = 1;
GLfloat theta = PI/2;

int view_state = 0;
int map_state = 0;

// FUNCTIONS

// Update ctm
void update_ctm() {

    // Position
    vrp = p;

    if (map_state == 1) {
        theta = 0;
        p.y = 100.0;
        n = (vec4) {0.0, -1.0, 0.0, 0.0};
        vup = (vec4) {0.0, 0.0, 1.0, 0.0};
    } else {
        p.y = 3.0;
        n = (vec4) {cos(azimuth), -cos(theta), sin(azimuth), 0.0};
    }

    mat4 vm = get_view_model(n, vup, vrp);
    int fov = 20;
    // mat4 p2 = get_perspective(NEAR, FAR);
    mat4 p = frustrum(NEAR, FAR, RIGHT, TOP, LEFT, BOTTOM);
    ctm = prod_mat_mat(p, vm);
    // ctm = vm;

}

// right
void right() {
    azimuth += azimuth_factor;
    if (azimuth > (2 * PI)) {
        azimuth -= (2 * PI);
    }
}

// left
void left() {
    azimuth -= azimuth_factor;
    if (azimuth < 0) {
        azimuth += (2 * PI);
    }
}

void forward() {
    p.x -= p_factor * cos(azimuth);
    p.z -= p_factor * sin(azimuth);
}

void backward() {
    p.x += p_factor * cos(azimuth);
    p.z += p_factor * sin(azimuth);
}

void s_right() {
    p.x += p_factor * sin(azimuth);
    p.z -= p_factor * cos(azimuth);
}

void s_left() {
    p.x -= p_factor * sin(azimuth);
    p.z += p_factor * cos(azimuth);
}

void down() {
    theta += azimuth_factor/4;
    if (theta > PI + azimuth_factor/4) {
        theta = PI;
    }
}

void up() {
    theta -= azimuth_factor/4;
    if (theta < - azimuth_factor/4) {
        theta = 0;
    }
}

void reset_view() {
    theta = PI/2;
}


// Count v definitions in file
size_t count_v(char *filename) {

    FILE *f;
    f = fopen(filename, "r");
    size_t num_v = 0;
    size_t bufsize = 200;
    char *buffer;
    buffer = malloc(bufsize * sizeof(char));
    //v is first block
    while (!feof(f)) {
        getline(&buffer, &bufsize, f);
        if (strstr(buffer, "v ") != NULL) {
            num_v++;
        }
    }
    free(buffer);
    fclose(f);
    return num_v;
}

// Count vt definitions in file
size_t count_vt(char *filename) {

    FILE *f;
    f = fopen(filename, "r");
    size_t num_v = 0;
    size_t bufsize = 200;
    char *buffer;
    buffer = malloc(bufsize * sizeof(char));
    //v is first block
    while (!feof(f)) {
        getline(&buffer, &bufsize, f);
        if (strstr(buffer, "vt ") != NULL) {
            num_v++;
        }
    }
    free(buffer);
    fclose(f);
    return num_v;
}

// Count number of facet vertices
size_t count_f(char *filename) {

    FILE *f;
    f = fopen(filename, "r");
    size_t num_v = 0;
    size_t bufsize = 500;
    char *buffer;
    buffer = malloc(bufsize * sizeof(char));
    //v is first block
    while (!feof(f)) {
        getline(&buffer, &bufsize, f);
        if (strstr(buffer, "f ") != NULL) {
            
            // Move forward for each space
            char *b = buffer;

            while(*b != '\n') {
                if (*b == ' ') {
                    num_v++;
                }
                b++;
            }
            num_v -= 2;
        }
    }
    num_v -= 2;
    free(buffer);
    fclose(f);
    return num_v;
}

// Load the obj
void load_obj(char *filename, size_t n_v, size_t n_vt, size_t n_f, vec4 *f, vec2 *t) {

    
    FILE *file;
    GLfloat x,y,z;
    int v1,v2,v3,v4,vt1,vt2,vt3,vt4;

    file = fopen(filename, "r");

    vec4 *v = (vec4 *)calloc(n_v, sizeof(vec4));
    vec2 *vt = (vec2 *)calloc(n_vt, sizeof(vec2));


    // Load the vertices
    for (size_t i = 0; i < n_v; i++) {
        fscanf(file, "v %f %f %f\n", &x, &y, &z);
        v[i] = (vec4) {x, y, z, 1.0};
    }

    // Load the vt's
    for (size_t i = 0; i < n_vt; i++) {
        fscanf(file, "vt %f %f\n", &x, &y);
        vt[i] = (vec2) {x, 1.0-y};
    }

    // Load the vertices
    int c = 0;

    while (!feof(file)) {
        // Scan first three values
        // printf("%d\n", c);
        fscanf(file, "f %d/%d %d/%d %d/%d", &v1, &vt1, &v2, &vt2, &v3, &vt3);

        // Make one facet
        f[3*c + 0] = v[v1-1];
        f[3*c + 1] = v[v2-1];
        f[3*c + 2] = v[v3-1];
        t[3*c + 0] = vt[vt1-1];
        t[3*c + 1] = vt[vt2-1];
        t[3*c + 2] = vt[vt3-1];
        c++;

        while (fscanf(file, "%d/%d", &v4, &vt4) != 0 && !feof(file)) {
            // Make one facet
            // printf("%d, %d, %d\n", c, v4, vt4);
            f[3*c + 0] = v[v1-1];
            f[3*c + 1] = v[v3-1];
            f[3*c + 2] = v[v4-1];
            t[3*c + 0] = vt[vt1-1];
            t[3*c + 1] = vt[vt3-1];
            t[3*c + 2] = vt[vt4-1];
            c++;
            
            // Move 4 to 3
            v3 = v4;
            vt3 = vt4;
        }

    }
    

    fclose(file);
}

void adjust(vec4 *f, int n_f) {
    // Get min x, y, z
    float min_x = 100.0, min_y = 100.0, max_z = -100.0;

    // Find minimums
    for (int i = 0; i < n_f*3; i++) {
        if (f[i].x < min_x) {
            min_x = f[i].x;
        }
        if (f[i].y < min_y) {
            min_y = f[i].y;
        }
        if (f[i].z > max_z) {
            max_z = f[i].z;
        }
    }

    mat4 scale_mat = scale(100, 100, 100);

    // Shift n' Scale
    for (int i = 0; i < n_f*3; i++) {
        f[i].x -= min_x;
        f[i].y -= min_y;
        f[i].z -= max_z;
        f[i] = prod_mat_vec(scale_mat, f[i]);
    }
}


void init(void)
{

    // Get sizes
    size_t n_v, n_vt, n_f, n_all_f;
    n_v = count_v(VERTEX_FILE);
    n_vt = count_vt(VERTEX_FILE);
    n_f = count_f(VERTEX_FILE);
    n_all_f = n_f + NUM_EXTRA_TESSELS;
    n_total_vertices = 3 * n_all_f;
    
    // printf("%d\n", n_v);
    // printf("%d\n", n_vt);
    // printf("%d\n", n_f);

    // Load standard tesselations
    vec4 *f = (vec4 *)calloc(n_total_vertices,sizeof(vec4));
    vec2 *t = (vec2 *)calloc(n_total_vertices,sizeof(vec2));
    load_obj(VERTEX_FILE, n_v, n_vt, n_f, f, t);

    // Shift and scale
    adjust(f, n_f);

    // Load texels
    GLubyte texels[TEX_SIZE][TEX_SIZE][3];
    FILE *fp = fopen(TEX_FILE, "r");
    fread(texels, TEX_SIZE * TEX_SIZE * 3, 1, fp);
    fclose(fp);


    // Some boilerplate
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    GLuint mytex[1];
    glGenTextures(1, mytex);
    glBindTexture(GL_TEXTURE_2D, mytex[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_SIZE, TEX_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int param;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &param);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Make the buffer
    size_t nbytes_vertices = n_total_vertices * sizeof(vec4);

    size_t nbytes_tex = n_total_vertices * sizeof(vec2);

    size_t nbytes = nbytes_vertices + nbytes_tex;

    printf("%d\n", n_total_vertices);
    update_ctm();

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, nbytes, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, n_f*3*sizeof(vec4), f);
    glBufferSubData(GL_ARRAY_BUFFER, n_f*3*sizeof(vec4), NUM_EXTRA_TESSELS*3*sizeof(vec4), EXTRA_TESSELS);
    glBufferSubData(GL_ARRAY_BUFFER, nbytes_vertices, n_f*3*sizeof(vec2), t);
    glBufferSubData(GL_ARRAY_BUFFER, n_f*3*sizeof(vec2) + nbytes_vertices, NUM_EXTRA_TESSELS*3*sizeof(vec2), EXTRA_TEX);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vTexCoord = glGetAttribLocation(program, "vTexCoord");
    glEnableVertexAttribArray(vTexCoord);
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(nbytes_vertices));

    GLuint texture_location = glGetUniformLocation(program, "texture");
    glUniform1i(texture_location, 0);

    ctm_location = glGetUniformLocation(program, "ctm");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    // glPolygonMode(GL_BACK, GL_LINE);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);

    glDrawArrays(GL_TRIANGLES, 0, n_total_vertices);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    printf("%c\n", key);
    
    switch(key) {
        case 'j':
            printf("move left\n");
            s_left();
            break;
        case 'l':
            printf("move right\n");
            s_right();
            break;
        case 'm':
            map_state = 1;
            break;
        case 'e':
            map_state = 0;
            break;
        case '[':
            printf("look up\n");
            up();
            break;
        case ']':
            printf("look down\n");
            down();
            break;
        case 'r':
            printf("view reset\n");
            reset_view();
            break;
    }

    update_ctm();

    print_mat(ctm);

    print_vec(p);
    printf("%f\n", azimuth);

    glutPostRedisplay();
}

void special_keys(unsigned char key, int mousex, int mousey) {
    switch(key) {

        case GLUT_KEY_UP:
            printf("forward\n");
            forward();
            break;
        case GLUT_KEY_DOWN:
            printf("backward\n");
            backward();
            break;
        case GLUT_KEY_LEFT:
            printf("look left\n");
            left();
            break;
        case GLUT_KEY_RIGHT:
            printf("look right\n");
                right();
            break;
        case GLUT_KEY_PAGE_UP:
            printf("look up\n");
                up();
            break;
        case GLUT_KEY_PAGE_DOWN:
            printf("look down\n");
                down();
            break;
    }
    update_ctm();

    print_mat(ctm);
    print_vec(p);
    printf("%f\n", azimuth);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    
    // mat4 rz;
    // if (button == GLUT_LEFT_BUTTON) {
    //     // Rotation
    //     if (state == GLUT_DOWN) {
    //         // printf("Click down @ %d, %d\n", x, y);
    //         down_success = get_ball(x, y, VIEW_X, VIEW_Y, (vec4 *) &down_loc); // , &down_loc
    //         if (down_success) {
    //             // printf("%f,%f,%f,%f\n", down_loc.x, down_loc.y, down_loc.z, down_loc.w);
    //         }
    //     } else if (state == GLUT_UP) {
    //         // printf("Click up @ %d, %d\n", x, y);
    //         vec4 up_loc;
    //         if (down_success && get_ball(x, y, VIEW_X, VIEW_Y, (vec4 *) &up_loc)) { //, &up_loc
    //             vec4 cross;
    //             vec4 origin = {0.0, 0.0, 0.0, 1.0};
    //             if (equals_vec(up_loc, down_loc)) return;
    //             cross = normalize(cross_vec_vec(up_loc, down_loc));
    //             GLfloat theta = (magnitude(down_loc) * magnitude(up_loc))/dot_vec_vec(down_loc, up_loc);
    //             // printf("%f,%f,%f,%f,%f\n", cross.x, cross.y, cross.z, cross.w, theta);
    //             rz = rotate_v(cross, origin, theta * SCALING_FACTOR);
    //             ctm = prod_mat_mat(ctm, rz);
    //         }
    //     }
    // } else if (button == 3) {
    //     // Scroll up, zoom out
    //     GLfloat z = zoom;
    //     ctm = prod_mat_mat(scale(z, z, z), ctm);
    // } else if (button == 4) {
    //     // Scroll down, zoom in
    //     GLfloat z = 1.0/zoom;
    //     ctm = prod_mat_mat(scale(z, z, z), ctm);
    // }
    //     // Rerender
    //     glutPostRedisplay();
}

void reshape(int width, int height)
{
    glViewport(0, 0, 512, 512);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("proj3");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special_keys);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);
    glutMainLoop();

    
    
    // assert(n_f == 7740);
    // printf("%d\n", n_f);

    

    return 0;
}
