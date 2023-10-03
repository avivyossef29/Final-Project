#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "symnmf.h"

/*
double **create_matrix(int, int);

double *create_vector(int);

void print_matrix(double **, int, int);

void delete_matrix(double **);

double **mul(double **, double **, int, int, int);

double **sub_matrix(double **, double **, int, int);

double *sub_vector(const double *, const double *, int);

double norm_matrix(double **, int, int);

double norm_vector(double *, int);

double **transpose(double **, int, int);

double **calc_diagonal(double **, int, int);

double **calc_similarity(double **, int, int);

double **calc_normal_similarity_matrix(double **, int, int);

double **duplicate_matrix(double **A, int n, int m);
*/


/*
if u create a matrix or vector u should check it isn't NULL
I didn't test calc_similarity
*/


double **create_matrix(int n, int m) {
    int i = 0 ;
    double *temp = (double *) malloc(n * m * sizeof(double));
    double **mat = (double **) malloc(n * sizeof(double *));
    if ((mat == NULL) || (temp == NULL)) return NULL;
    for (i = 0; i < n; i++) {
        mat[i] = temp + m * i;
    }
    return mat;
}

double *create_vector(int n) {
    double *v = (double *) malloc(n * sizeof(double));
    return v;
}

void print_matrix(double **mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == m - 1) printf("%.4f\n", mat[i][j]);
            else printf("%.4f,", mat[i][j]);
        }
    }
}

void delete_matrix(double **mat) {
    free(mat[0]);
    free(mat);
}

 /* A is n*k and B is k*m */
double **mul(double **A, double **B, int n, int k, int m) {
    double temp;
    double **C = create_matrix(n, m);
    if (!C) return NULL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            temp = 0.0;
            for (int cnt = 0; cnt < k; cnt++) {
                temp += (A[i][cnt] * B[cnt][j]);
            }
            C[i][j] = temp;
        }
    }
    return C;
}

double **sub_matrix(double **A, double **B, int n, int m) {
    double **C = create_matrix(n, m);
    if (!C) return NULL;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

double *sub_vector(const double *v, const double *w, int n) {
    double *sub = create_vector(n);
    if (!sub) return NULL;
    for (int i = 0; i < n; i++) {
        sub[i] = v[i] - w[i];
    }
    return sub;
}


double norm_matrix(double **mat, int n, int m) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result += pow(mat[i][j], 2);
        }
    }
    return sqrt(result);
}

double norm_vector(double *v, int n) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += pow(v[i], 2);
    }
    return sqrt(result);
}

double **transpose(double **mat, int n, int m) {
    double **mat_t = create_matrix(m, n);
    if (!mat_t) return NULL;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            mat_t[i][j] = mat[j][i];
        }
    }
    return mat_t;

}

double **calc_diagonal(double **mat, int n, int m) {
    double **sym = calc_similarity(mat, n, m);
    double **diagonal = create_matrix(n, n);
    if (!diagonal) return NULL;
    double temp;
    for (int i = 0; i < n; i++) {
        temp = 0.0;
        for (int j = 0; j < n; j++) {
            temp += sym[i][j];
            diagonal[i][j] = 0.0;
        }
        diagonal[i][i] = temp;
    }
    delete_matrix(sym);
    return diagonal;
}


/* each vector x_i should be a row of mat */
double **calc_similarity(double **mat, int n, int m) {
    double **similarity = create_matrix(n, n);
    if (!similarity) return NULL;
    double *x_i_sub_x_j;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                similarity[i][j] = 0.0;
            } else {
                double *x_i = mat[i]; /* x_i is the i-th row of the matrix */
                double *x_j = mat[j]; /* x_j is the j-th row of the matrix */
                x_i_sub_x_j = sub_vector(x_i, x_j, m);
                if (!x_i_sub_x_j) return NULL;
                similarity[i][j] = exp((pow(norm_vector(x_i_sub_x_j, m), 2) / -2));
                free(x_i_sub_x_j);
            }
        }
    }
    return similarity;
}

/* in place */
void opposite_diagonal(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                mat[i][j] = 1 / mat[i][j];
            } else {
                mat[i][j] = 0;
            }
        }
    }
}

// in place
void **root_diagonal(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat[i][j] = sqrt(mat[i][j]);
        }
    }
    return NULL;
}


double **calc_normal_similarity_matrix(double **mat, int n, int m) {
    double **D = calc_diagonal(mat, n, m);
    if (!D) return NULL;
    opposite_diagonal(D, n);
    root_diagonal(D, n);
    double **A = calc_similarity(mat, n, m);
    if (!A) return NULL;
    /* create temp to free later */
    double **temp = mul(D, A, n, n, n);
    if (!temp) return NULL;
    double **W = mul(temp, D, n, n, n);
    delete_matrix(temp);
    delete_matrix(D);
    delete_matrix(A);
    return W;
}

/* returns a copy of matrix A */
double **duplicate_matrix(double **A, int n, int m) {
    double **copy = create_matrix(n, m);
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            copy[i][j] = A[i][j];
        }
    }
    return copy;
}