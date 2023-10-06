
import symnmfapi
import sys
from sklearn.metrics import silhouette_score
import pandas as pd
import subprocess
import math
import numpy as np 

EROR = "An Error Has Occurred"

def calc_distance(v1, v2):
    sum = 0
    for i in range(len(v1)):
        sum += math.pow(v1[i] - v2[i], 2)
    return math.sqrt(sum)

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

def create_lables(data,centroids):
    min = -1
    distance = -1
    result = [None for i in range(len(data))]
    for index_data , vector_data in enumerate(data):
        min = sys.maxsize
        for index_centroid , vector_centroid in enumerate(centroids):
            distance = calc_distance(vector_data,vector_centroid)
            if distance < min:
                result[index_data] = index_centroid
                min = distance
    return result

    

try:
    assert len(sys.argv) == 3
    k , file_name , max_iter = sys.argv[1] ,sys.argv[2] , 300

    mat_kmeans =subprocess.run(['python3', 'kmeans.py', k, '300', file_name], 
                                                stdout=subprocess.PIPE, universal_newlines=True).stdout.split()
    mat_kmeans = [ list(map(float,mat_kmeans[i].split(','))) for i in range(len(mat_kmeans))]

    mat_symnmf  = subprocess.run(['python3', 'symnmf.py', k,'symnmf', file_name], stdout=subprocess.PIPE, universal_newlines=True).stdout.split()
    mat_symnmf = [ list(map(float,mat_symnmf[i].split(','))) for i in range(len(mat_symnmf))]

    npH = np.array(mat_symnmf)
    symnmf_array = np.argmax(npH, axis=1)
    data = process_txt(file_name)
    lable_kmeans = np.array(create_lables(data,mat_kmeans))
    kmeans_score  = "{:.4f}".format(silhouette_score(data , lable_kmeans))
    symnmf_score = "{:.4f}".format(silhouette_score(data, symnmf_array)) 
    print(f"nmf: {symnmf_score}")
    print(f"kmeans: {kmeans_score}")

except:
    print(EROR)


