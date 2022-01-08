/* linalg.h
 * Purpose: for printing and manipulating vectors and square matrices of size '4'
 * Author: Shane Riley
 * Date: 9/12/2021
 * Class: CS_1566
 * Lab 2
 */


// Header guards
#ifndef LINALG_H_
#define LINALG_H

#include <stdio.h>
#include <GL/freeglut.h>

// Type definitions

typedef struct {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
} vec4;

typedef struct {
	GLfloat x;
	GLfloat y;
} vec2;

typedef struct {
	vec4 x;
	vec4 y;
	vec4 z;
	vec4 w;
} mat4;

static const double PI = 3.141592654;

// Vector manipulations

/*
 * Function: sum_vec_vec
 * -------------------
 * adds a scalar to a vector
 *
 * v1: vec4 vector
 * 
 * v2: vec4 vector
 * 
 * Returns: vec4 sum
 */

vec4 sum_vec_vec(vec4 v1, vec4 v2);

/*
 * Function: diff_vec_vec
 * -------------------
 * subtracts one vector from another
 *
 * v1: vec4 minuend
 * 
 * v2: vec4 subtrahend
 * 
 * Returns: vec4 difference
 */

vec4 diff_vec_vec(vec4 v1, vec4 v2);

/*
 * Function: magnitude
 * -------------------
 * produces magnitude of a vector
 * 
 * v: vec4 vector
 * 
 * Returns: GLfloat magnitude
 */

GLfloat magnitude(vec4 v);

/*
 * Function: normalize
 * -------------------
 * produces normalized copy of vector
 * 
 * v: vec4 vector
 * 
 * Returns: vec4 normalized vector
 */

vec4 normalize(vec4 v);

/*
 * Function: prod_vec_scalar
 * -------------------
 * multiples a scalar to a vector
 * 
 * v: vec4 vector
 *
 * s: GLfloat scalar
 * 
 * Returns: vec4 product
 */

vec4 prod_vec_scalar(vec4 v, GLfloat s);

/*
 * Function: dot_vec_vec
 * -------------------
 * dot multiples a vector to a vector
 *
 * v1: vec4 vector
 * 
 * v2: vec4 vector
 * 
 * Returns: GlFloat product
 */

GLfloat dot_vec_vec(vec4 v1, vec4 v2);

/*
 * Function: cross_vec_vec
 * -------------------
 * cross multiples a vector to a vector
 *
 * v1: vec4 vector
 * 
 * v2: vec4 vector
 * 
 * Returns: vec4 product
 */

vec4 cross_vec_vec(vec4 v1, vec4 v2);


// Matrix manipulations

/*
 * Function: prod_mat_scalar
 * -------------------
 * multiples a scalar to a matrix
 *
 * m: mat4 matrix
 * 
 * s: GLfloat scalar
 * 
 * Returns: mat4 product
 */

mat4 prod_mat_scalar(mat4 m, GLfloat s);

/*
 * Function: sum_mat_mat
 * -------------------
 * adds a matrix to a matrix
 *
 * m1: mat4 matrix
 * 
 * m2: mat4 matrix
 * 
 * Returns: mat4 sum
 */

mat4 sum_mat_mat(mat4 m1, mat4 m2);

/*
 * Function: diff_mat_mat
 * -------------------
 * subtracts a matrix from a matrix
 *
 * m1: mat4 minuend matrix
 * 
 * m2: mat4 subtrahend matrix
 * 
 * Returns: mat4 difference
 */

mat4 diff_mat_mat(mat4 m1, mat4 m2);

/*
 * Function: prod_mat_mat
 * -------------------
 * multiplies a matrix a matrix to a matrix
 *
 * m1: mat4 matrix
 * 
 * m2: mat4 matrix
 * 
 * Returns: mat4 product
 */

mat4 prod_mat_mat(mat4 m1, mat4 m2);

/*
 * Function: prod_mat_vec
 * -------------------
 * multiplies a matrix with a vector
 *
 * m: mat4 matrix
 * 
 * v: vec4 vector
 * 
 * Returns: vec4 product
 */

vec4 prod_mat_vec(mat4 m, vec4 v);

/*
 * Function: transpose
 * -------------------
 * transposes a matrix
 *
 * m: mat4 matrix
 * 
 * Returns: mat4 transpose
 */

mat4 transpose(mat4 m);

/*
 * Function: determinant
 * -------------------
 * finds the determinant of a matrix
 *
 * m: mat4 matrix
 * 
 * Returns: GLfloat determinant
 */

