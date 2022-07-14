/* linalg.c
 * Purpose: for printing and manipulating vectors and square matrices of size '4'
 * Author: Shane Riley
 * Date: 9/12/2021
 * Class: gp
 * Lab 2
 */

#include <math.h>
#include <stdio.h>
#include "linalg.h"

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

vec4 sum_vec_vec(vec4 v1, vec4 v2) {
    vec4 v3;
    v3.x = v1.x + v2.x;
    v3.y = v1.y + v2.y;
    v3.z = v1.z + v2.z;
    v3.w = v1.w + v2.w;
    return v3;
}

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

vec4 diff_vec_vec(vec4 v1, vec4 v2) {
    vec4 v3;
    v3.x = v1.x - v2.x;
    v3.y = v1.y - v2.y;
    v3.z = v1.z - v2.z;
    v3.w = v1.w - v2.w;
    return v3;
}

/*
 * Function: magnitude
 * -------------------
 * produces magnitude of a vector
 * 
 * v: vec4 vector
 * 
 * Returns: GLfloat magnitude
 */

GLfloat magnitude(vec4 v) {
    return sqrt(pow(v.x, 2)
                + pow(v.y, 2)
                + pow(v.z, 2)
                + pow(v.w, 2));
}

/*
 * Function: normalize
 * -------------------
 * produces normalized copy of vector
 * 
 * v: vec4 vector
 * 
 * Returns: vec4 normalized vector
 */

vec4 normalize(vec4 v) {
    vec4 v2;
    GLfloat size = magnitude(v);
    v2.x = v.x / size;
    v2.y = v.y / size;
    v2.z = v.z / size;
    v2.w = v.w / size;
    return v2;
}

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

vec4 prod_vec_scalar(vec4 v, GLfloat s) {
    vec4 v2;
    v2.x = v.x * s;
    v2.y = v.y * s;
    v2.z = v.z * s;
    v2.w = v.w * s;
    return v2;
}

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

GLfloat dot_vec_vec(vec4 v1, vec4 v2) {
    return (
        v1.x * v2.x
      + v1.y * v2.y
      + v1.z * v2.z
      + v1.w * v2.w
    );
    
}

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

vec4 cross_vec_vec(vec4 v1, vec4 v2) {
    vec4 v3;
    v3.x = (v1.y * v2.z) - (v1.z * v2.y);
    v3.y = (v1.z * v2.x) - (v1.x * v2.z);
    v3.z = (v1.x * v2.y) - (v1.y * v2.x);
    v3.w = 0.0;
    return v3;
}


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

mat4 prod_mat_scalar(mat4 m, GLfloat s) {
    mat4 m2;
    m2.x.x = m.x.x * s;
    m2.x.y = m.x.y * s;
    m2.x.z = m.x.z * s;
    m2.x.w = m.x.w * s;
    m2.y.x = m.y.x * s;
    m2.y.y = m.y.y * s;
    m2.y.z = m.y.z * s;
    m2.y.w = m.y.w * s;
    m2.z.x = m.z.x * s;
    m2.z.y = m.z.y * s;
    m2.z.z = m.z.z * s;
    m2.z.w = m.z.w * s;
    m2.w.x = m.w.x * s;
    m2.w.y = m.w.y * s;
    m2.w.z = m.w.z * s;
    m2.w.w = m.w.w * s;
    return m2;
}

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

mat4 sum_mat_mat(mat4 m1, mat4 m2) {
    mat4 m3;
    m3.x.x = m1.x.x + m2.x.x;
    m3.x.y = m1.x.y + m2.x.y;
    m3.x.z = m1.x.z + m2.x.z;
    m3.x.w = m1.x.w + m2.x.w;
    m3.y.x = m1.y.x + m2.y.x;
    m3.y.y = m1.y.y + m2.y.y;
    m3.y.z = m1.y.z + m2.y.z;
    m3.y.w = m1.y.w + m2.y.w;
    m3.z.x = m1.z.x + m2.z.x;
    m3.z.y = m1.z.y + m2.z.y;
    m3.z.z = m1.z.z + m2.z.z;
    m3.z.w = m1.z.w + m2.z.w;
    m3.w.x = m1.w.x + m2.w.x;
    m3.w.y = m1.w.y + m2.w.y;
    m3.w.z = m1.w.z + m2.w.z;
    m3.w.w = m1.w.w + m2.w.w;
    return m3;
}

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

