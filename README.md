# Programa multi-hilados usando semáforos sin nombre

Al trabajar con hilos o con un conjunto de procesos podemos notar que en ocasiones al
momento de trabajar en escribir y leer una variable por parte de estos mismos podemos
notar que la información no es la que deberían de escribir o de leer, esto sucede porque al
momento de que un proceso utiliza la variable otro proceso puede utilizar la misma variable y
no espera a que el primer proceso termine con la consulta de la variable por lo que eso
ocasiona una incoherencia en la variable. 

Para este problema utilizaremos sincronización por
medio de candados que bloquean los procesos para que solo uno ingrese a su sección
crítica y cuando termine abra el candado para que otro proceso entre a su sección crítica, y
semáforos que permiten que cierto número de procesos entren y acceden a la sección
crítica.

Las funciones a utilizar son:

* pthread_mutex_t c1: que crea un candado c1.
* pthread_mutex_init (&c1, NULL): inicializa el candado y tiene que definirse antes de la creación de los hilos.
* pthread_mutex_lock (&c1): Cierra el candado
* pthread_mutex_unlock(&c1): Abre el candado
* sem_t semáforo: se utiliza para declarar un semáforo
* sem_init (&semaforo, 0, 5): Define el candado indicando cuantos procesos pueden entrar
* sem_wait (&semaforo): indica que entra en el semáforo
* sem_post (&semaforo): indica que sale del semáforo
