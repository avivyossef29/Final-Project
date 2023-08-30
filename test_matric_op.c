#include "matric_op.c"


int main(int argc, char* argv[]) {
    double** A = create_matrix(3,3);
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0; j<3; j++){
            A[i][j] = 3*i+j;
        }
    }
    print_matrix(A,3,3);
    double** A_2 = mul(A,A,3,3,3);
    print_matrix(A_2,3,3);
    double** zero = sub_matrix(A,A,3,3);
    print_matrix(zero,3,3);
    printf("%f\n" , norm_matrix(A,3,3));
    double** A_t = transpose(A,3,3);
    print_matrix(A_t,3,3);
    double** A_d = calc_diagonal(A,3);
    print_matrix(A_d,3,3);
    double** A_sym = calc_similarity(A,3);
    print_matrix(A_sym,3,3);
    double** A_n_sym = calc_normal_similarity_matrix(A,3);
    print_matrix(A_n_sym,3,3);

    delete_matrix(A);
    delete_matrix(A_2);
    delete_matrix(zero);
    delete_matrix(A_t);

    return 0;
}