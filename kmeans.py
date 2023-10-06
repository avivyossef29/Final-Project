import math
import sys

try:
    epsilon = 0.001
    n = 0  # vectors dimension


    def distance(v1: tuple, v2: tuple):
        sum = 0
        for i in range(len(v1)):
            sum += math.pow(v1[i] - v2[i], 2)
        return math.sqrt(sum)


    def find_cluster(clusters, v):
        min_distance = math.inf
        index = -1
        counter = 0
        for cluster in clusters:  # for i in range(k):
            curr_distance = distance(cluster[0], v)
            if curr_distance < min_distance:
                min_distance = curr_distance
                index = counter
            counter += 1
        return index


    def add_to_cluster(clusters, index, v):
        clusters[index][1].append(v)


    def add_vectors(v1: tuple, lis):
        for i in range(len(v1)):
            lis[i] = lis[i] + v1[i]


    def calc_uk(clusters, index):
        sum = [0.0 for i in range(n)]  # sum is zero vector
        k = len(clusters[index][1])  # k = num of members in the cluster
        if k == 0:
            return clusters[index][0]
        for vector in clusters[index][1]:
            add_vectors(vector, sum)
        for i in range(n):
            sum[i] = sum[i] / k
        return tuple(sum)

    k = int(sys.argv[1])
    if len(sys.argv) == 4:
        assert int(sys.argv[2]) < 1000, "Invalid maximum iteration!"
        max_iter = int(sys.argv[2])
        file_name = sys.argv[3]
    elif len(sys.argv) == 3:
        max_iter = 200
        file_name = sys.argv[2]
    else:
        print("An Error Has Occurred")
        sys.exit()

    f = open(file_name, "r")
    lines = f.readlines()
    assert k <= len(lines), "Invalid number of clusters!"
    vectors = [tuple(map(float, line.split(","))) for line in lines]
    n = len(vectors[0])
    clusters = [[vectors[i], []] for i in range(k)]
    valid = False

    while max_iter > 0 and (not valid):
        valid = True
        for vector in vectors:
            index = find_cluster(clusters, vector)
            add_to_cluster(clusters, index, vector)
        for i in range(len(clusters)):
            new_cluster = calc_uk(clusters, i)
            if valid:
                delta = distance(new_cluster, clusters[i][0])
                if delta > epsilon:
                    valid = False
            clusters[i] = [new_cluster, []]
        max_iter -= 1

    result = [cluster[0] for cluster in clusters]
    f.close()

    for i in range(len(result)):
        x = ""
        for j in range(len(result[i])):
            x += '%.4f' % (result[i][j])
            if j < (len(result[i]) - 1):
                x += ","
        print(x)

except:
    print("An Error Has Occurred")
