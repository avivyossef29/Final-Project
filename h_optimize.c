#include "symnmf.h"
/* include "matric_op.c" 
 update H_i i,j  to H_i+1 i,j */

double calc_H_entry(double** H, double** WH, double** HHtH, int i , int j) {
    double res = H[i][j] * (0.5 + 0.5 * WH[i][j] / HHtH[i][j]);
    return res;
}

/* update H_1 to final H */

void optimize_h(double** W, double** H, int n, int k, int max_iter, double eps) {
    double **prev_H;
    double **WH, **HHtH;
    double delta ; 
    int iter = 1, i, j;
    do {
        prev_H = duplicate_matrix(H, n, k); /* you create every time a new MATRIX */ 
        WH = mul(W, H, n, n, k);
        HHtH = mul(mul(H, transpose(H, n, k), n, k, n), H, n, n, k);
        for (i = 0; i < n; i++) {
            for (j = 0; j < k; j++) {
                H[i][j] = calc_H_entry(H, WH, HHtH, i, j);
            }
        }
        delta = norm_matrix(sub_matrix(H, prev_H, n, k), n, k);
        delete_matrix(prev_H);
        iter++;
    } while ((iter <= max_iter) || (delta < eps));
}