mat4 diff_mat_mat(mat4 m1, mat4 m2) {
    mat4 m3;
    m3.x.x = m1.x.x - m2.x.x;
    m3.x.y = m1.x.y - m2.x.y;
    m3.x.z = m1.x.z - m2.x.z;
    m3.x.w = m1.x.w - m2.x.w;
    m3.y.x = m1.y.x - m2.y.x;
    m3.y.y = m1.y.y - m2.y.y;
    m3.y.z = m1.y.z - m2.y.z;
    m3.y.w = m1.y.w - m2.y.w;
    m3.z.x = m1.z.x - m2.z.x;
    m3.z.y = m1.z.y - m2.z.y;
    m3.z.z = m1.z.z - m2.z.z;
    m3.z.w = m1.z.w - m2.z.w;
    m3.w.x = m1.w.x - m2.w.x;
    m3.w.y = m1.w.y - m2.w.y;
    m3.w.z = m1.w.z - m2.w.z;
    m3.w.w = m1.w.w - m2.w.w;
    return m3;
}

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

mat4 prod_mat_mat(mat4 m1, mat4 m2) {
    mat4 m3;
    m3.x.x = dot_vec_vec( (vec4) {m1.x.x, m1.y.x, m1.z.x, m1.w.x}, m2.x);
    m3.x.y = dot_vec_vec( (vec4) {m1.x.y, m1.y.y, m1.z.y, m1.w.y}, m2.x);
    m3.x.z = dot_vec_vec( (vec4) {m1.x.z, m1.y.z, m1.z.z, m1.w.z}, m2.x);
    m3.x.w = dot_vec_vec( (vec4) {m1.x.w, m1.y.w, m1.z.w, m1.w.w}, m2.x);
    m3.y.x = dot_vec_vec( (vec4) {m1.x.x, m1.y.x, m1.z.x, m1.w.x}, m2.y);
    m3.y.y = dot_vec_vec( (vec4) {m1.x.y, m1.y.y, m1.z.y, m1.w.y}, m2.y);
    m3.y.z = dot_vec_vec( (vec4) {m1.x.z, m1.y.z, m1.z.z, m1.w.z}, m2.y);
    m3.y.w = dot_vec_vec( (vec4) {m1.x.w, m1.y.w, m1.z.w, m1.w.w}, m2.y);
    m3.z.x = dot_vec_vec( (vec4) {m1.x.x, m1.y.x, m1.z.x, m1.w.x}, m2.z);
    m3.z.y = dot_vec_vec( (vec4) {m1.x.y, m1.y.y, m1.z.y, m1.w.y}, m2.z);
    m3.z.z = dot_vec_vec( (vec4) {m1.x.z, m1.y.z, m1.z.z, m1.w.z}, m2.z);
    m3.z.w = dot_vec_vec( (vec4) {m1.x.w, m1.y.w, m1.z.w, m1.w.w}, m2.z);
    m3.w.x = dot_vec_vec( (vec4) {m1.x.x, m1.y.x, m1.z.x, m1.w.x}, m2.w);
    m3.w.y = dot_vec_vec( (vec4) {m1.x.y, m1.y.y, m1.z.y, m1.w.y}, m2.w);
    m3.w.z = dot_vec_vec( (vec4) {m1.x.z, m1.y.z, m1.z.z, m1.w.z}, m2.w);
    m3.w.w = dot_vec_vec( (vec4) {m1.x.w, m1.y.w, m1.z.w, m1.w.w}, m2.w);
    return m3;
}

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

vec4 prod_mat_vec(mat4 m, vec4 v) {
    vec4 v2;
    v2.x = dot_vec_vec( (vec4) {m.x.x, m.y.x, m.z.x, m.w.x}, v);
    v2.y = dot_vec_vec( (vec4) {m.x.y, m.y.y, m.z.y, m.w.y}, v);
    v2.z = dot_vec_vec( (vec4) {m.x.z, m.y.z, m.z.z, m.w.z}, v);
    v2.w = dot_vec_vec( (vec4) {m.x.w, m.y.w, m.z.w, m.w.w}, v);
    return v2;
}

