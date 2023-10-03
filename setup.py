from setuptools import Extension, setup

symnmf_module = Extension(
    'symnmfapi',  # Name of the extension module
    sources=['symnmfmodule.c', 'matric_op.c', 'symnmf.c' ,'h_optimize.c'],  # List of C source files
)

setup(
    name='symnmfapi',
    version='1.0',
    author='Aviv Ben Shoushan',
    description='symnmf algorithem',
    ext_modules=[symnmf_module],  # List of extension modules
)