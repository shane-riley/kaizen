/* linalg.c
 * Purpose: for printing and manipulating vectors and square matrices of size '4'
 * Author: Shane Riley
 * Date: 9/12/2021
 * Class: CS_1566
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
