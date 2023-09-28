# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include "matric_op.c"
#include "symnmf.c"

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
    double **norm_mat;
    norm_mat = sym(c_mat, v_num, v_size);
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