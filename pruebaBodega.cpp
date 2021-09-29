#include <iostream>

#include "bodega.h"
#include "stack.h"
#include "pedido.h"
#include "queue.h"

using namespace std;

struct stack pilaBodega;
struct queue colaPedidos;

int main(){
    bodega b1 = {"arroz",2,5,30};
    bodega b2 = {"cerveza",3,3,100};

    pilaBodega.push(&b1);
    pilaBodega.push(&b2);

    //EJEMPLO DE LA PILA DE BODEGA
    //FUNCIONANDO
    while (!pilaBodega.isEmpty())
    {
        struct bodega currentElement = (*(struct bodega*)pilaBodega.pop());
        cout << "Tipo de Producto en Bodega: " << currentElement.tipoProducto << endl;
        cout << "Cantidad de Columnas destinadas: " << currentElement.columnasxTipo << endl;
    }
    
    pedido p1 = {10,false,"arroz",60};
    pedido p2 = {11,false,"cerveza",250};

    colaPedidos.enqueue(&p1);
    colaPedidos.enqueue(&p2);
    
    //EJEMPLO DE LA COLA DE PEDIDOS
    //FUNCIONANDO
    while (!colaPedidos.isEmpty())
    {
        struct pedido currentElement = (*(struct pedido*)colaPedidos.dequeue());
        cout << "#Pedido: " << currentElement.numeroPedido << endl;
        cout << "Tipo de Pedido: " << currentElement.tipoProducto << endl;
    }

/*     for (nodo* i = pilaBodega.stackList.start; i != nullptr; i = i->next)
    {
        void* genPointer = i->data;
        bodega* pointerBodega = (bodega*)genPointer;
        cout << pointerBodega->tipoProducto << endl;
    } */

}