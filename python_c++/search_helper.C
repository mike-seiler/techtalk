#include <Python.h>
#include "searcher.h"
#include "iostream"

#define throw(msg);  PyErr_SetString( PyExc_TypeError, msg); return 0;

/* The function doc string */
PyDoc_STRVAR(meth_load__doc__,
"Loads the searcher object with an argument of a type similar to ghostery_mock = [(0, \"doubleclick.com\"), (1, \"advertising.com\"), (2, \"valueclick.com\")]");

PyDoc_STRVAR(meth_search_helper_to_you__doc__,
"Searches in the cached tuple for the haystack argument");

static void destroy_searcher(void *f)
{
  Searcher *searcher = (Searcher *)f;
  delete searcher;
}

std::string
stdstring_from_pystring(PyObject * py_str)
{
  std::string res(PyString_AsString(py_str), PyString_Size(py_str));
  return std::move(res);
}

static PyObject *
safe_load(PyObject *self, PyObject *args)
{
  PyObject * py_data = NULL;
  int ok = PyArg_ParseTuple(args, "O", &py_data);
  if (!ok) return 0;
  if(py_data == NULL){ throw("NULL");}
  if(!PyList_Check(py_data)){throw("Not a Python List");}

  std::vector<Pair> data;

  Py_ssize_t list_size = PyList_Size(py_data);

  for(int i = 0; i < list_size; i++)
  {

    PyObject * py_pair = PyList_GetItem(py_data, i);
    if(!PyTuple_Check(py_pair)) {throw("Not a valid python tuple"); }
    if(PyTuple_Size(py_pair) != 2 ){ throw("Tuple is the wrong size");}
    PyObject * py_id =  PyTuple_GetItem(py_pair, 0);
    PyObject * py_str = PyTuple_GetItem(py_pair, 1);

    if(!PyString_Check(py_str) || !PyInt_Check(py_id)){throw("invalid tuple inputs");}
    Pair line_pair = Pair(PyInt_AsLong(py_id), stdstring_from_pystring(py_str));
    data.push_back(line_pair);
  }

  void * mysearcher = (void *) new Searcher(std::move(data));
  return PyCObject_FromVoidPtr(mysearcher, destroy_searcher);
}


PyObject *
pylist_from_vector(const std::vector <int>  & res)
{
  PyObject * pylist = PyList_New(res.size());
  Py_ssize_t cnt = 0;
  for(auto it = res.begin(); it != res.end(); ++it){
    if( PyList_SetItem(pylist, cnt ,PyInt_FromLong((long)*it) ) == -1)
    {
      throw("Constructing list failed");
    }
    cnt++;
  }
  return pylist;
}

static PyObject *
safe_search(PyObject *self, PyObject *args)
{
  PyObject * py_searcher;
  PyObject * py_string;
  int ok = PyArg_ParseTuple(args, "OS", &py_searcher, &py_string);
  if (!ok) return 0;
  std::string my_string(PyString_AsString(py_string), PyString_Size(py_string));
  Searcher * mysearcher  = (Searcher *) PyCObject_AsVoidPtr(py_searcher);
  auto res = mysearcher->search(my_string);
  PyObject * pyres =  pylist_from_vector(res);

  if(!pyres){
    throw("OOPS");
  }
  return pyres;
}


static PyMethodDef search_helper_methods[] = {
  {"load",  safe_load, METH_VARARGS, meth_load__doc__},
  {"search",  safe_search, METH_VARARGS, meth_search_helper_to_you__doc__},
  {NULL, NULL}      /* sentinel */
};

/* The module doc string */
PyDoc_STRVAR(search_helper__doc__,
"Hello World Library");

PyMODINIT_FUNC
initsearch_helper(void)
{
  /* There have been several InitModule functions over time */
  Py_InitModule3("search_helper", search_helper_methods,
                   search_helper__doc__);
}
