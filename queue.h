#ifndef _QUEUE_
#define _QUEUE_ 1

#include "listaGenerica.h"

struct queue
{
    struct listadoble stackList;

    bool isEmpty(){
        return stackList.isEmpty();
    }

    void enqueue(void* pElement){
        stackList.addToEnd(pElement);
    }
    
    void* dequeue() {
        if (!stackList.isEmpty()) {
            return stackList.removeFirst();
        } else {
            return nullptr;
        }
    }

};

#endif