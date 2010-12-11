from distutils.core import setup, Command
from distutils.extension import Extension
from Cython.Distutils import build_ext

srcpath = 'sha3lib/'
hashpath = srcpath + 'hash_functions/'

ext_modules = [
    Extension("sha3lib.hash_functions.echo.echo_hash",
        [hashpath+"echo/echo_hash.pyx", 
         hashpath+'echo/sha3nist.c', 
         hashpath+"echo/echo.c"],
    extra_compile_args=[
        '-funroll-loops',
        '-m32',
        '-march=prescott',
        '-O2',
        '-fomit-frame-pointer']
    ),
]

setup(
    name='SHA3lib',
    version='0.1',
    description='Python bindings for SHA3-256 in Cython',
    cmdclass = {'build_ext': build_ext},
    ext_modules = ext_modules,
    packages =
        ['sha3lib',
        'sha3lib.hash_functions',
        'sha3lib.hash_functions.echo',],
)