/*
 * Function: transpose
 * -------------------
 * transposes a matrix
 *
 * m: mat4 matrix
 * 
 * Returns: mat4 transpose
 */

mat4 transpose(mat4 m) {
    mat4 m2;
    m2.x.x = m.x.x;
    m2.x.y = m.y.x;
    m2.x.z = m.z.x;
    m2.x.w = m.w.x;
    m2.y.x = m.x.y;
    m2.y.y = m.y.y;
    m2.y.z = m.z.y;
    m2.y.w = m.w.y;
    m2.z.x = m.x.z;
    m2.z.y = m.y.z;
    m2.z.z = m.z.z;
    m2.z.w = m.w.z;
    m2.w.x = m.x.w;
    m2.w.y = m.y.w;
    m2.w.z = m.z.w;
    m2.w.w = m.w.w;
    return m2;
}

/*
 * Function: determinant
 * -------------------
 * finds the determinant of a matrix
 *
 * m: mat4 matrix
 * 
 * Returns: GLfloat determinant
 */

GLfloat determinant(mat4 m) {
    return (
        m.x.x * ((m.y.y * m.z.z * m.w.w) + (m.z.y * m.w.z * m.y.w) + (m.w.y * m.y.z * m.z.w)
                -(m.w.y * m.z.z * m.y.w) - (m.z.y * m.y.z * m.w.w) - (m.y.y * m.w.z * m.z.w))
      - m.x.y * ((m.y.x * m.z.z * m.w.w) + (m.z.x * m.w.z * m.y.w) + (m.w.x * m.y.z * m.z.w)
                -(m.w.x * m.z.z * m.y.w) - (m.z.x * m.y.z * m.w.w) - (m.y.x * m.w.z * m.z.w))
      + m.x.z * ((m.y.x * m.z.y * m.w.w) + (m.z.x * m.w.y * m.y.w) + (m.w.x * m.y.y * m.z.w)
                -(m.w.x * m.z.y * m.y.w) - (m.z.x * m.y.y * m.w.w) - (m.y.x * m.w.y * m.z.w))
      - m.x.w * ((m.y.x * m.z.y * m.w.z) + (m.z.x * m.w.y * m.y.z) + (m.w.x * m.y.y * m.z.z)
                -(m.w.x * m.z.y * m.y.z) - (m.z.x * m.y.y * m.w.z) - (m.y.x * m.w.y * m.z.z))
    );
}

/*
 * Function: inverse
 * -------------------
 * inverts a matrix using cramer's rule
 *
 * m: mat4 matrix
 * 
 * Returns: mat4 inverse
 */

