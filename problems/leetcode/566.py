# Reshape the Matrix
from typing import List
class Solution:
    def matrixReshape(self, mat: List[List[int]], r: int, c: int) -> List[List[int]]:
        # Size check
        m = len(mat)
        n = 0 if m == 0 else len(mat[0])
        if (r * c) != (m * n):
            return mat
        
        # Else
        new_mat = [[0]*c for _ in range(r)]
        # Loop through matrix index
        for i in range(r*c):
            m_i = i // n
            n_i = i % n
            r_i = i // c
            c_i = i % c
            new_mat[r_i][c_i] = mat[m_i][n_i]
        return new_mat
