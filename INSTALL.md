# Requisitos
    Necesita la versión de Ubuntu más reciente; Windows Driver de NVIDIA y WSL2.
    CUDA Toolkit (No todas las tarjetas gráficas son compatibles con la versión más reciente).
    Versiones de gcc y g++ compatibles con la versión de CUDA instalada.
    make
    autoconf
    automake
    libtool
    autoconf-archive

    /usr/bin/nvcc -ccbin g++-14 -arch=native -std=c++20 \
-Xcompiler -fPIC -I../include -c alpha_kernels.cu -o alpha_kernels.o
nvcc fatal   : Unsupported gpu architecture 'compute_120'
make[2]: *** [Makefile:821: alpha_kernels.o] Error 1
make[2]: Leaving directory '/mnt/c/Users/PC-LAB3D/Documents/GitHub/Proyecto1_SO/src'
make[1]: *** [Makefile:417: all-recursive] Error 1
make[1]: Leaving directory '/mnt/c/Users/PC-LAB3D/Documents/GitHub/Proyecto1_SO'
make: *** [Makefile:349: all] Error 2

GNU Make 4.3
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

autoconf (GNU Autoconf) 2.71
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv3+/Autoconf: GNU GPL version 3 or later
<https://gnu.org/licenses/gpl.html>, <https://gnu.org/licenses/exceptions.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by David J. MacKenzie and Akim Demaille.

automake (GNU automake) 1.16.5
Copyright (C) 2021 Free Software Foundation, Inc.
License GPLv2+: GNU GPL version 2 or later <https://gnu.org/licenses/gpl-2.0.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Written by Tom Tromey <tromey@redhat.com>
       and Alexandre Duret-Lutz <adl@gnu.org>.

libtool (GNU libtool) 2.4.7
Written by Gordon Matzigkeit, 1996

Copyright (C) 2014 Free Software Foundation, Inc.

# Compilación
    Antes de compilar, asegurese de tener las librerías anteriores instaladas.

    $ autoreconf -fi
    $ ./configure
    $ make

# Ejecución
    Para ejecutar el programa, necesita usar:
    $ ./src/pipeline_engine [ARCHIVO]
    
    [ARCHIVO] es el archivo .work que debería encontrarse en la carpeta test/. Acá hay unos archivos para usar:
    - test.work
    - 3.work

    Comando de ejemplo de uso:
    $ ./src/pipeline_engien test/test.work

    Puede crear nuevos archivos .work y usarlos en el programa. Para ello debe seguir el 
sintaxis correcto:
    <Capacidad_Queue>
    <Num_Gamma_Threads> <Tiempo_Despacho_Gamma>
    <Num_Alfa_Threads> <Cantidad_Paquetes_Por_Alfa>
    <Num_Beta_Threads> <Cantidad_Paquetes_Por_Beta>

    Para asegurarse de crear uno nuevo con el sintaxis correcto, se recomienda copiar el 
test.work y cambiar sus valores.