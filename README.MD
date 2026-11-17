# Compilación
  Antes de compilar, es importante verificar que todo está actualizado.
  $ sudo apt-get update
  $ sudo apt-get upgrade

  Luego de verificar que todo está bien, también se necesitan los compiladores de C++. Si ya los tiene instalados, se
puede saltar este paso.
  $ sudo apt-get install gcc g++

  Ahora que todo está en orden, se necesitan las librerías esenciales de Autotools y Make. Para eso necesitará 
ejecutar el siguiente comando en consola.
  $ sudo apt-get install build-essential autoconf automake libtool make

  Ya con esto instalado, va a tener que situarse en la carpeta raíz del programa. Cuando lo esté, tendrá que
ejecutar lo siguiente:
  $ autoreconf --ivf

  Cuando ya todo esté configurado, verá que se crearon varios archivos de configuración, ya con esto tendrá que 
hacer:
  $ ./configure 

  Después de ejecutar el comando anterior, se crearan unos archivos Makefile, los cuales serviran para poder 
compilar el programa para la ejecución. Para ello se tendrá que usar:
  $ make

# Ejecución
  Para ejecutar el programa, necesita usar:
  $./src/pipeline_simulator [ARCHIVO]
  
  Donde [ARCHIVO] podrá ser cualquiera de los siguientes:
  - 1
  - 2
  - 3
  - test
  - bigshot

  No hace falta ingresar ".work" al momento de seleccionar el archivo, ya que el programa automáticamente busca e 
identifica el archivo con su extensión en el directorio "test/". Si crea un archivo nuevo, especifique su extensión 
como ".work", ya que el programa no lo reconocerá de otra forma.

  Comando de ejemplo de uso:
  $./src/pipeline_simulator test

# Funcionamiento
  Lo primero que hace el programa será leer el nombre del archivo entregado, el mismo buscará el archivo en la 
carpeta correspondiente y añadirá la extensión ".work" para que el programa lo pueda reconocer. Después de 
encontrar el archivo y leerlo, le pasará los datos a las hebras de trabajo, 2 productoras y 1 consumidora, donde 
las 3 comparten un búfer para manenter coordinación en el trabajo. 

## Hebras Productoras
  Las hebras productoras se encargan de encolar los paquetes a la cola del búfer compartido, pero si intentan 
encolar con la cola llena, se quedarán en espera hasta que haya un espacio nuevo en cola. 

## Hebra Consumidora
  La hebra consumidora se encarga de sacar los paquetes de la cola del búfer compartido, haciendo espacio para 
la integración de más paquetes a la cola. Cada que saca un paquete de la cola imprime en pantalla su tipo de 
paquete, su identificador y los paquetes restantes en cola.

## Búfer Compartido
  Se encarga de sincrónizar los procesos de las 3 hebras, evitando condiciones de carrera entre ellas, haciendo 
que el trabajo sea más fluido y eficiente. También tiene un tamaño de cola máximo, que es definido por el 
archivo ".work" a procesar.

## Protección de procesos
  Al momento de hacer cambios en la cola, se usan mutex para proteger la cola de alguna alteración durante un 
proceso externo o en paralelo, ya que las 3 hebras acceden a ella al mismo tiempo, hay que evitar que las 3 
puedan modificar los datos al mismo tiempo y deja que sólo 1 a la vez pueda hacerlo. 
  También se usan condiciones de espera, es decir, si cierta condición sucede, como por ejemplo la cola está 
llena, la hebra que intentar encolar un paquete a la cola, quedará en espera hasta que la señal de "Cola ya no 
está llena" sea lanzada cuando la Hebra Consumidora saque un paquete de la cola. A la vez, al momento de 
desencolar un paquete, la Hebra Consumidora quedará en espera de la misma forma cuando la cola esté vacía, de 
esta forma se evita hacer ejecuciones inválidas.

## Especificaciones
  Cuando una de las Hebras Prouctoras ya produzca 5 paquetes, se toma un tiempo de descanso de 160ms para evitar 
sobrecalentamiento del sistema. La Hebra Consumidora también tiene sus tiempos de descanso, los cuales son 
definidos por el archivo ".work" que se use, haciendo que descanse cada vez que termina un paquete, y también 
teniendo un tiempo de penalización, donde es forzado a deterse antes de procesar un paquete cuando la cola 
queda vacía, haciendo que tarde 40ms extras por estar la cola vacía.

  Cuando el flujo haya terminado, se imprimirá en pantalla la cantidad total de paquetes procesados y terminará 
sin errores


La solución es prohibir la copia explícitamente en SharedBuffer:

cpp
SharedBuffer(const SharedBuffer&) = delete;
SharedBuffer& operator=(const SharedBuffer&) = delete;

Con eso, cualquiera de los tres casos anteriores pasa a ser un error de compilación, en vez de un bug que descubres en tiempo de ejecución. Es una práctica de las C++ Core Guidelines (la rúbrica las menciona), y puedes citarla en el README.