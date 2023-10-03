# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include "matric_op.c"
#include "symnmf.c"


double **py_to_c(Pyobject* old_py , int n , int m){
    double ** c_mat;
    c_mat = create_matrix(n,m);
    if (c_mat == NULL) return NULL;
    PyObject *curr_v;
    int i, j;
    for (i = 0; i < n; i++) {
        curr_v = PyList_GetItem(mat, i);
        for (j = 0; j < v_size; j++) {
            c_mat[i][j] = PyFloat_AsDouble(PyList_GetItem(curr_v, j));
        }
    }
    return c_mat;
}

Pyobject* c_to_py(double** old_c , int n , int m){
    PyObject *res;
    new_py = PyList_New(n);
    for (i = 0; i < n; i++) {
        curr_v = PyList_New(m);
        for (j = 0; j < m; j++) {
            PyList_SetItem(curr_v, j, Py_BuildValue("d", old_c[i][j]));
        }
        PyList_SetItem(res, i, curr_v);
    }
    return new_py;

}

/* symnmf wrapper */
static PyObject *symnmf(PyObject *self, PyObject *args) {
    PyObject *H;
    PyObject *W;
    int n; 
    int k;
    int max_iter;
    int eps

    /* This parses the Python arguments into C arguments */
    if (!PyArg_ParseTuple(args, "OOiiii", &W,&H &n, &k,&max_iter,&eps)) {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
    }
    /* create a new H_c matrix */
    double ** H_c_mat = py_to_c(H,n,k);
    if (H_c_mat == NULL) return NULL;
    double ** W_c_mat = py_to_c(W,n,n);
    if (W_c_mat == NULL) return NULL;
    symnmf(W_c , H_c , int n, int k, int max_iter, double eps);
    PyObject* result = c_to_py(H_c,n,k)
    delete_matrix(H_c);
    delete_matrix(W_c);
    return result;
}

/* sym wrapper */
static PyObject *sym(PyObject *self, PyObject *args) {
    PyObject *mat;
    int v_num;
    int v_size;
    /* This parses the Python arguments into C arguments */
    if (!PyArg_ParseTuple(args, "Oii", &mat, &v_num, &v_size)) {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
    }
    /* create a new C matrix */
    double **c_mat;
    c_mat = create_matrix(v_num, v_size);
    if (c_mat == NULL) return NULL;
    /* populate the C matrix with the data from the Python matrix */
    PyObject *curr_v;
    int i, j;
    for (i = 0; i < v_num; i++) {
        curr_v = PyList_GetItem(mat, i);
        for (j = 0; j < v_size; j++) {
            c_mat[i][j] = PyFloat_AsDouble(PyList_GetItem(curr_v, j));
        }
    }
    /* calculate the similarity matrix */
    double **sym_mat;
    sym_mat = sym(c_mat, v_num, v_size);
    /* This parses the C arguments into Python arguments */
    PyObject *res;
    res = PyList_New(v_num);
    for (i = 0; i < v_num; i++) {
        curr_v = PyList_New(vec_num);
        for (j = 0; j < vec_num; j++) {
            PyList_SetItem(curr_v, j, Py_BuildValue("d", sym_mat[i][j]));
        }
        PyList_SetItem(res, i, curr_v);
    }
    delete_matrix(c_mat);
    delete_matrix(sym_mat);
    return res;
}

