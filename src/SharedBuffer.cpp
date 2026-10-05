#include "../include/SharedBuffer.hpp"
#include <iostream>

SharedBuffer::SharedBuffer(int cap): _queueCapacity(cap) {
    pthread_mutex_init(&m, nullptr);            // Inicialización de Mutex (Protección).
    pthread_cond_init(&notFull, nullptr);       // Inicialización de condition (Funciona como señal).
    pthread_cond_init(&notEmpty, nullptr);      // Inicialización de condition (Funciona como señal).
}

void SharedBuffer::push(Package pkg) {
    pthread_mutex_lock(&m);                     // Lock Activo.

    while (pkgQueue.size() == _queueCapacity) { // Si la cola está llena,
        pthread_cond_wait(&notFull, &m);        // Espera señal hasta que
    }                                           // se haga un espacio.
    
    pkgQueue.push(pkg);                         // Añade el Paquete a la cola.
    pthread_cond_signal(&notEmpty);             // Envía señal "Cola ya no vacía".

    pthread_mutex_unlock(&m);                   // Desbloquea.
}

PopResult SharedBuffer::pop() {
    pthread_mutex_lock(&m);                     // Lock Activo.

    bool underflow = pkgQueue.empty();          // Revisa si la cola está vacía.

    while (pkgQueue.empty()) {                  // Si la cola está vacía,
        pthread_cond_wait(&notEmpty, &m);       // Espera señal hasta que
    }                                           // llegue un paquete.

    Package pkg = pkgQueue.front();             // Se guarda el paquete en variable.
    pkgQueue.pop();                             // Se quita paquete de la cola.

    int remain = pkgQueue.size();               // Se revisa el número de paquetes restantes.

    pthread_cond_signal(&notFull);              // Se manda señal de "Ya no estoy lleno".

    pthread_mutex_unlock(&m);                   // Desbloquea.

    return PopResult{pkg, remain, underflow};   // Se retornan los resultados.
}

SharedBuffer::~SharedBuffer() {
    pthread_mutex_destroy(&m);                  // Destrucción/Limpieza.
    pthread_cond_destroy(&notFull);             // Destrucción/Limpieza.
    pthread_cond_destroy(&notEmpty);            // Destrucción/Limpieza.
}