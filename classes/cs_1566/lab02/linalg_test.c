/* linalg_test.c
 * Purpose: For testing the linalg library
 * Author: Shane Riley
 * Date: 9/12/2021
 * Class: CS_1566
 * Lab 2
 */

#include "linalg.h"
#include <stdio.h>

int main() {

    // Definitions from lab 2

    GLfloat s = 3.0;
    vec4 v1 = {1, 2, 3, 4};
    vec4 v2 = {5, 6, 7, 8};
    mat4 m1 = { {1, -5, 9,  13},
                {2, 6,  -10,14},
                {3, 7,  11, 15},
                {4, 8,  12, -16}};
    mat4 m2 = { {4, 8,  12, 16},
                {3, 7,  11, 15},
                {2, 6,  10, 14},
                {1, 5,  9,  13}};
    
    GLfloat sr;
    vec4 vr;
    mat4 mr;
    
    // Print inputs

    printf("s = \n%.4f\n", s);
    printf("v1 =\n");
    print_vec(v1);
    printf("v2 =\n");
    print_vec(v2);
    printf("m1 =\n");
    print_mat(m1);
    printf("m2 =\n");
    print_mat(m2);
    printf("\n");

    // Test vector ops

    // Vector Scalar mult
    printf("s * v1 =\n");
    vr = prod_vec_scalar(v1, s);
    print_vec(vr);

    // Vector add
    printf("v1 + v2 =\n");
    vr = sum_vec_vec(v1, v2);
    print_vec(vr);

    // Vector subtract
    printf("v1 - v2 =\n");
    vr = diff_vec_vec(v1, v2);
    print_vec(vr);

    // Vector magnitude
    printf("|v1| =\n");
    sr = magnitude(v1);
    printf("%.4f\n", sr);

    // Vector normalize
    printf("v1 normalized =\n");
    vr = normalize(v1);
    print_vec(vr);

    // Vector dot product
    printf("v1 dot v2 =\n");
    sr = dot_vec_vec(v1, v2);
    printf("%.4f\n", sr);

    // Vector cross product
    printf("v1 cross v2 =\n");
    vr = cross_vec_vec(v1, v2);
    print_vec(vr);

    // Test Matrix ops

    // Matrix Scalar mult
    printf("s * m1 =\n");
    mr = prod_mat_scalar(m1, s);
    print_mat(mr);

    // Matrix add
    printf("m1 + m2 =\n");
    mr = sum_mat_mat(m1, m2);
    print_mat(mr);

    // Matrix subtract
    printf("m1 - m2 =\n");
    mr = diff_mat_mat(m1, m2);
    print_mat(mr);

    // Matrix Matrix mult
    printf("m1 * m2 =\n");
    mr = prod_mat_mat(m1, m2);
    print_mat(mr);

    // Inverse
    printf("m1 inverse =\n");
    mr = inverse(m1);
    print_mat(mr);

    // Transpose
    printf("m1 transpose =\n");
    mr = transpose(m1);
    print_mat(mr);

    // Matrix Vector mult
    printf("m1 * v1 =\n");
    vr = prod_mat_vec(m1, v1);
    print_vec(vr);
}