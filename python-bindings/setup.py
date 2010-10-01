# encoding: utf-8
from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

ext_modules = [
    Extension("bmw.bmw",
        ["bmw/bmw.pyx", 'bmw/BlueMidnightWish.c'],),
    Extension("groestl.groestl",
        ["groestl/groestl.pyx", 'groestl/Groestl-opt.c'],),
    
    ]

setup(
    name='SHA3lib',
    version='0.1',
    description='Python bindings for SHA3 using cython',
    author='Eirik Haver and Pål Ruud',
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules,
    packages = ['bmw','groestl'],
    py_modules = ['sha3lib'],
)
