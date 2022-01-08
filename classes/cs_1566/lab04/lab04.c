/*
 * Lab04.c
 *
 * An OpenGL source code Lab04.
 */


#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <stdio.h>
#include <assert.h>

#include "../mylib/initShader.h"
#include "../mylib/linalg.h"


#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

// Cone parameters
vec4 CONE_LOCATION = {0.0, -0.75, 0.0, 1.0};
GLfloat CONE_HEIGHT = 1.5;
GLfloat CONE_RADIUS = 0.5;
int NUM_SUBDIVISIONS = 20;
double PI = 3.141592654;

// Transformation variables
// Rotation
GLfloat angle = 0.0;
GLfloat ANGLE_INC = 0.002;


// Scaling
GLfloat s_scale = 1.0;
GLfloat SCALE_INC = 0.002;
GLfloat MAX_SCALE_CHANGE = 0.5;
int scaleDirection = 1;

// Translation
GLfloat xdisp = 0;
GLfloat DISP_INC = 0.002;
GLfloat MAX_DISP = 0.25;
int dispDirection = 1;

GLuint ctm_location;

mat4 ctm = {{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}};
            
/*
 * Function: cone_get_num_vertices
 * -------------------
 * Gets total number of vertices from number of circle divisions
 * 
 * Returns: int num vertices
 */

int cone_get_num_vertices() {
    return NUM_SUBDIVISIONS*6;
}

/*
 * Function: cone_get_num_vertices
 * -------------------
 * Gets array of vertices from number of circle divisions
 *
 * Returns: vec4 vertices
 */

void cone_get_vertices(vec4* vertices) {
    
    int num_vertices = cone_get_num_vertices();

    // Each subdivision gets 6 points, or 2 triangles
    assert(num_vertices % 6 == 0);

    int i;
    GLfloat theta;
    GLfloat dtheta = 2 * PI / NUM_SUBDIVISIONS;
    for (i = 0; i < NUM_SUBDIVISIONS; i++) {
        theta = i * dtheta;

        // TOP TRIANGLE
        vertices[6*i].x = CONE_RADIUS * cos(theta);
        vertices[6*i].y = CONE_LOCATION.y;
        vertices[6*i].z = CONE_RADIUS * sin(theta);
        vertices[6*i].w = 1.0;

        vertices[6*i+1].x = CONE_LOCATION.x;
        vertices[6*i+1].y = CONE_LOCATION.y + CONE_HEIGHT;
        vertices[6*i+1].z = CONE_LOCATION.z;
        vertices[6*i+1].w = 1.0;

        vertices[6*i+2].x = CONE_RADIUS * cos(theta+dtheta);
        vertices[6*i+2].y = CONE_LOCATION.y;
        vertices[6*i+2].z = CONE_RADIUS * sin(theta+dtheta);
        vertices[6*i+2].w = 1.0;

        // BOTTOM TRIANGLE
        vertices[6*i+3].x = CONE_RADIUS * cos(theta);
        vertices[6*i+3].y = CONE_LOCATION.y;
        vertices[6*i+3].z = CONE_RADIUS * sin(theta);
        vertices[6*i+3].w = 1.0;

        vertices[6*i+4].x = CONE_RADIUS * cos(theta+dtheta);
        vertices[6*i+4].y = CONE_LOCATION.y;
        vertices[6*i+4].z = CONE_RADIUS * sin(theta+dtheta);
        vertices[6*i+4].w = 1.0;

        vertices[6*i+5].x = CONE_LOCATION.x;
        vertices[6*i+5].y = CONE_LOCATION.y;
        vertices[6*i+5].z = CONE_LOCATION.z;
        vertices[6*i+5].w = 1.0;
    }
}

/*
 * Function: cone_get_colors
 * -------------------
 * Gets array of colors
 * 
 * Returns: vec4 vertices
 */

void cone_get_colors(vec4* colors) {

    int n = cone_get_num_vertices();

    // Triangles, n should be divisible by 3
    assert (n % 3 == 0);
    GLfloat color_1, color_2, color_3;

    int i, j;
    for (i = 0; i < n/3; i++) {

        // Get random color
        color_1 = (((GLfloat) rand()) / RAND_MAX);
        color_2 = (((GLfloat) rand()) / RAND_MAX);
        color_3 = (((GLfloat) rand()) / RAND_MAX);

        // Apply color to triangle
        for (j = 0; j < 3; j++) {
            colors[3*i + j].x = color_1;
            colors[3*i + j].y = color_2;
            colors[3*i + j].z = color_3;
            colors[3*i + j].w = 1.0;
        }
    }
}


void init(void)
{
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    // Make cone
    int num_vertices = cone_get_num_vertices();
    vec4 vertices[num_vertices];
    vec4 colors[num_vertices];
    cone_get_vertices(&vertices);
    cone_get_colors(&colors);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    ctm_location = glGetUniformLocation(program, "ctm");

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *) sizeof(vertices));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glUniformMatrix4fv(ctm_location, 1, GL_FALSE, (GLfloat *) &ctm);

    glDrawArrays(GL_TRIANGLES, 0, cone_get_num_vertices());

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
    glViewport(0, 0, 512, 512);
}

void idle() {

    // Handle rotation
    angle += ANGLE_INC;
    if (angle > 2*PI) angle = 0;

    // Handle displacement
    xdisp += (DISP_INC * dispDirection);
    if (xdisp > MAX_DISP) {
        xdisp = MAX_DISP;
        dispDirection = -1;
    } else if (xdisp < MAX_DISP * -1) {
        xdisp = MAX_DISP * -1;
        dispDirection = 1;
    }

    // Handle scaling
    s_scale += (SCALE_INC * scaleDirection);
    if (s_scale > (1 + MAX_SCALE_CHANGE)) {
        s_scale = (1 + MAX_SCALE_CHANGE);
        scaleDirection = -1;
    } else if (s_scale < (1 - MAX_SCALE_CHANGE)) {
        s_scale = (1 - MAX_SCALE_CHANGE);
        scaleDirection = 1;
    }

    // Added translation functions to linear algebra library
    mat4 ctm1 = rotate_x(angle);
    mat4 ctm2 = translate(xdisp, 0, 0);
    mat4 ctm3 = scale(s_scale, s_scale, s_scale);
    ctm = prod_mat_mat(ctm1, ctm2);
    ctm = prod_mat_mat(ctm, ctm3);

    // Rerender
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Lab04");
    glewInit();
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);

    glutIdleFunc(idle);
    glutMainLoop();

    return 0;
}
