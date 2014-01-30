from distutils.core import setup, Extension

setup(name="search_helper", version="0.0",
      ext_modules = [Extension("search_helper",
                               ["search_helper.C"
                               ],
                               extra_compile_args = ['-std=c++0x', '-O3', '-funroll-loops', '-march=native'],
                               language = "c++"
                              )])
