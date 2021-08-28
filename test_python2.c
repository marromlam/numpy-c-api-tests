//#define NPY_NO_DEPRECATED_APINPY_1_7_API_VERSION
//#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL cool_ARRAY_API
#include <Python.h>
#include <numpy/arrayobject.h> // numpy!
#include <iostream>
using namespace std;
#include <stdlib.h>
#include <string>

/* PyObject *numpy = PyImport_ImportModule("numpy"); */
/* PyObject *numpy_matrix = PyObject_GetAttrString(numpy, "matrix"); */
/* PyObject *my_matrix = PyObject_CallFunction(numpy_matrix, "(s)", "0 0; 0 0"); */
/*  */

int main(){

// Name of input-file
char pyfilename[] = "Testfile";

// initilaize python interpreter
Py_Initialize();
import_array(); 

// load input-file
PyObject *pyName = PyUnicode_FromString(pyfilename);
PyObject *pyModule = PyImport_Import(pyName);

// import my numpy array object
PyObject *A = PyObject_GetAttrString(pyModule, "A");
PyObject *B = PyObject_GetAttrString(pyModule, "B");

// PyObject *shit = npy_acosh(A);

// Array Dimensions
npy_intp dimA[] = { PyArray_NDIM(A) }; // array dimension
dimA[0] = PyArray_DIM(A, 0); // number of rows
dimA[1] = PyArray_DIM(A, 1); // number of columns

npy_intp dimB[] = { PyArray_NDIM(B) }; // array dimension
dimB[0] = PyArray_DIM(B, 0); // number of rows
dimB[1] = PyArray_DIM(B, 1); // number of columns

// PyArray_SimpleNew allocates the memory needed for the array.
PyObject *ArgsArray = PyArray_SimpleNew(2, dimA, NPY_DOUBLE);

// The pointer to the array data is accessed using PyArray_DATA()
double *p = (double *)PyArray_DATA(ArgsArray);

for (int i = 0; i<dimA[0]; i++)
{
    for (int j = 0; j<dimA[1]; j++)
        {
             p[i * dimA[1] + j] = *((int *)PyArray_GETPTR2(A, i, j));
             cout << "p[" << i * dimA[1] + j << "]" << p[i * dimA[1] + j] << endl;
        }
}
// -----------------------------------------------------------


Py_Finalize();

return 0;
}
