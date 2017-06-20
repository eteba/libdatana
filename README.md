# libdatana
Librería C++ simple de análisis de datos.

COMPILAR:
$ make
# make install
# make link

Para incorporarla a algún programa, es necesario tener instalado ROOT.

Ej:
g++ programa.cc -o programa -ldatana `root-config --cflags --libs`

Aunque solo es estrictamente necesario:
g++ programa.cc -o programa -ldatana -L/usr/lib64/root -lMathCore

