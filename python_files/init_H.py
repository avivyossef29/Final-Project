import math
import random
import sys
import numpy as np

np.random.seed(0)

def rand_float(lower_bound, upper_bound):
    return np.random.uniform(lower_bound, upper_bound)


def entries_avg(W):
    avg = 0
    n = len(W)
    for i in range(n):
        for j in range(n):
            avg += W[i][j]
    avg = avg / pow(n, 2)
    return avg


def init_H(W, n, k):
    upper_bound = 2 * math.sqrt(entries_avg(W) / k)
    H = [[rand_float(0, upper_bound) for _ in range(k)] for _ in range(n)]
    return H

def print_matrix(mat):
    for row in mat:
        print(row)

def main():
    matrix = [[1, 2, 3],
              [4, 5, 6],
              [7, 8, 9]]
    h = init_H(matrix, len(matrix), 3)
    print_matrix(h)


