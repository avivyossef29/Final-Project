#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double** create_matrix(int,int);
void print_matrix(double**,int,int);
void delete_matrix(double**,int,int);
double** mul(double**,double**,int,int,int);
double** sub_matrix(double** , double** , int ,int);
double norm_matrix(double** , int ,int);
double** transpose(double** ,int,int);
double** calc_diagonal(double**,int,int);


double** create_matrix(int n , int m){
    double * temp = (double*)malloc(n*m*sizeof(double));
    double** mat = (double**)malloc(n*sizeof(double*));
    if((mat == NULL) || (temp == NULL)) return NULL;
    for(int i = 0 ; i < n ; i++){
        mat[i] = temp + m*i;
    }
    return mat;
}

void print_matrix(double** mat , int n , int m){
    for(int i = 0 ; i< n ; i++){
        for(int j = 0 ; j < m ; j++ ){
            printf("%f ",mat[i][j]);
        }
        printf("\n");
    }
}

void delete_matrix(double** mat,int n , int m ){
    free(mat[0]);
    free(mat);
}

// A is n*k and B is k*m 
double** mul(double** A,double** B , int n , int k , int m){
    double temp;
    double** C = create_matrix(n,m);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            temp = 0.0;
            for(int cnt = 0; cnt < k ; cnt++ ){
                temp += (A[i][cnt] * B[cnt][j]);
            }
            C[i][j] = temp;
        }
    }
    return C;
}

double** sub_matrix(double** A , double** B , int n ,int m){
    double** C = create_matrix(n,m);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < m ; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}


double norm_matrix(double** mat , int n ,int m){
    double result = 0;
    for(int i = 0 ; i < n ; i++ ){
        for(int j = 0 ; j < m ; j++){
            result += pow(mat[i][j] ,2);
        }
    }
    return sqrt(result);
}

double** transpose(double** mat ,int n ,int m){
    double** mat_t = create_matrix(m,n);
    for(int i = 0 ; i < n ; i++ ){
        for(int j = 0 ; j < m ; j++){
            mat_t[i][j] = mat[j][i];
        }
    }
    return mat_t;
    
}

double** calc_diagonal(double** mat ,int n ,int m){
    double** diagonal = create_matrix(n,m);
    double temp;
    for(int i = 0 ; i < n ; i++ ){
        temp = 0.0;
        for(int j = 0 ; j < m ; j++){
            temp += mat[i][j];
            diagonal[i][j] = 0.0;
        }
        diagonal[i][i] = temp;
    }
    return diagonal;
}