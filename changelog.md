# Versión 1.0 | Día 4 de Octubre 2026 | Base del programa.
    Se empezó añadiendo la estructura base del programa, es decir los .hpp:
        - Consumer.hpp
        - Producer.hpp
        - SharedBuffer.hpp
        - Package.hpp
    Se tenía intencionado crear un quinto .hpp llamado "WorkReader.hpp", que se enfocaría en 
leer el archivo .work y entregar los resultados en un struct para después pasarle los datos 
necesarios a las hebras de producción y consumidora, pero esta fue descartada para hacerla una 
función en el propio main.cpp junto al struct.

    Luego de haber definido todos los .hpp con sus funciones y atributos, se empezó con el 
main.cpp para hacer pruebas de compilación. Como nada dio problemas, se empezó con la 
codificación de los .cpp.

    De las cosas que más dio problema fue el pasar los parámetros a las hebras 
correspondientes, debido a que comparten el mismo Búfer, deben tener una referencia al mismo, 
así que se tuvo que hacer cambios menores en la variable del búfer en Consumer.hpp y Producer.hpp 
para acomodar estos problemas. La solución a esto fue añadir un "&" después de SharedBuffer, 
tanto en variable privada como parámetro al momento de crear el objeto de la clase.

    Otro problema fue al momento de pasarle la función estática a la hebra de la 
correspondiente, ya que la función "run()" era la que se estaba pasando como estática, pero al 
hacerlo, no permitía la modiciación ni uso de variables como acceder al búfer. Para 
solucionarlo se creó otra función que se llama "enter", y esta recibe un parámetro "void*", el 
cual servirá para hacer referencia a si mismo y después poder ejecutar run(), el cual se 
cambió a una simple función "void", donde se hacen todos los procesos necesarios.

    Después de que todo ya estaba implementado correctamente, se empezó con la lectura del 
archivo, y como se había mencionado anteriormente, esto se maneja en una función dentro de 
main.cpp, el cual devuelve un struct con todos los datos del archivo .work. Trabajar esto fue 
lo más sencillo de todo, además de que se agregaron chequeos extras por si no se ingresa un 
workload, o si se ingresan más de 1, y también si es que no se encuentra el workload.

# Versión 1.5 | Día 21 de Noviembre 2026 | Expansión de las hebras.
    Se expandieron el funcionamiento de las hebras, haciendo que tengan trabajo real y no 
simulado, método de proceso, cantidad ilimitada de hebras consumidoras, y diferenciación entre 
las hebras productoras Alpha y Beta. Además, las productoras mantienen el uso de pthreads, 
mientras que las consumidoras ahora usan std::thread para la creación de hebras.

    Las hebras consumidoras ahora pueden ser varias y no sólo 1, permitiendo un consumo de 
paquetes más rápido. Sucede lo mismo con las hebras productoras, incrementando drásticamente 
la producción de paquetes, pero esto se compenza con la cantidad incrementada de hebras 
consumidoras.

    Las hebras productoras Alpha ahora usan CUDA para procesar su trabajo, que es la 
transformación de rotación de vértices. CUDA permite que la hebra pueda solicitar un espacio 
en la GPU y usarla para hacer sus cálculos, luego recibe los resultados y los encola al búfer 
compartido.
    Las hebras productoras Beta ahora usan OpenMP, de estar forma permite aprovechar el proceso 
multinúcleo de la CPU para procesar los cambios de velocidad, haciendo que haga cálculos 
bastante rápido.

    El búfer compartido funciona bastante similar que antes, pero ahora usa un Broadcast para 
avisar cuando la cola está llena/vacía en vez de un Signal, haciendo que todas las hebras 
despierten, y no sólo una a la vez. Además que ahora cuenta con una condición de actividad, 
por lo que fuerza el termino de las hebras cuando el pipeline termina el trabajo.

    Se añadieron bastantes manejos de errores al momento de inicializar el programa, comenzar 
los procesos de las hebras, y al terminar. 