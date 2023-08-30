import math
import random


def rand_float(lower_bound, upper_bound):
    return random.uniform(lower_bound, upper_bound)


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
