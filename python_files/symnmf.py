import sys

import init_H
import numpy as np


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


def main():
    assert (len(sys.argv) == 4)
    K = sys.argv[1]  # K is the number of clusters
    goal = sys.argv[2]
    file_path = sys.argv[3]
    matrix = process_txt(file_path)
    print_matrix(matrix)
    if goal == "symnmf":
        # this method should receive W and initial H as arguments and return the final H
        symnmf()  # this method should be defined in a C file
    elif goal == "sym":
        # this method should receive the data points matrix and return the similarity matrix
        sym()  # this method should be defined in a C file
    elif goal == "ddg":
        # this method should receive the data points matrix and return the diagonal matrix D
        ddg()  # this method should be defined in a C file
    elif goal == "norm":
        # this method should receive the data points matrix and return the normalized similarity matrix
        norm()  # this method should be defined in a C file


main()
