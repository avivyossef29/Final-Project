#ifndef SYMNMF_H
#define SYMNMF_H
double** symnmf(double** W , double** H, int n, int k, int max_iter, double eps);
int calc_vectors_num(const char *file_path);
int calc_vector_size(const char *file_path);
double** process_txt(const char *file_path, int v_num, int v_size);
double** sym(double **matrix, int v_num, int v_size);
double** ddg(double **matrix, int v_num, int v_size);
double** norm(double **matrix, int v_num, int v_size);
double** symnmf(double** W , double** H, int n, int k, int max_iter, double eps);

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

void optimize_h(double** W, double** H, int n, int k, int max_iter, double eps);
double calc_H_entry(double** H, double** WH, double** HHtH, int i , int j);

#endif