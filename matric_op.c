double** create_matrix(int,int);
double** mal(**double,**double,int,int,int);


double** create_matrix(int n , int m){
    temp = (double*)malloc(n*m*sizeof(double));
    mat = (double**)malloc(n*sizeof(double*));
    if((mat == NULL) || (temp == NULL)) return;
    for(int i = 0 ; i < n ; i++){
        mat[i] = temp + m*i;
    }
    return mat;
}