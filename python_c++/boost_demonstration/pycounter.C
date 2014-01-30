#include <boost/python.hpp>
#include <boost/python/class.hpp>
#include "counter.h"

BOOST_PYTHON_MODULE(counter)
{
    boost::python::class_<Counter>("Counter")
        .def(boost::python::init<int>())
        .def("increment", &Counter::increment<int>)
        ;
};

