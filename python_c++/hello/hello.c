#include <Python.h>

#define throw(msg);  PyErr_SetString( PyExc_TypeError, msg); return 0;

static PyObject *
safe_hello_to_you(PyObject *self, PyObject *args)
{
  PyObject * py_name = NULL;
  int ok = PyArg_ParseTuple(args, "S", &py_name);
  if (!ok) return 0;

  if ( ! PyString_Check(py_name))
  {
    throw("Argument passed was not a string!"); 
  }

  Py_ssize_t name_len = PyString_Size(py_name);
  char * name = PyString_AsString(py_name);
  if ( name == NULL)
  {
    throw("Argument passed was not a string!"); 
  }

  char * hello = "Hello ";
  Py_ssize_t hello_len = strlen(hello);


  Py_ssize_t hello_name_len = hello_len + name_len;
  char * hello_name = (char * ) malloc(hello_name_len + 1 ); //nullbyte
  hello_name[hello_name_len] = '\0';

  memcpy(hello_name, hello, hello_len);
  memcpy(hello_name + hello_len , name, name_len);

  PyObject * py_hello_name = PyString_FromStringAndSize(hello_name, hello_name_len);
  if ( !py_hello_name)
  {
    throw("Error allocating pythong string Hello World");
  }

  free(hello_name);
  return py_hello_name;
}

static PyObject *
safe_hello(PyObject *self, PyObject *args)
{
  PyObject * py_hello_world = PyString_FromString("Hello World");
  if ( !py_hello_world)
  {
    throw("Error allocating pythong string Hello World");
  }
  return py_hello_world;
}

/* The function doc string */
PyDoc_STRVAR(meth_hello__doc__,
"Returns the string \"Hello World\"");
PyDoc_STRVAR(meth_hello_to_you__doc__,
"Says hello to the person passed to you as an argument");

static PyMethodDef hello_methods[] = {
  {"hello",  safe_hello, METH_VARARGS, meth_hello__doc__},
  {"hello_to_you",  safe_hello_to_you, METH_VARARGS, meth_hello_to_you__doc__},
  {NULL, NULL}      /* sentinel */
};

/* The module doc string */
PyDoc_STRVAR(hello__doc__,
"Hello World Library");

PyMODINIT_FUNC
inithello(void)
{
  /* There have been several InitModule functions over time */
  Py_InitModule3("hello", hello_methods,
                   hello__doc__);
}
