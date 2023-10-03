#include "symnmf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* include "matric_op.c" 
 update H_i i,j  to H_i+1 i,j */

double calc_H_entry(double** H, double** WH, double** HHtH, int i , int j) {
    double res = H[i][j] * (0.5 + 0.5 * WH[i][j] / HHtH[i][j]);
    return res;
}

/* update H_1 to final H */

void optimize_h(double** W, double** H, int n, int k, int max_iter, double eps) {
    double **WH, **HHtH , **Ht , **HHt , **sub;
    double delta ; 
    int iter = 0, i, j;
    double** next_H = create_matrix(n, k);

    do {
         /* you create every time a new MATRIX */ 
        WH = mul(W, H, n, n, k);
        Ht = transpose(H , n, k);
        HHt = mul(H,Ht,n,k,n);
        HHtH = mul(HHt, H, n, n, k);
        for (i = 0; i < n; i++) {
            for (j = 0; j < k; j++) {
                next_H[i][j] = calc_H_entry(H, WH, HHtH, i, j);
            }
        }
        delete_matrix(WH);
        delete_matrix(Ht);
        delete_matrix(HHt);
        delete_matrix(HHtH);
        /* debug*/
        sub = sub_matrix(H, next_H, n, k);
        delta = norm_matrix(sub,n,k);
        delete_matrix(sub);
        copy_matrix(next_H,H , n, k);
        iter++;

    } while ((iter < max_iter) && (pow(delta,2) > eps));
    delete_matrix(next_H);
}