mat4 inverse(mat4 m) {

    // Derivation courtesy of semath.info

    GLfloat det = determinant(m);

    mat4 m2;

    m2.x.x = ((m.y.y * m.z.z * m.w.w) + (m.z.y * m.w.z * m.y.w) + (m.w.y * m.y.z * m.z.w)
            -(m.w.y * m.z.z * m.y.w) - (m.z.y * m.y.z * m.w.w) - (m.y.y * m.w.z * m.z.w))/det;
    m2.x.y = ((m.w.y * m.z.z * m.x.w) + (m.z.y * m.x.z * m.w.w) + (m.x.y * m.w.z * m.z.w)
            -(m.x.y * m.z.z * m.w.w) - (m.z.y * m.w.z * m.x.w) - (m.w.y * m.x.z * m.z.w))/det;
    m2.x.z = ((m.x.y * m.y.z * m.w.w) + (m.y.y * m.w.z * m.x.w) + (m.w.y * m.x.z * m.y.w)
            -(m.w.y * m.y.z * m.x.w) - (m.y.y * m.x.z * m.w.w) - (m.x.y * m.w.z * m.y.w))/det;
    m2.x.w = ((m.z.y * m.y.z * m.x.w) + (m.y.y * m.x.z * m.z.w) + (m.x.y * m.z.z * m.y.w)
            -(m.x.y * m.y.z * m.z.w) - (m.y.y * m.z.z * m.x.w) - (m.z.y * m.x.z * m.y.w))/det;

    m2.y.x = ((m.w.x * m.z.z * m.y.w) + (m.z.x * m.y.z * m.w.w) + (m.y.x * m.w.z * m.z.w)
            -(m.y.x * m.z.z * m.w.w) - (m.z.x * m.w.z * m.y.w) - (m.w.x * m.y.z * m.z.w))/det;
    m2.y.y = ((m.x.x * m.z.z * m.w.w) + (m.z.x * m.w.z * m.x.w) + (m.w.x * m.x.z * m.z.w)
            -(m.w.x * m.z.z * m.x.w) - (m.z.x * m.x.z * m.w.w) - (m.x.x * m.w.z * m.z.w))/det;
    m2.y.z = ((m.w.x * m.y.z * m.x.w) + (m.y.x * m.x.z * m.w.w) + (m.x.x * m.w.z * m.y.w)
            -(m.x.x * m.y.z * m.w.w) - (m.y.x * m.w.z * m.x.w) - (m.w.x * m.x.z * m.y.w))/det;
    m2.y.w = ((m.x.x * m.y.z * m.z.w) + (m.y.x * m.z.z * m.x.w) + (m.z.x * m.x.z * m.y.w)
            -(m.z.x * m.y.z * m.x.w) - (m.y.x * m.x.z * m.z.w) - (m.x.x * m.z.z * m.y.w))/det;

    m2.z.x = ((m.y.x * m.z.y * m.w.w) + (m.z.x * m.w.y * m.y.w) + (m.w.x * m.y.y * m.z.w)
            -(m.w.x * m.z.y * m.y.w) - (m.z.x * m.y.y * m.w.w) - (m.y.x * m.w.y * m.z.w))/det;
    m2.z.y = ((m.w.x * m.z.y * m.x.w) + (m.z.x * m.x.y * m.w.w) + (m.x.x * m.w.y * m.z.w)
            -(m.x.x * m.z.y * m.w.w) - (m.z.x * m.w.y * m.x.w) - (m.w.x * m.x.y * m.z.w))/det;
    m2.z.z = ((m.x.x * m.y.y * m.w.w) + (m.y.x * m.w.y * m.x.w) + (m.w.x * m.x.y * m.y.w)
            -(m.w.x * m.y.y * m.x.w) - (m.y.x * m.x.y * m.w.w) - (m.x.x * m.w.y * m.y.w))/det;
    m2.z.w = ((m.z.x * m.y.y * m.x.w) + (m.y.x * m.x.y * m.z.w) + (m.x.x * m.z.y * m.y.w)
            -(m.x.x * m.y.y * m.z.w) - (m.y.x * m.z.y * m.x.w) - (m.z.x * m.x.y * m.y.w))/det;

    m2.w.x = ((m.w.x * m.z.y * m.y.z) + (m.z.x * m.y.y * m.w.z) + (m.y.x * m.w.y * m.z.z)
            -(m.y.x * m.z.y * m.w.z) - (m.z.x * m.w.y * m.y.z) - (m.w.x * m.y.y * m.z.z))/det;
    m2.w.y = ((m.x.x * m.z.y * m.w.z) + (m.z.x * m.w.y * m.x.z) + (m.w.x * m.x.y * m.z.z)
            -(m.w.x * m.z.y * m.x.z) - (m.z.x * m.x.y * m.w.z) - (m.x.x * m.w.y * m.z.z))/det;
    m2.w.z = ((m.w.x * m.y.y * m.x.z) + (m.y.x * m.x.y * m.w.z) + (m.x.x * m.w.y * m.y.z)
            -(m.x.x * m.y.y * m.w.z) - (m.y.x * m.w.y * m.x.z) - (m.w.x * m.x.y * m.y.z))/det;
    m2.w.w = ((m.x.x * m.y.y * m.z.z) + (m.y.x * m.z.y * m.x.z) + (m.z.x * m.x.y * m.y.z)
            -(m.z.x * m.y.y * m.x.z) - (m.y.x * m.x.y * m.z.z) - (m.x.x * m.z.y * m.y.z))/det;
    return m2;
}

/*
 * Function: identity
 * -------------------
 * returns identity matrix
 * 
 * Returns: mat4 identity
 */

