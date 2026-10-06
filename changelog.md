# Versión 1.0 | Día 4 de Octubre 2026 | Base del programa.
    Se empezó añadiendo la estructura base del programa, es decir los .hpp:
        - Consumer.hpp
        - Producer.hpp
        - SharedBuffer.hpp
        - Package.hpp
    Se tenía intencionado crear un quinto .hpp llamado "WorkReader.hpp", que
se enfocaría en leer el archivo .work y entregar los resultados en un struct
para después pasarle los datos necesarios a las hebras de producción y 
consumidora, pero esta fue descartada para hacerla una función en el propio
main.cpp junto al struct.

    Luego de haber definido todos los .hpp con sus funciones y atributos, se
empezó con el main.cpp para hacer pruebas de compilación. Como nada dio 
problemas, se empezó con la codificación de los .cpp.

    De las cosas que más dio problema fue el pasar los parámetros a las hebras
correspondientes, debido a que comparten el mismo Búfer, deben tener una 
referencia al mismo, así que se tuvo que hacer cambios menores en la variable
del búfer en Consumer.hpp y Producer.hpp para acomodar estos problemas. La
solución a esto fue añadir un "&" después de SharedBuffer, tanto en variable 
privada como parámetro al momento de crear el objeto de la clase.

    Otro problema fue al momento de pasarle la función estática a la hebra de 
la correspondiente, ya que la función "run()" era la que se estaba pasando 
como estática, pero al hacerlo, no permitía la modiciación ni uso de variables 
como acceder al búfer. Para solucionarlo se creó otra función que se llama 
"enter", y esta recibe un parámetro "void*", el cual servirá para hacer 
referencia a si mismo y después poder ejecutar run(), el cual se cambió a una 
simple función "void", donde se hacen todos los procesos necesarios.

    Después de que todo ya estaba implementado correctamente, se empezó con la 
lectura del archivo, y como se había mencionado anteriormente, esto se maneja 
en una función dentro de main.cpp, el cual devuelve un struct con todos los 
datos del archivo .work. Trabajar esto fue lo más sencillo de todo, además de 
que se agregaron chequeos extras por si no se ingresa un workload, o si se 
ingresan más de 1, y también si es que no se encuentra el workload.