GLfloat determinant(mat4 m);

/*
 * Function: inverse
 * -------------------
 * inverts a matrix using cramer's rule
 *
 * m: mat4 matrix
 * 
 * Returns: mat4 inverse
 */

mat4 inverse(mat4 m);

/*
 * Function: identity
 * -------------------
 * returns identity matrix
 * 
 * Returns: mat4 identity
 */

mat4 identity();

/*
 * Function: equals_vec
 * -------------------
 * Checks for vector equality
 *
 * v1: vec4 vector
 *
 * v2: vec4 vector
 *
 * Returns: 1 if equal, 0 if not
 */
int equals_vec(vec4 v1, vec4 v2);

// Printing functions

/*
 * Function: print_vec
 * -------------------
 * prints a vector to stdout
 *
 * v: vec4 vector
 */

void print_vec(vec4 v);

/*
 * Function: print_mat
 * -------------------
 * prints a vector to stdout
 *
 * m: mat4 matrix
 */

void print_mat(mat4 m);

// Transformation functions

/*
 * Function: translate
 * -------------------
 * Creates translation transformation matrix
 *
 * x: GLfloat deltax
 *
 * y: GLfloat deltay
 *
 * z: GLfloat deltaz
 *
 * Returns: mat4 transformation matrix
 */

mat4 translate(GLfloat x, GLfloat y, GLfloat z);

/*
 * Function: rotate_x
 * -------------------
 * Creates x-rotation transformation matrix
 *
 * theta: GLfloat angle to rotate
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_x(GLfloat theta);

/*
 * Function: rotate_y
 * -------------------
 * Creates y-rotation transformation matrix
 *
 * theta: GLfloat angle to rotate
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_y(GLfloat theta);

/*
 * Function: rotate_z
 * -------------------
 * Creates z-rotation transformation matrix
 *
 * theta: GLfloat angle to rotate
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_z(GLfloat theta);

/*
 * Function: scale
 * -------------------
 * Creates scaling transformation matrix
 *
 * x: GLfloat x scale
 *
 * y: GLfloat y scale
 *
 * z: GLfloat z scale
 *
 * Returns: mat4 transformation matrix
 */

mat4 scale(GLfloat x, GLfloat y, GLfloat z);

/*
 * Function: rotate_v
 * -------------------
 * Rotate about vector w.r.t center
 *
 * v: normalized direction
 *
 * p: center
 * 
 * Returns: mat4 transformation matrix
 */

mat4 rotate_v(vec4 v, vec4 p, GLfloat theta);

/*
 * Function: get_ball
 * -------------------
 * Gets normalized trackball vector from screen coordinates. Returns null if out of range
 *
 * int xi: x screen location
 * 
 * int yi: y screen location
 * 
 * int xv: x screen size
 * 
 * int yv: y screen size
 * 
 * vec4 *trackball: resultant vector
 *
 * Returns: 0 if failed, 1 if succeeded
 */

int get_ball(int xi, int yi, int xw, int yw, vec4 *v);

/*
 * Function: get_model
 * -------------------
 * Returns model matrix (gets from object to camera frame)
 *
 * vec4 n: normal vector to view plane
 *
 * vec4 vup: view-up vector
 * 
 * mat4: returned matrix
 */

mat4 get_model(vec4 n, vec4 vup);

/*
 * Function: get_view_model
 * -------------------
 * Returns view model matrix
 *
 * vec4 n: normal vector to view plane
 *
 * vec4 vup: view-up vector
 * 
 * vec4 vrp: view reference point
 * 
 * mat4: returned matrix
 */

mat4 get_view_model(vec4 n, vec4 vup, vec4 vrp);

/*
 * Function: get_perspective
 * -------------------
 * Returns view model matrix
 *
 * GLfloat near: near depth
 *
 * GLfloat far: far depth
 * 
 * GLfloat FOV: field of view
 * 
 * mat4: returned matrix
 */

mat4 get_perspective(GLfloat near, GLfloat far);

/*
 * Function: get_perspective
 * -------------------
 * Returns view model matrix
 *
 * GLfloat near: near depth
 *
 * GLfloat far: far depth
 * 
 * GLfloat FOV: field of view
 * 
 * mat4: returned matrix
 */

mat4 frustrum(GLfloat near, GLfloat far, GLfloat right, GLfloat top, GLfloat left, GLfloat bottom);

mat4 look_at(vec4 eye, vec4 at, vec4 up);

#endif /* LINALG_H_ */
