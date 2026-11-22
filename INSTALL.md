# Requisitos
    Necesita la versión de Ubuntu más reciente; Windows Driver de NVIDIA y WSL2.
    CUDA Toolkit (No todas las tarjetas gráficas son compatibles con la versión más reciente).
    Versiones de gcc y g++ compatibles con la versión de CUDA instalada.
    make
    autoconf
    automake
    libtool
    autoconf-archive

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