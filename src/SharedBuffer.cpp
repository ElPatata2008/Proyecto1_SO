#include "../include/SharedBuffer.hpp"
#include <iostream>

SharedBuffer::SharedBuffer(size_t cap): _queueCapacity(cap) {
    pthread_mutex_init(&m, nullptr);            // Inicialización de Mutex (Protección).
    pthread_cond_init(&notFull, nullptr);       // Inicialización de condition (Funciona como señal).
    pthread_cond_init(&notEmpty, nullptr);      // Inicialización de condition (Funciona como señal).
}

void SharedBuffer::start(int total) {
    _totalProyected = total;
    _pipelineActive = (total > 0);
}

void SharedBuffer::push(char type) {
    pthread_mutex_lock(&m);                     

    while (pkgQueue.size() == _queueCapacity) { 
        pthread_cond_wait(&notFull, &m);        
    }                                           
    
    Package pkg;
    if (type == 'A') {
        pkg.id = _nextIdAlpha++;
    } else if (type == 'B') {
        pkg.id = _nextIdBeta++;
    }

    pkgQueue.push(pkg);                        
    pthread_cond_signal(&notEmpty);             

    pthread_mutex_unlock(&m);                   
}

PopResult SharedBuffer::pop() {
    pthread_mutex_lock(&m);                     

    bool underflow = pkgQueue.empty();          

    while (pkgQueue.empty()) {                  
        pthread_cond_wait(&notEmpty, &m);       
    }                                           

    Package pkg = pkgQueue.front();             
    pkgQueue.pop();                             

    int remain = pkgQueue.size();               

    pthread_cond_signal(&notFull);              

    pthread_mutex_unlock(&m);                   

    return PopResult{pkg, remain, underflow};   
}

SharedBuffer::~SharedBuffer() {
    pthread_mutex_destroy(&m);                  // Destrucción/Limpieza.
    pthread_cond_destroy(&notFull);             // Destrucción/Limpieza.
    pthread_cond_destroy(&notEmpty);            // Destrucción/Limpieza.
}