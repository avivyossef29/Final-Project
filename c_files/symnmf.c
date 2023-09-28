#include "matric_op.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int vectors_num, vector_size; /* vectors_num is the number of vectors and K is the dimension of each vector */

struct Node {
    double val;
    struct Node *next;
};

typedef struct Node Node;

Node *creat_node(double val) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("ֿ\nAn Error Has Occurred\n");
        exit(1);
    }
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

int calc_vectors_num(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("ֿ\nAn Error Has Occurred\n");
        exit(1);
    }
    /* Count the number of lines in the file (vectors_num) */
    int n = 0;
    char ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == '\n') n++;
    }
    fclose(file);
    return n;
}

int calc_vector_size(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if(file == NULL) {
        printf("ֿ\nAn Error Has Occurred\n");
        exit(1);
    }
    /* Calculate the size of each vector(K) */
    int k = 1;
    char ch;
    while (!feof(file)) {
        ch = fgetc(file);
        if (ch == ',') k++;
        else if (ch == '\n') break; /* Assuming all vectors are of the same size we can stop after the first one */
    }
    fclose(file);
    return k;
}

double** process_txt(const char *file_path, int v_num, int v_size) {
    FILE *file = fopen(file_path, "r");
    if(file == NULL) {
        printf("ֿ\nAn Error Has Occurred\n");
        exit(1);
    }
    double **matrix = create_matrix(v_num, v_size);
    if(matrix == NULL) {
        printf("ֿ\nAn Error Has Occurred\n");
        exit(1);
    }
    int i, j;
    for (i = 0; i < v_num; i++) {
        for (j = 0; j < v_size; j++) {
            /* For the last value in a row, use fscanf with newline as the separator */
            if (j == v_size - 1) fscanf(file, "%lf\n", &matrix[i][j]);
                /* For other values in a row, use fscanf with comma as the separator */
            else fscanf(file, "%lf,", &matrix[i][j]);
        }
    }
    return matrix;
}

double** sym(double **matrix, int v_num, int v_size) {
    return calc_similarity(matrix, v_num, v_size);
}

double** ddg(double **matrix, int v_num, int v_size) {
    return calc_diagonal(matrix, v_num, v_size);
}

double** norm(double **matrix, int v_num, int v_size) {
    return calc_normal_similarity_matrix(matrix, v_num, v_size);
}

int main(int argc, char *argv[]) {
    if (argc != 3) { /* we should receive file_path and a goal */
        printf("ֿ\nAn Error Has Occurred\n");
        exit(1);
    }
    char *file_path = argv[2]; /* file path is provided right after the goal */
    double **res_mat;
    vectors_num = calc_vectors_num(file_path);
    vector_size = calc_vector_size(file_path);
    double **matrix = process_txt(file_path, vectors_num, vector_size);
    if (strcmp(argv[1], "sym") == 0) {
        res_mat = sym(matrix, vectors_num, vector_size);
    } else if (strcmp(argv[1], "ddg") == 0) {
        res_mat = ddg(matrix, vectors_num, vector_size);
    } else if (strcmp(argv[1], "norm") == 0) {
        res_mat = norm(matrix, vectors_num, vector_size);
    } else { /* the given goal has to be one of the 3 defined goals */
            printf("ֿ\nAn Error Has Occurred\n");
            exit(1);
    }
    print_matrix(res_mat, vectors_num, vectors_num);
}