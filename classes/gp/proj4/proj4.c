/*
 * proj4.c
 *
 * Rubik's cube project
 * Shane Riley
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

// State
int shuffle_state = 0;
int animation_state = 0;
int shuffle_step;
int animation_step;
// 0: none
// 1: front
// 2: back
// 3: right
// 4: left
// 5: top
// 6: bottom
int front[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
int right[9] = {2, 11, 20, 5, 14, 23, 8, 17, 26};
int back[9] = {20, 19, 18, 23, 22, 21, 26, 25, 24};
int left[9] = {18, 9, 0, 21, 12, 3, 24, 15, 6};
int up[9] = {18, 19, 20, 9, 10, 11, 0, 1, 2};
int down[9] = {6, 7, 8, 15, 16, 17, 24, 25, 26};
GLfloat base_height = -10;
// Light
vec4 lightPosition = {0.0, 10.0, 0.0, 0.0};

// Animation
int n_steps = 9;
char shuffles[31];

// vertices and cubies
int n_v = 144;
int n_v_source = 36;
int n_v_bottom = 6;
int n_c = 27;
vec4 vertices[186];
vec4 colors[186];
vec4 normals[186];
mat4 cubies[27];
int windowSize;
vec4 click;

int down_success = 0;
GLfloat ZOOM_FACTOR = 1.02;
GLfloat MOVE_FACTOR = 0.5;
GLfloat LIGHT_MOVE_FACTOR = 0.5;

mat4 ctm1 = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};
mat4 id_mat = {
    {1.0, 0.0, 0.0, 0.0},
    {0.0, 1.0, 0.0, 0.0},
    {0.0, 0.0, 1.0, 0.0},
    {0.0, 0.0, 0.0, 1.0}
};

GLuint ctm1_location;
GLuint ctm2_location;
GLuint lp_location;
GLuint eye_location;
vec4 vrp;

GLfloat view_radius = 10;
GLfloat view_theta = PI/2;
GLfloat view_phi = PI/2;

GLfloat NEAR = -5.0;
GLfloat FAR = -100.0;
GLfloat RIGHT = 1;
GLfloat LEFT = -1;
GLfloat TOP = 1;
GLfloat BOTTOM = -1;


void get_edges(vec4 *v, int n_v, float t) {

    v[0] = (vec4){-0.5, -0.5, 0.6, 1.0};
    v[1] = (vec4){0.5, -0.5, 0.6, 1.0};
    v[2] = (vec4){0.5, 0.5, 0.6, 1.0};
    v[3] = (vec4){-0.5, -0.5, 0.6, 1.0};
    v[4] = (vec4){0.5, 0.5, 0.6, 1.0};
    v[5] = (vec4){-0.5, 0.5, 0.6, 1.0};
    // for(int i=0; i<6; i++) {
    //     v[i] = prod_mat_vec(translate(0,0,.1), v[i]);
    // }
    v[6] = (vec4){-0.5, 0.5, 0.6, 1.0};
    v[7] = (vec4){0.5, 0.5, 0.6, 1.0};
    v[8] = (vec4){0.5, 0.6, 0.5, 1.0};
    v[9] = (vec4){-0.5, -0.5, 0.5, 1.0};
    v[10] = (vec4){0.5, 0.5, 0.5, 1.0};
    v[11] = (vec4){-0.5, 0.5, 0.5, 1.0};
    v[12] = (vec4){0.5, 0.5, 0.6, 1.0};
    v[13] = (vec4){0.5, -0.5, 0.6, 1.0};
    v[14] = (vec4){0.6, -0.5, 0.5, 1.0};
    v[15] = (vec4){0.5, 0.5, 0.6, 1.0};
    v[16] = (vec4){0.6, -0.5, 0.5, 1.0};
    v[17] = (vec4){0.6, 0.5, 0.5, 1.0};
    v[18] = (vec4){0.5, 0.5, 0.6, 1.0};
    v[19] = (vec4){0.6, 0.5, 0.5, 1.0};
    v[20] = (vec4){0.5, 0.6, 0.5, 1.0};
    v[21] = (vec4){0.5, -0.6, 0.5, 1.0};
    v[22] = (vec4){0.6, -0.5, 0.5, 1.0};
    v[23] = (vec4){0.5, -0.5, 0.6, 1.0};

    for (int i=0; i<24; i++) {
        v[24 + i] = prod_mat_vec(rotate_y(PI/2), v[i]);
    }
    for (int i=0; i<24; i++) {
        v[48 + i] = prod_mat_vec(rotate_y(PI), v[i]);
    }
    for (int i=0; i<24; i++) {
        v[72 + i] = prod_mat_vec(rotate_y(3*PI/2), v[i]);
    }
    for (int i=0; i<24; i++) {
        v[96 + i] = prod_mat_vec(rotate_x(PI/2), v[i]);
    }
    for (int i=0; i<6; i++) {
        v[120 + i] = prod_mat_vec(rotate_x(3*PI/2), v[i]);
    }
    for (int i=0; i<18; i++) {
        v[126 + i] = prod_mat_vec(rotate_y(PI), v[102+i]);
    }
}

void get_normals(vec4 *normals, int size) {
    for (int j = 0; j < n_v/3; j++) {
        vec4 v1 = vertices[j*3];
        vec4 v2 = vertices[j*3+1];
        vec4 v3 = vertices[j*3+2];

        vec4 v4 = diff_vec_vec(v2, v1);
        vec4 v5 = diff_vec_vec(v3, v1);
        vec4 v6 = cross_vec_vec(v4, v5);
        vec4 v7 = normalize(v6);
        v7.w = 0.0;
        normals[j*3] = v7;
        normals[j*3+1] = v7;
        normals[j*3+2] = v7;
    }
}

void get_lpos() {
    GLfloat xp = lightPosition.x + 0.1;
    GLfloat xn = lightPosition.x - 0.1;
    GLfloat yp = lightPosition.y + 0.1;
    GLfloat yn = lightPosition.y - 0.1;
    GLfloat zp = lightPosition.z + 0.1;
    GLfloat zn = lightPosition.z - 0.1;

    // y
    vertices[n_v + 0] = (vec4){xn, yp, zn, 1.0};
    vertices[n_v + 1] = (vec4){xn, yp, zp, 1.0};
    vertices[n_v + 2] = (vec4){xp, yp, zn, 1.0};
    vertices[n_v + 3] = (vec4){xp, yp, zn, 1.0};
    vertices[n_v + 4] = (vec4){xn, yp, zp, 1.0};
    vertices[n_v + 5] = (vec4){xp, yp, zp, 1.0};
    normals[n_v + 0] = (vec4){0, yn, 0, 1.0};
    normals[n_v + 1] = (vec4){0, yn, 0, 1.0};
    normals[n_v + 2] = (vec4){0, yn, 0, 1.0};
    normals[n_v + 3] = (vec4){0, yn, 0, 1.0};
    normals[n_v + 4] = (vec4){0, yn, 0, 1.0};
    normals[n_v + 5] = (vec4){0, yn, 0, 1.0};

    vertices[n_v + 6] = (vec4){xn, yn, zn, 1.0};
    vertices[n_v + 7] = (vec4){xp, yn, zn, 1.0};
    vertices[n_v + 8] = (vec4){xn, yn, zp, 1.0};
    vertices[n_v + 9] = (vec4){xp, yn, zn, 1.0};
    vertices[n_v + 10] = (vec4){xp, yn, zp, 1.0};
    vertices[n_v + 11] = (vec4){xn, yn, zp, 1.0};

    // x
    vertices[n_v + 12] = (vec4){xp, yn, zn, 1.0};
    vertices[n_v + 13] = (vec4){xp, yn, zp, 1.0};
    vertices[n_v + 14] = (vec4){xp, yp, zn, 1.0};
    vertices[n_v + 15] = (vec4){xp, yp, zn, 1.0};
    vertices[n_v + 16] = (vec4){xp, yn, zp, 1.0};
    vertices[n_v + 17] = (vec4){xp, yp, zp, 1.0};
    vertices[n_v + 18] = (vec4){xn, yn, zn, 1.0};
    vertices[n_v + 19] = (vec4){xn, yp, zn, 1.0};
    vertices[n_v + 20] = (vec4){xn, yn, zp, 1.0};
    vertices[n_v + 21] = (vec4){xn, yp, zn, 1.0};
    vertices[n_v + 22] = (vec4){xn, yp, zp, 1.0};
    vertices[n_v + 23] = (vec4){xn, yn, zp, 1.0};

    // z
    vertices[n_v + 24] = (vec4){xn, yn, zp, 1.0};
    vertices[n_v + 25] = (vec4){xp, yn, zp, 1.0};
    vertices[n_v + 26] = (vec4){xn, yp, zp, 1.0};
    vertices[n_v + 27] = (vec4){xn, yp, zp, 1.0};
    vertices[n_v + 28] = (vec4){xp, yn, zp, 1.0};
    vertices[n_v + 29] = (vec4){xp, yp, zp, 1.0};
    vertices[n_v + 30] = (vec4){xn, yn, zn, 1.0};
    vertices[n_v + 31] = (vec4){xn, yp, zn, 1.0};
    vertices[n_v + 32] = (vec4){xp, yn, zn, 1.0};
    vertices[n_v + 33] = (vec4){xn, yp, zn, 1.0};
    vertices[n_v + 34] = (vec4){xp, yp, zn, 1.0};
    vertices[n_v + 35] = (vec4){xp, yn, zn, 1.0};

    // Base
    vertices[n_v + 36] = (vec4){-10, base_height, -10, 1.0};
    vertices[n_v + 37] = (vec4){-10, base_height, 10, 1.0};
    vertices[n_v + 38] = (vec4){10, base_height, -10, 1.0};
    vertices[n_v + 39] = (vec4){10, base_height, -10, 1.0};
    vertices[n_v + 40] = (vec4){-10, base_height, 10, 1.0};
    vertices[n_v + 41] = (vec4){10, base_height, 10, 1.0};

    for (int i = 0; i < 42; i++) {
        colors[n_v + i] = (vec4){1.0, 1.0, 1.0, 1.0};
        normals[n_v + i] = (vec4){1.0, 1.0, 1.0, 1.0};
    }
    
}

int shuffle(){
	if(animation_state == 0 && shuffle_state == 0){

        // gen chars
        for (int i = 0; i < 30; i++) {
            int num = rand() % 12;
            if (num == 0) {
                shuffles[i] = 'f';
            }
            if (num == 1) {
                shuffles[i] = 'u';
            }
            if (num == 2) {
                shuffles[i] = 'r';
            }
            if (num == 3) {
                shuffles[i] = 'l';
            }
            if (num == 4) {
                shuffles[i] = 'd';
            }
            if (num == 5) {
                shuffles[i] = 'b';
            }
            if (num == 6) {
                shuffles[i] = 'F';
            }
            if (num == 7) {
                shuffles[i] = 'U';
            }
            if (num == 8) {
                shuffles[i] = 'R';
            }
            if (num == 9) {
                shuffles[i] = 'L';
            }
            if (num == 10) {
                shuffles[i] = 'D';
            }
            if (num == 11) {
                shuffles[i] = 'B';
            }
        }

        shuffle_state = 1;
		shuffle_step = 0;
        animation_step = 0;
		return 1;
	}
	return 0;
}

int rotate_front(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = front[i];
		}
		front[0] = temp[6];
		front[1] = temp[3];
		front[2] = temp[0];
		front[3] = temp[7];
		front[4] = temp[4];
		front[5] = temp[1];
		front[6] = temp[8];
		front[7] = temp[5];
		front[8] = temp[2];
		right[0] = front[2];
		right[3] = front[5];
		right[6] = front[8];
		up[6] = front[0];
		up[7] = front[1];
		up[8] = front[2];
		left[2] = front[0];
		left[5] = front[3];
		left[8] = front[6]; 
		down[0] = front[6];
		down[1] = front[7];
		down[2] = front[8];
		animation_state = 1;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_front2(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = front[i];
		}
		front[0] = temp[2];
		front[1] = temp[5];
		front[2] = temp[8];
		front[3] = temp[1];
		front[4] = temp[4];
		front[5] = temp[7];
		front[6] = temp[0];
		front[7] = temp[3];
		front[8] = temp[6];
		right[0] = front[2];
		right[3] = front[5];
		right[6] = front[8];
		up[6] = front[0];
		up[7] = front[1];
		up[8] = front[2];
		left[2] = front[0];
		left[5] = front[3];
		left[8] = front[6]; 
		down[0] = front[6];
		down[1] = front[7];
		down[2] = front[8];
        up[6] = front[0];
		up[7] = front[1];
		up[8] = front[2];
		left[2] = front[0];
		left[5] = front[3];
		left[8] = front[6]; 
		down[0] = front[6];
		down[1] = front[7];
		down[2] = front[8];
		animation_state = 7;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_right(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = right[i];
		}
		right[0] = temp[6];
		right[1] = temp[3];
		right[2] = temp[0];
		right[3] = temp[7];
		right[4] = temp[4];
		right[5] = temp[1];
		right[6] = temp[8];
		right[7] = temp[5];
		right[8] = temp[2];
		back[0] = right[2];
		back[3] = right[5];
		back[6] = right[8];
		up[2] = right[2];
		up[5] = right[1];
		up[8] = right[0];
		front[2] = right[0];
		front[5] = right[3];
		front[8] = right[6];
		down[2] = right[6];
		down[5] = right[7];
		down[8] = right[8];
		animation_state = 3;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_right2(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = right[i];
		}
        right[0] = temp[2];
		right[1] = temp[5];
		right[2] = temp[8];
		right[3] = temp[1];
		right[4] = temp[4];
		right[5] = temp[7];
		right[6] = temp[0];
		right[7] = temp[3];
		right[8] = temp[6];
		back[0] = right[2];
		back[3] = right[5];
		back[6] = right[8];
		up[2] = right[2];
		up[5] = right[1];
		up[8] = right[0];
		front[2] = right[0];
		front[5] = right[3];
		front[8] = right[6];
		down[2] = right[6];
		down[5] = right[7];
		down[8] = right[8];
		animation_state = 9;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_up(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = up[i];
		}
		up[0] = temp[6];
		up[1] = temp[3];
		up[2] = temp[0];
		up[3] = temp[7];
		up[4] = temp[4];
		up[5] = temp[1];
		up[6] = temp[8];
		up[7] = temp[5];
		up[8] = temp[2];
		right[0] = up[8];
		right[1] = up[5];
		right[2] = up[2];
		back[0] = up[2];
		back[1] = up[1];
		back[2] = up[0];
		left[0] = up[0];
		left[1] = up[3];
		left[2] = up[6];
		front[0] = up[6];
		front[1] = up[7];
		front[2] = up[8];
		animation_state = 5;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_up2(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = up[i];
		}
		up[0] = temp[2];
		up[1] = temp[5];
		up[2] = temp[8];
		up[3] = temp[1];
		up[4] = temp[4];
		up[5] = temp[7];
		up[6] = temp[0];
		up[7] = temp[3];
		up[8] = temp[6];
		right[0] = up[8];
		right[1] = up[5];
		right[2] = up[2];
		back[0] = up[2];
		back[1] = up[1];
		back[2] = up[0];
		left[0] = up[0];
		left[1] = up[3];
		left[2] = up[6];
		front[0] = up[6];
		front[1] = up[7];
		front[2] = up[8];
		animation_state = 11;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_left(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = left[i];
		}
		left[0] = temp[6];
		left[1] = temp[3];
		left[2] = temp[0];
		left[3] = temp[7];
		left[4] = temp[4];
		left[5] = temp[1];
		left[6] = temp[8];
		left[7] = temp[5];
		left[8] = temp[2];
		up[0] = left[0];
		up[3] = left[1];
		up[6] = left[2];
		front[0] = left[2];
		front[3] = left[5];
		front[6] = left[8];
		down[6] = left[6];
		down[3] = left[7];
		down[0] = left[8];
		back[2] = left[0];
		back[5] = left[3];
		back[8] = left[6];
		animation_state = 4;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_left2(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = left[i];
		}
		left[0] = temp[2];
		left[1] = temp[5];
		left[2] = temp[8];
		left[3] = temp[1];
		left[4] = temp[4];
		left[5] = temp[7];
		left[6] = temp[0];
		left[7] = temp[3];
		left[8] = temp[6];
		up[0] = left[0];
		up[3] = left[1];
		up[6] = left[2];
		front[0] = left[2];
		front[3] = left[5];
		front[6] = left[8];
		down[6] = left[6];
		down[3] = left[7];
		down[0] = left[8];
		back[2] = left[0];
		back[5] = left[3];
		back[8] = left[6];
		animation_state = 10;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_back(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = back[i];
		}
		back[0] = temp[6];
		back[1] = temp[3];
		back[2] = temp[0];
		back[3] = temp[7];
		back[4] = temp[4];
		back[5] = temp[1];
		back[6] = temp[8];
		back[7] = temp[5];
		back[8] = temp[2];
		up[2] = back[0];
		up[1] = back[1];
		up[0] = back[2];
		left[0] = back[2];
		left[3] = back[5];
		left[6] = back[8];
		down[6] = back[8];
		down[7] = back[7];
		down[8] = back[6];
		right[2] = back[0];
		right[5] = back[3];
		right[8] = back[6];
		animation_state = 2;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_back2(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = back[i];
		}
		back[0] = temp[2];
		back[1] = temp[5];
		back[2] = temp[8];
		back[3] = temp[1];
		back[4] = temp[4];
		back[5] = temp[7];
		back[6] = temp[0];
		back[7] = temp[3];
		back[8] = temp[6];
		up[2] = back[0];
		up[1] = back[1];
		up[0] = back[2];
		left[0] = back[2];
		left[3] = back[5];
		left[6] = back[8];
		down[6] = back[8];
		down[7] = back[7];
		down[8] = back[6];
		right[2] = back[0];
		right[5] = back[3];
		right[8] = back[6];
		animation_state = 8;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_down(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = down[i];
		}
		down[0] = temp[6];
		down[1] = temp[3];
		down[2] = temp[0];
		down[3] = temp[7];
		down[4] = temp[4];
		down[5] = temp[1];
		down[6] = temp[8];
		down[7] = temp[5];
		down[8] = temp[2];
		front[6] = down[0];
		front[7] = down[1];
		front[8] = down[2];
		right[6] = down[2];
		right[7] = down[5];
		right[8] = down[8];
		back[6] = down[8];
		back[7] = down[7];
		back[8] = down[6];
		left[6] = down[6];
		left[7] = down[3];
		left[8] = down[0];
		animation_state = 6;
        animation_step = 0;
		return 1;
	}
	return 0;
}
int rotate_down2(){
	if(animation_state == 0){
		int temp[9];
		for(int i=0; i<9; i++){
			temp[i] = down[i];
		}
		down[0] = temp[2];
		down[1] = temp[5];
		down[2] = temp[8];
		down[3] = temp[1];
		down[4] = temp[4];
		down[5] = temp[7];
		down[6] = temp[0];
		down[7] = temp[3];
		down[8] = temp[6];
		front[6] = down[0];
		front[7] = down[1];
		front[8] = down[2];
		right[6] = down[2];
		right[7] = down[5];
		right[8] = down[8];
		back[6] = down[8];
		back[7] = down[7];
		back[8] = down[6];
		left[6] = down[6];
		left[7] = down[3];
		left[8] = down[0];
		animation_state = 12;
        animation_step = 0;
		return 1;
	}
	return 0;
}

void init(void) {
    for (int i = 0; i < n_c; i++) {
        cubies[i] = id_mat;
        cubies[i] = prod_mat_mat(scale(0.333, 0.333, 0.333), cubies[i]);

        // Place the cubie

        if (i < 9) {
            cubies[i] = prod_mat_mat(translate(0, 0, 0.405), cubies[i]);
        } else if (i >= 18) {
            cubies[i] = prod_mat_mat(translate(0, 0, -0.405), cubies[i]);
        }

        if (i % 9 == 0 || i % 9 == 1 || i % 9 == 2) {
            cubies[i] = prod_mat_mat(translate(0, 0.405, 0), cubies[i]);
        } else if (i % 9 == 6 || i % 9 == 7 || i % 9 == 8) {
            cubies[i] = prod_mat_mat(translate(0, -0.405, 0), cubies[i]);
        }

        if (i % 9 == 0 || i % 9 == 3 || i % 9 == 6) {
            cubies[i] = prod_mat_mat(translate(-0.405, 0, 0), cubies[i]);
        } else if (i % 9 == 2 || i % 9 == 5 || i % 9 == 8) {
            cubies[i] = prod_mat_mat(translate(0.405, 0, 0), cubies[i]);
        } 
    }
    get_normals(normals, n_v);
    GLuint program = initShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    ctm1_location = glGetUniformLocation(program, "ctm1");
    ctm2_location = glGetUniformLocation(program, "ctm2");
    lp_location = glGetUniformLocation(program, "lightPosition");
    eye_location = glGetUniformLocation(program, "eye");

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(normals), normals);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices)));

    GLuint vNormal = glGetAttribLocation(program, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices) + sizeof(colors)));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDepthRange(1,0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    update_ctm();

    glUniformMatrix4fv(ctm1_location, 1, GL_FALSE, (GLfloat *) &ctm1);
    glUniform4fv(lp_location, 1, (GLfloat *) &lightPosition);
    glUniform4fv(eye_location, 1, (GLfloat *) &vrp);

    get_lpos();

    for (int i = 0; i < n_c; i++) {
        if (i < 9) {
            for (int j = 0; j < 6; j++) {
                colors[j] = (vec4){0, .25, 0, 1};
            }
        } else {
            for (int j = 0; j < 24; j++) {
                colors[j] = (vec4){0.1, 0.1, 0.1, 1};
            }
        }
        if (i >= 18) {
            for (int j = 0; j < 6; j++) {
                colors[48+j] = (vec4){0, 0, 1, 1};
            }
        } else {
            for (int j = 0; j < 24; j++) {
                colors[48+j] = (vec4){0.1, 0.1, 0.1, 1};
            }
        }

        if (i % 9 == 0 || i % 9 == 1 || i % 9 == 2) {
            for (int j = 0; j < 6; j++) {
                colors[120+j] = (vec4){1, 1, 1, 1};
            }
        } else {
            for (int j = 0; j < 24; j++) {
                colors[120+j] = (vec4){0.1, 0.1, 0.1, 1};
            }
        }

        if (i % 9 == 6 || i % 9 == 7 || i % 9 == 8) {
            for (int j = 0; j < 6; j++) {
                colors[96+j] = (vec4){1, 1, 0, 1};
            }
        } else {
            for (int j = 0; j < 24; j++) {
                colors[96+j] = (vec4){0.1, 0.1, 0.1, 1};
            }
        }

        if (i % 9 == 0 || i % 9 == 3 || i % 9 == 6) {
            for (int j = 0; j < 6; j++) {
                colors[72+j] = (vec4){1, 0.35, 0, 1};
            }
        } else {
            for (int j = 0; j < 24; j++) {
                colors[72+j] = (vec4){0.1, 0.1, 0.1, 1};
            }
        }

        if (i % 9 == 2 || i % 9 == 5 || i % 9 == 8) {
            for (int j = 0; j < 6; j++) {
                colors[24+j] = (vec4){0.6, 0, 0, 1};
            }
        } else {
            for (int j = 0; j < 24; j++) {
                colors[24+j] = (vec4){0.1, 0.1, 0.1, 1};
            }
        }

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(colors), sizeof(normals), normals);
        glUniformMatrix4fv(ctm2_location, 1, GL_FALSE, (GLfloat *) &cubies[i]);
        glDrawArrays(GL_TRIANGLES, 0, n_v);
    }

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, n_v);
    // glDrawArrays(GL_TRIANGLES, n_v, 42);
    glutSwapBuffers();
}

void idle(void) {
	
    if (shuffle_state == 1) {
        if (animation_state == 0) {
            char next_turn = shuffles[shuffle_step];
            if (next_turn == 'f') rotate_front();
            if (next_turn == 'd') rotate_down();
            if (next_turn == 'l') rotate_left();
            if (next_turn == 'r') rotate_right();
            if (next_turn == 'u') rotate_up();
            if (next_turn == 'b') rotate_back();
            if (next_turn == 'F') rotate_front2();
            if (next_turn == 'D') rotate_down2();
            if (next_turn == 'L') rotate_left2();
            if (next_turn == 'R') rotate_right2();
            if (next_turn == 'U') rotate_up2();
            if (next_turn == 'B') rotate_back2();
            shuffle_step++;
            if (shuffle_step == 30) {
                shuffle_state = 0;
            }
        }
    }

	if(animation_state == 1){
		for(int i = 0; i<9; i++){
			cubies[front[i]] = prod_mat_mat(rotate_z(-PI/(2 * n_steps)), cubies[front[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    if(animation_state == 7){
		for(int i = 0; i<9; i++){
			cubies[front[i]] = prod_mat_mat(rotate_z(PI/(2 * n_steps)), cubies[front[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}

	if(animation_state == 3){
		for(int i = 0; i<9; i++){
			cubies[right[i]] = prod_mat_mat(rotate_x(-PI/(2 * n_steps)), cubies[right[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    if(animation_state == 9){
		for(int i = 0; i<9; i++){
			cubies[right[i]] = prod_mat_mat(rotate_x(PI/(2 * n_steps)), cubies[right[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}


	if(animation_state == 5){
		for(int i = 0; i<9; i++){
			cubies[up[i]] = prod_mat_mat(rotate_y(-PI/(2 * n_steps)), cubies[up[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    if(animation_state == 11){
		for(int i = 0; i<9; i++){
			cubies[up[i]] = prod_mat_mat(rotate_y(PI/(2 * n_steps)), cubies[up[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}

	if(animation_state == 4){
		for(int i = 0; i<9; i++){
			cubies[left[i]] = prod_mat_mat(rotate_x(PI/(2 * n_steps)), cubies[left[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    if(animation_state == 10){
		for(int i = 0; i<9; i++){
			cubies[left[i]] = prod_mat_mat(rotate_x(-PI/(2 * n_steps)), cubies[left[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}

	if(animation_state == 2){
		for(int i = 0; i<9; i++){
			cubies[back[i]] = prod_mat_mat(rotate_z(PI/(2 * n_steps)), cubies[back[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    if(animation_state == 8){
		for(int i = 0; i<9; i++){
			cubies[back[i]] = prod_mat_mat(rotate_z(-PI/(2 * n_steps)), cubies[back[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    

	if(animation_state == 6){
		for(int i = 0; i<9; i++){
			cubies[down[i]] = prod_mat_mat(rotate_y(PI/(2 * n_steps)), cubies[down[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}
    if(animation_state == 12){
		for(int i = 0; i<9; i++){
			cubies[down[i]] = prod_mat_mat(rotate_y(-PI/(2 * n_steps)), cubies[down[i]]);
		}
		animation_step++;
		if(animation_step == n_steps){
			animation_step = 0;
            animation_state = 0;
		}
	}

	// if(isShuffling){
	// 	int success = 0;
	// 	switch(randomSequence[currIndex]){
	// 		case 'f':
	// 			success = rotateFront();
	// 			if(success){
	// 				r_string_front();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'r':
	// 			success = rotateRight();			
	// 			if(success){
	// 				r_string_right();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'b':
	// 			success = rotateBack();				
	// 			if(success){
	// 				r_string_back();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'l':
	// 			success = rotateLeft();
	// 			if(success){
	// 				r_string_left();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'u':
	// 			success = rotateUp();
	// 			if(success){
	// 				r_string_up();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'd':
	// 			success = rotateDown();
	// 			if(success){
	// 				r_string_down();
	// 				currIndex++;
	// 			}
	// 			break;
	// 	}
	// 	if(currIndex == 30){
	// 		isShuffling = 0;
	// 		currIndex = 0;
	// 	}
	// }

	// if(isSolving){
	// 	int success = 0;
	// 	switch(solution[currIndex]){
	// 		case 'f':
	// 			success = rotateFront();
	// 			if(success){
	// 				r_string_front();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'r':
	// 			success = rotateRight();			
	// 			if(success){
	// 				r_string_right();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'b':
	// 			success = rotateBack();				
	// 			if(success){
	// 				r_string_back();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'l':
	// 			success = rotateLeft();
	// 			if(success){
	// 				r_string_left();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'u':
	// 			success = rotateUp();
	// 			if(success){
	// 				r_string_up();
	// 				currIndex++;
	// 			}
	// 			break;
	// 		case 'd':
	// 			success = rotateDown();
	// 			if(success){
	// 				r_string_down();
	// 				currIndex++;
	// 			}
	// 			break;
	// 	}
	// 	if(currIndex == solveNum){
	// 		isSolving = 0;
	// 		currIndex = 0;
	// 	}
	// }
	glutPostRedisplay();
}

void keyboard(unsigned char key, int mousex, int mousey)
{
    if(key == 'q')
    	exit(0);

    if(key == 'f'){
    	int success = rotate_front();
    }
    if(key == 'F'){
    	int success = rotate_front2();
    }
    if(key == 'r'){
    	int success = rotate_right();
    }
    if(key == 'R'){
    	int success = rotate_right2();
    }
    if(key == 'u'){
    	int success = rotate_up();
    }
    if(key == 'U'){
    	int success = rotate_up2();
    }
    if(key == 'l'){
    	int success = rotate_left();
    }
    if(key == 'L'){
    	int success = rotate_left2();
    }
    if(key == 'b'){
    	int success = rotate_back();
    }
    if(key == 'B'){
    	int success = rotate_back2();
    }
    if(key == 'd'){
    	int success = rotate_down();
    }
    if(key == 'D'){
    	int success = rotate_down2();
    }
    if(key == 's'){
    	int success = shuffle();
    }
    if(key == 'X'){
        lightPosition.x += LIGHT_MOVE_FACTOR;  
    }
    if(key == 'x'){
        lightPosition.x -= LIGHT_MOVE_FACTOR;
        printf("Light position:\n");
        print_vec(lightPosition);
    }
    if(key == 'Y'){
        lightPosition.y += LIGHT_MOVE_FACTOR;
        printf("Light position:\n");
        print_vec(lightPosition);
    }
    if(key == 'y'){
        lightPosition.y -= LIGHT_MOVE_FACTOR;
        printf("Light position:\n");
        print_vec(lightPosition);
    }
    if(key == 'Z'){
        lightPosition.z += LIGHT_MOVE_FACTOR;
        printf("Light position:\n");
        print_vec(lightPosition);
    }
    if(key == 'z'){
        lightPosition.z -= LIGHT_MOVE_FACTOR;
        printf("Light position:\n");
        print_vec(lightPosition);
    }
    if(key == 'e') {
        printf("Zoom in\n");
        view_radius -= 0.25;
    }
    if(key == 'E') {
        printf("Zoom out\n");
        view_radius += 0.25;
    }
    if(key == 'A') {
        printf("Base up\n");
        base_height += 0.5;
    }
    if(key == 'a') {
        printf("Base down\n");
        base_height -= 0.5;
    }
    glutPostRedisplay();
}

void special(unsigned char key, int mousex, int mousey)
{
    if(key == GLUT_KEY_UP) {
        printf("Up\n");
        view_phi -= 0.1;
        if (view_phi < 0.1) {
            view_phi = 0.1;
        }  
    }
    if(key == GLUT_KEY_DOWN) {
        printf("Down\n");
        view_phi += 0.1;
        if (view_phi > PI - 0.1) {
            view_phi = PI - 0.1;
        }
    }
    if(key == GLUT_KEY_LEFT) {
        printf("Left\n");
        view_theta += 0.1;
        if (view_theta >= 2*PI) {
            view_theta = 0;
        }
    }
    if(key == GLUT_KEY_RIGHT) {
        printf("Right\n");
        view_theta -= 0.1;
        if (view_theta < 0) {
            view_theta = 2*PI;
        }
    }
    glutPostRedisplay();
}

void update_ctm() {

    vrp = (vec4) {view_radius*sin(view_phi)*cos(view_theta), view_radius*cos(view_phi), view_radius*sin(view_phi)*sin(view_theta), 1.0};
    vec4 vup = {0.0, 1.0, 0.0, 1.0};
    vec4 n = prod_vec_scalar(vrp, -1);
    // print_vec(vrp);
    // print_vec(n);
    // print_vec(vup);

    mat4 vm = look_at(vrp, n, vup);
    mat4 p = frustrum(NEAR, FAR, RIGHT, TOP, LEFT, BOTTOM);
    ctm1 = prod_mat_mat(p, vm);
}

void mouse(int button, int state, int x, int y) {
    
    // printf("Mouse\n");
    // if (button == GLUT_LEFT_BUTTON) {
    //     // Rotation
    //     if (state == GLUT_DOWN) {
    //         printf("Click down @ %d, %d\n", x, y);
    //         down_success = get_ball(x, y, windowSize, windowSize, (vec4 *) &down_loc); // , &down_loc
    //         if (down_success) {
    //             printf("%f,%f,%f,%f\n", down_loc.x, down_loc.y, down_loc.z, down_loc.w);
    //         }
    //     } else if (state == GLUT_UP) {
    //         printf("Click up @ %d, %d\n", x, y);
    //         vec4 up_loc;
    //         if (down_success && get_ball(x, y, windowSize, windowSize, (vec4 *) &up_loc)) { //, &up_loc
    //             printf("Rotate\n");
    //             vec4 cross;
    //             vec4 origin = {0.0, 0.0, 0.0, 1.0};
    //             cross = normalize(cross_vec_vec(up_loc, down_loc));
    //             GLfloat theta = (magnitude(down_loc) * magnitude(up_loc))/dot_vec_vec(down_loc, up_loc);
    //             printf("%f,%f,%f,%f,%f\n", cross.x, cross.y, cross.z, cross.w, theta);
    //             ctm1 = prod_mat_mat(ctm1, rotate_v(cross, origin, theta * MOVE_FACTOR));
    //         }
    //     }
    // if (button == 3) {
    //     // Scroll up, zoom out
    //     printf("Zoom out\n");
    //     GLfloat z = ZOOM_FACTOR;
    //     ctm1 = prod_mat_mat(scale(z, z, z), ctm1);
    // } else if (button == 4) {
    //     // Scroll down, zoom in
    //     printf("Zoom in\n");
    //     GLfloat z = 1.0/ZOOM_FACTOR;
    //     ctm1 = prod_mat_mat(ctm1, scale(z, z, z));
    // }
    //     // Rerender
    //     glutPostRedisplay();
}

vec4 get_vector(int x, int y) {
    vec4 result;
    GLfloat xunit = (float) x / (float)windowSize;
    GLfloat yunit = (float) y / (float)windowSize;
    xunit = (xunit - 0.5) * 2;
    yunit = (yunit - 0.5) * 2;
    GLfloat zSquared = 1 - (xunit*xunit) - (yunit*yunit);

    result.x = xunit;
    result.y = yunit;
    result.z = sqrt(zSquared);
    result.w = 1;

    return result;
}

void reshape(int width, int height)
{
    glViewport(0, 0, windowSize, windowSize);
}

int main(int argc, char **argv) {
    windowSize = 512;
    get_edges(vertices, n_v, 1);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(windowSize, windowSize);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Project 4");
    glewInit();
    GLenum err = glGetError();
    init();
    glutIdleFunc(idle);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutSpecialFunc(special);
    
    glutMainLoop();

    return 0;
}

