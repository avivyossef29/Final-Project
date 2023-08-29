#include <stdio.h>

double** create_matrix(int,int);
void print_matrix(double**,int,int);
double** mal(double**,double**,int,int,int);


double** create_matrix(int n , int m){
    double * temp = (double*)malloc(n*m*sizeof(double));
    double** mat = (double**)malloc(n*sizeof(double*));
    if((mat == NULL) || (temp == NULL)) return;
    for(int i = 0 ; i < n ; i++){
        mat[i] = temp + m*i;
    }
    return mat;
}

void print_matrix(double** mat , int n , int m){
    for(int i = 0 ; i< n ; i++){
        for(int j = 0 ; j < m ; j++ ){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}
