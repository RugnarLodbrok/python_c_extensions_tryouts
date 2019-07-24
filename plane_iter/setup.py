# https://www.youtube.com/watch?v=bfmslcTKriw
# https://gist.github.com/physacco/2e1b52415f3a964ad2a542a99bebed8f
import sys
from distutils.core import setup, Extension

if sys.platform == 'win32':
    # https://stackoverflow.com/a/57109148/3367753
    # gcc should be in the PATH
    import distutils.cygwinccompiler

    distutils.cygwinccompiler.get_msvcr = lambda: []
    extra_link_args = ["-Wl,-Bstatic", "-lpthread"]

m = Extension('plane_iter',
              include_dirs=["."],
              libraries=['pthread'],
              sources=['plane_iter.c'])

setup(name='plane_iter',
      version='1.0',
      description='iterate indexes of 2d plane in various modes',
      author='rugnar',
      url='',
      ext_modules=[m])
