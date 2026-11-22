# Funcionamiento
	El programa lee el archivo .work entregado al momento de ejecutar el programa y almacenará 
sus datos en un struct temporal. Luego pasará los datos a la librería dinámica.

	La librería inicializará el engine, luego comprobará si los valores son válidos para la 
ejecución del programa. Los valores no pueden ser negativos, si una hebra productora tiene 
una capacidad asignada, esta no puede tener 0 instancias de la misma, y tiene que haber si o 
si una hebra productora y consumidora.
	Luego de hacer la comprobación, empezará a inicializar el Búfer compartido, la(s) hebra(s) 
consumidora(s) Gamma, y todas las hebras productoras Alpha y Beta según corresponda. Cuando 
todo inicialize sin errores, empezará a trabajar. Se espera que cada hebra termine su trabajo 
y luego se termina el proceso completo del programa, mostrando en pantalla el total de 
paquetes despachados. En caso de errores, se marcarán en pantalla, y qué pasó resultó con error.

## Hebras Productoras (pthread)
	Las hebras productoras se encargan de encolar los paquetes a la cola del búfer compartido, 
pero si intentan encolar con la cola llena, se quedarán en espera hasta que haya un espacio 
nuevo en cola. 

### Alpha
	Esta se encarga de hacer transformaciones de vértices. Trabaja mediante el uso de CUDA, 
la cual reserva un espacio en la memoría de la GPU, copia los datos a la misma, y ejecuta la 
función de transformación. Al terminar, copias los datos devuelta a la CPU y libera la reserva 
de memoria en la GPU.
	Esta depende si o si de la existencia de una tarjeta gráfica NVIDIA para trabajar.

### Beta
	Esta se encarga de hacer cálculos de velocidad. Trabaja mediante el uso de OpenMP, 
diviendo la tarea en más mini-hebras usando multinúcleos, permitiendo hacer cálculos rápidos 
casi instantáneos.
	Por el uso de OpenMP, hay posibilidad de que TSan tiré falsos positivos relacionados al 
mismo, pero en realidad no hay condiciones de carrera. Por eso mismo, estos informes son 
suprimidos.

## Hebra Consumidora (std::thread)
	La hebra consumidora se encarga de sacar los paquetes de la cola del búfer compartido, 
haciendo espacio para la integración de más paquetes a la cola. Cada que saca un paquete de la 
cola imprime en pantalla la id de la hebra consumidora, tipo de paquete, su identificador y los paquetes restantes en cola.

## Búfer Compartido
	Se encarga de sincrónizar los procesos de todas las hebras, evitando condiciones de 
carrera entre ellas, haciendo que el trabajo sea fluido y eficiente. También tiene un tamaño de cola máximo, que es definido por el archivo ".work" a procesar.
	Debido a que son múltiples hebras, el uso de Signal no es suficiente, por lo que es 
necesario usar un Broadcast para avisar cuando la cola está vacía o llena. Cuando el programa 
termina de procesar los paquetes, fuerza a todas las hebras a terminar y evita que otras hebras 
intenten producir/consumir más paquetes.

## Protección de procesos
	Al momento de hacer cambios en la cola, se usan mutex para proteger la cola de alguna 
alteración durante un proceso externo o en paralelo, ya que todas las hebras acceden a ella al 
mismo tiempo, hay que evitar que puedan modificar los datos al mismo tiempo y dejar que sólo 1 
a la vez pueda hacerlo. 
	También se usan condiciones de espera, es decir, si cierta condición sucede, como por 
ejemplo la cola está llena, una hebra que intenta encolar un paquete a la cola, quedará en 
espera hasta que la señal de "Cola ya no está llena" sea lanzada cuando una Hebra Consumidora 
saque un paquete de la cola. A la vez, al momento de desencolar un paquete, la Hebra 
Consumidora quedará en espera de la misma forma cuando la cola esté vacía, así se evita hacer ejecuciones inválidas.

## Especificaciones
	Cuando una de las Hebras Prouctoras ya produzca 5 paquetes, se toma un tiempo de descanso 
de 160ms para evitar sobrecalentamiento del sistema. Las Hebras Consumidoras también tiene sus 
tiempos de descanso, los cuales son definidos por el archivo ".work" que se use, haciendo que 
descanse cada vez que termina un paquete, y también teniendo un tiempo de penalización, donde 
es forzado a deterse antes de procesar un paquete cuando la cola queda vacía, haciendo que 
tarde 40ms extras por estar la cola vacía.
	Cuando el flujo haya terminado, se imprimirá en pantalla la cantidad total de paquetes 
procesados y terminará sin errores.