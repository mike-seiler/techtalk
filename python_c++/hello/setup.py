from distutils.core import setup, Extension

setup(name="hello", version="0.0",
  ext_modules = [Extension("hello", ["hello.c"])])
