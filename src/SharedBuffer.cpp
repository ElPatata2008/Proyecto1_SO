#include "../include/SharedBuffer.hpp"

SharedBuffer::SharedBuffer(size_t cap): _queueCapacity(cap) {
    pthread_mutex_init(&m, nullptr);            // Inicialización de Mutex (Protección).
    pthread_cond_init(&notFull, nullptr);       // Inicialización de condition (Funciona como señal).
    pthread_cond_init(&notEmpty, nullptr);      // Inicialización de condition (Funciona como señal).
}

void SharedBuffer::start(int total) {
    pthread_mutex_lock(&m);                      
    _totalProyected = total;
    _pipelineActive = (total > 0);
    pthread_mutex_unlock(&m);
}

void SharedBuffer::shutdown() {
    pthread_mutex_lock(&m);                      
    _pipelineActive = false;                     
    pthread_cond_broadcast(&notFull);            
    pthread_cond_broadcast(&notEmpty);           
    pthread_mutex_unlock(&m);                    
}

void SharedBuffer::push(char type) {
    pthread_mutex_lock(&m);                     

    while (pkgQueue.size() == _queueCapacity && _pipelineActive) { 
        pthread_cond_wait(&notFull, &m);        
    }             
    
    if (!_pipelineActive) {                         
        pthread_mutex_unlock(&m);               
        return;                                 
    }
    
    Package pkg{};
    if (type == 'A') {
        pkg = {'A', _nextIdAlpha++};
    } else if (type == 'B') {
        pkg = {'B', _nextIdBeta++};
    }

    pkgQueue.push(pkg);                        
    pthread_cond_broadcast(&notEmpty);             

    pthread_mutex_unlock(&m);                   
}

PopResult SharedBuffer::pop() {
    pthread_mutex_lock(&m);                     

    bool underflow = pkgQueue.empty() && _pipelineActive;          

    while (pkgQueue.empty() && _pipelineActive) {                  
        pthread_cond_wait(&notEmpty, &m);       
    }

    bool done = !_pipelineActive && pkgQueue.empty();

    if (done) {                                  
        pthread_mutex_unlock(&m);               
        return PopResult{Package(), 0, underflow, done}; 
    }

    Package pkg = pkgQueue.front();             
    pkgQueue.pop();
    _consumed++;                    

    if (_consumed == _totalProyected) {                  
        _pipelineActive = false;              
        pthread_cond_broadcast(&notEmpty);    
    }
    
    int remain = pkgQueue.size();               

    pthread_cond_broadcast(&notFull);

    pthread_mutex_unlock(&m);                   

    return PopResult{pkg, remain, underflow, done};   
}

SharedBuffer::~SharedBuffer() {
    pthread_mutex_destroy(&m);                  // Destrucción/Limpieza.
    pthread_cond_destroy(&notFull);             // Destrucción/Limpieza.
    pthread_cond_destroy(&notEmpty);            // Destrucción/Limpieza.
}