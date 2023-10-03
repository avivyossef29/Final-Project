import sys

import init_H
import numpy as np

EROR = 'eror'


# import symnmfmodule

# Read N vectors from a file
def process_txt(file_name):
    matrix = []
    with open(file_name, 'r') as file:
        for line in file:
            # Split each line into a list of values using ',' as the separator
            values = line.strip().split(',')
            # Convert the values from strings to floats
            row = [float(value) for value in values]
            matrix.append(row)
    return matrix


def print_matrix(matrix):
    for row in matrix:
        formatted_row = [f"{num:.4f}" for num in row]
        formatted_row_str = ",".join(formatted_row)
        print(formatted_row_str)


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
    np.random.seed(0)
    upper_bound = 2 * math.sqrt(entries_avg(W) / k)
    H = [[rand_float(0, upper_bound) for _ in range(k)] for _ in range(n)]
    return H



def main():
    assert (len(sys.argv) == 4)
    K = sys.argv[1]  # K is the number of clusters
    goal = sys.argv[2]
    file_path = sys.argv[3]
    matrix = process_txt(file_path)
    #print_matrix(matrix)
    if goal == "symnmf":
        # this method should receive W and initial H as arguments and return the final H
        W = norm()
        
        result = symnmf()  # this method should be defined in a C file
    elif goal == "sym":
        # this method should receive the data points matrix and return the similarity matrix
        result = sym(matrix, len(metrix), len(matrix[0]))  # this method should be defined in a C file
    elif goal == "ddg":
        # this method should receive the data points matrix and return the diagonal matrix D
        result = ddg()  # this method should be defined in a C file
    elif goal == "norm":
        # this method should receive the data points matrix and return the normalized similarity matrix
        result = norm()  # this method should be defined in a C file
    else:
        result = None
    
    if result is None:
        print(EROR)
        return
    
    else:
        print_matrix(result)
        return




main()