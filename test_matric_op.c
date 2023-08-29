
#include "matric_op.c"


void main(int argc , char* argv){
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

    delete_matrix(A,3,3);
    delete_matrix(A_2,3,3);
    delete_matrix(zero,3,3);
    delete_matrix(A_t,0,0);
}