/* ddg wrapper */
static PyObject *ddg(PyObject *self, PyObject *args) {
    PyObject *mat;
    int v_num;
    int v_size;
    /* This parses the Python arguments into C arguments */
    if (!PyArg_ParseTuple(args, "Oii", &mat, &v_num, &v_size)) {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
    }
    /* create a new C matrix */
    double **c_mat;
    c_mat = create_matrix(v_num, v_size);
    if (c_mat == NULL) return NULL;
    /* populate the C matrix with the data from the Python matrix */
    PyObject *curr_v;
    int i, j;
    for (i = 0; i < v_num; i++) {
        curr_v = PyList_GetItem(mat, i);
        for (j = 0; j < v_size; j++) {
            c_mat[i][j] = PyFloat_AsDouble(PyList_GetItem(curr_v, j));
        }
    }
    /* calculate the ddg matrix */
    double **ddg_mat;
    ddg_mat = ddg(c_mat, v_num, v_size);
    /* This parses the C arguments into Python arguments */
    PyObject *res;
    res = PyList_New(v_num);
    for (i = 0; i < v_num; i++) {
        curr_v = PyList_New(vec_num);
        for (j = 0; j < vec_num; j++) {
            PyList_SetItem(curr_v, j, Py_BuildValue("d", ddg_mat[i][j]));
        }
        PyList_SetItem(res, i, curr_v);
    }
    delete_matrix(c_mat);
    delete_matrix(ddg_mat);
    return res;
}

/* norm wrapper */
static PyObject *norm(PyObject *self, PyObject *args) {
    PyObject *mat;
    int v_num;
    int v_size;
    /* This parses the Python arguments into C arguments */
    if (!PyArg_ParseTuple(args, "Oii", &mat, &v_num, &v_size)) {
        return NULL; /* In the CPython API, a NULL value is never valid for a
                        PyObject* so it is used to signal that an error has occurred. */
    }
    /* create a new C matrix */
    double **c_mat;
    c_mat = create_matrix(v_num, v_size);
    if (c_mat == NULL) return NULL;
    /* populate the C matrix with the data from the Python matrix */
    PyObject *curr_v;
    int i, j;
    for (i = 0; i < v_num; i++) {
        curr_v = PyList_GetItem(mat, i);
        for (j = 0; j < v_size; j++) {
            c_mat[i][j] = PyFloat_AsDouble(PyList_GetItem(curr_v, j));
        }
    }
    /* calculate the similarity matrix */
    double **norm_mat;

    norm_mat = norm(c_mat, v_num, v_size);  //* wtf

    /* This parses the C arguments into Python arguments */
    PyObject *res;
    res = PyList_New(v_num);
    for (i = 0; i < v_num; i++) {
        curr_v = PyList_New(vec_num);
        for (j = 0; j < vec_num; j++) {
            PyList_SetItem(curr_v, j, Py_BuildValue("d", norm_mat[i][j]));
        }
        PyList_SetItem(res, i, curr_v);
    }
    delete_matrix(c_mat);
    delete_matrix(norm_mat);
    return res;
}

static PyMethodDef symnmfMethods[] = {{"symnmf", (PyCFunction) symnmf, METH_VARARGS, PyDoc_STR("Performs the symNMF algorithm and returns the optimized H. The function expects: initialized H, initialized W, ... COMPLETE")},
                                      {"sym", (PyCFunction) sym, METH_VARARGS, PyDoc_STR("Calculates and returns the similarity matrix. The function expects: vectors matrix or size n x m, int n, int m")},
                                      {"ddg", (PyCFunction) ddg, METH_VARARGS, PyDoc_STR("Calculates and returns the diagonal matrix. The function expects: vectors matrix or size n x m, int n, int m")},
                                      {"norm", (PyCFunction) norm, METH_VARARGS, PyDoc_STR("Calculates and returns the normalized similarity matrix. The function expects: vectors matrix or size n x m, int n, int m")},
                                      {NULL,NULL,0,NULL}
};

static struct PyModuleDef symnmfmodule = {
        PyModuleDef_HEAD_INIT,
        "symnmfapi", /* name of module */
        NULL, /* module documentation, may be NULL */
        -1,  /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
        symnmfMethods /* the PyMethodDef array from before containing the methods of the extension */
};

PyMODINIT_FUNC PyInit_symnmfapi(void)
{
    PyObject *m;
    m = PyModule_Create(&symnmfmodule);
    if (!m) {
        Py_RETURN_NONE;
    }
    return m;
}