mat4 identity() {
    mat4 m ={{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {0.0, 0.0, 0.0, 1.0}};
    return m;
}

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
int equals_vec(vec4 v1, vec4 v2) {
    return (v1.x == v2.x
            && v1.y == v2.y
            && v1.z == v2.z
            && v1.w == v2.w);
}

// Printing functions

/*
 * Function: print_vec
 * -------------------
 * prints a vector to stdout
 *
 * v: vec4 vector
 */

void print_vec(vec4 v) {
    printf("[%10.4f%10.4f%10.4f%10.4f]\n", v.x, v.y, v.z, v.w);
}

/*
 * Function: print_mat
 * -------------------
 * prints a vector to stdout
 *
 * m: mat4 matrix
 */

void print_mat(mat4 m) {
    print_vec( (vec4) {m.x.x, m.y.x, m.z.x, m.w.x});
    print_vec( (vec4) {m.x.y, m.y.y, m.z.y, m.w.y});
    print_vec( (vec4) {m.x.z, m.y.z, m.z.z, m.w.z});
    print_vec( (vec4) {m.x.w, m.y.w, m.z.w, m.w.w});
}

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

mat4 translate(GLfloat dx, GLfloat dy, GLfloat dz) {
    mat4 ctm ={{1.0, 0.0, 0.0, 0.0},
            {0.0, 1.0, 0.0, 0.0},
            {0.0, 0.0, 1.0, 0.0},
            {dx, dy, dz, 1.0}};
    return ctm;
}

/*
 * Function: rotate_x
 * -------------------
 * Creates x-rotation transformation matrix
 *
 * theta: GLfloat angle to rotate
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_x(GLfloat theta) {
    mat4 ctm = {{1.0, 0.0, 0.0, 0.0},
                {0.0, cos(theta), sin(theta), 0.0},
                {0.0, -sin(theta), cos(theta), 0.0},
                {0.0, 0.0, 0.0, 1.0}};
    return ctm;
}

/*
 * Function: rotate_y
 * -------------------
 * Creates y-rotation transformation matrix
 *
 * theta: GLfloat angle to rotate
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_y(GLfloat theta) {
    mat4 ctm = {{cos(theta), 0.0, -sin(theta), 0.0},
                {0.0, 1.0, 0.0, 0.0},
                {sin(theta), 0.0, cos(theta), 0.0},
                {0.0, 0.0, 0.0, 1.0}};
    return ctm;
}

/*
 * Function: rotate_z
 * -------------------
 * Creates z-rotation transformation matrix
 *
 * theta: GLfloat angle to rotate
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_z(GLfloat theta) {
    mat4 ctm = {{cos(theta), sin(theta), 0.0, 0.0},
                {-sin(theta), cos(theta), 0.0, 0.0},
                {0.0, 0.0, 1.0, 0.0},
                {0.0, 0.0, 0.0, 1.0}};
    return ctm;
}

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

mat4 scale(GLfloat dx, GLfloat dy, GLfloat dz) {
    mat4 ctm = {{dx, 0.0, 0.0, 0.0},
                {0.0, dy, 0.0, 0.0},
                {0.0, 0.0, dz, 0.0},
                {0.0, 0.0, 0.0, 1.0}};
    return ctm;
}

/*
 * Function: rotate_v
 * -------------------
 * Rotate about vector (assumed about 0,0,0)
 *
 * v: normalized direction
 * 
 * p: center location
 *
 * Returns: mat4 transformation matrix
 */

mat4 rotate_v(vec4 v, vec4 p, GLfloat theta) {
    mat4 ctm, T_in, T_out, R_x_in, R_y_in, R_x_out, R_y_out, R_z;
    GLfloat theta_x, theta_y, theta_z, d;

    v = normalize(v);

    // Get the thetas
    d = sqrt(pow(v.y, 2) + pow(v.z, 2));
    theta_x = asin(v.y / d);
    theta_y = asin(v.x);
    theta_z = theta;
    // printf("%f, %f, %f\n", theta_x, theta_y, theta_z);
    T_in = translate(p.x, p.y, p.z);
    T_out = translate(-p.x, -p.y, -p.z);
    R_x_in = rotate_x(theta_x);
    R_x_out = rotate_x(-theta_x);
    R_y_in = rotate_y(theta_y);
    R_y_out = rotate_y(-theta_y);
    R_z = rotate_z(theta_z);
    
    // Multiply the matrices
    ctm = prod_mat_mat(T_in, R_x_in);
    ctm = prod_mat_mat(ctm, R_y_in);
    ctm = prod_mat_mat(ctm, R_z);
    ctm = prod_mat_mat(ctm, R_y_out);
    ctm = prod_mat_mat(ctm, R_x_out);
    ctm = prod_mat_mat(ctm, T_out);

    return ctm;
}

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

int get_ball(int xi, int yi, int xw, int yw, vec4 *v) {
    GLfloat a = xw / 2.0;
    GLfloat b = yw / 2.0;
    GLfloat x, y, r, z;

    // Shift and normalize
    x = ((GLfloat) xi - a) / a;
    y = ((GLfloat) yi - b) / b;

    // Get circle radius
    r = sqrt(pow(x, 2) + pow(y, 2));

    if (r > 1) {
        // Outside of trackball
        // printf("%f %f %f -1.0\n", x, y, r);
        return 0;
    } else {
        // Inside of trackball
        z = sqrt(1 - pow(r, 2));
        // printf("%f %f %f %f\n", x, y, r, z);
        (*v).x = x;
        (*v).y = y;
        (*v).z = z;
        (*v).w = 1.0;
        return 1;
    }
}

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

mat4 get_model(vec4 n, vec4 vup) {
    
    vec4 v = diff_vec_vec(vup, prod_vec_scalar(n, dot_vec_vec(n, vup)/dot_vec_vec(n,n)));
    vec4 u = cross_vec_vec(v, n);

    vec4 un = normalize(u);
    vec4 vn = normalize(v);
    vec4 nn = normalize(n);

    mat4 M = { 
        {un.x, vn.x, nn.x, 0.0},
        {un.y, vn.y, nn.y, 0.0},
        {un.z, vn.z, nn.z, 0.0},
        {0.0, 0.0, 0.0, 1.0}
    };
    return M;
}

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

mat4 get_view_model(vec4 n, vec4 vup, vec4 vrp) {
    
    mat4 M = get_model(n, vup);
    vec4 vrpp = prod_vec_scalar(vrp,-1.0);
    mat4 T = translate(vrpp.x, vrpp.y, vrpp.z);
    return prod_mat_mat(M, T);
}

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

mat4 get_perspective(GLfloat near, GLfloat far){

    mat4 M = {
        {1, 0.0, 0.0, 0.0},
        {0.0, 1, 0.0, 0.0},
        {0.0, 0.0, (near+far)/(far-near), -1.0},
        {0.0, 0.0, -2.0*(near*far)/(far-near), 0.0}
    };
    return M;
}

mat4 look_at(vec4 eye, vec4 at, vec4 up)
{
	mat4 m;
	vec4 n, u, v;

	n = diff_vec_vec(eye, at);
	GLfloat nMag = magnitude(n);
	n = prod_vec_scalar(n, 1/nMag);

	//if(up.x == n.x && up.y == n.y && up.z == n.z){ //if looking straight down
	//	u = (vec4){1, 0, 0, 0};
	//}
	//else{
		u = cross_vec_vec(up, n);
		GLfloat uMag = magnitude(u);
		u = prod_vec_scalar(u, 1/uMag);
	//}


	v = cross_vec_vec(n, u);
	GLfloat vMag = magnitude(v);
	v = prod_vec_scalar(v, 1/vMag);

	m.x.x = u.x;	m.y.x = u.y;	m.z.x = u.z;	m.w.x = 0;
	m.x.y = v.x;	m.y.y = v.y;	m.z.y = v.z;	m.w.y = 0;
	m.x.z = n.x;	m.y.z = n.y;	m.z.z = n.z;	m.w.z = 0;
	m.x.w = eye.x;	m.y.w = eye.y;	m.z.w = eye.z;	m.w.w = 1;

	m = transpose(m);
	m = inverse(m);
	return m;
}

/*
 * Function: frustrum
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

mat4 frustrum(GLfloat near, GLfloat far, GLfloat right, GLfloat top, GLfloat left, GLfloat bottom) {
    return (mat4) {{-2*near/(right-left), 0.0, 0.0, 0.0},
                    {0.0, -2*near/(top-bottom), 0.0, 0.0},
                    {(left+right)/(right-left), (bottom+top)/(top-bottom), (near+far)/(far-near), -1.0},
                    {0.0, 0.0, -2*(near*far)/(far-near), 0.0}};
}

