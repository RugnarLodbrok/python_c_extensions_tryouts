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

m = Extension('plane_traverse',
              include_dirs=["."],
              libraries=['pthread'],
              sources=['revgen.c'])

setup(name='revgen',
      version='1.0',
      description='c extension example generator',
      author='rugnar',
      url='',
      ext_modules=[m])
