#include <iostream>

#include "bodega.h"
#include "stack.h"
#include "pedido.h"
#include "queue.h"
#include "montacarga.h"
#include "listaGenerica.h"
#include "producto.h"

#define CANTIDAD_MONTACARGAS 4             //Se definen la cantidad de montacargas a crearse
#define CANTIDAD_COLUMNAS_TOTALES 5        // por las columnas

using namespace std;

struct stack pilaBodega;
struct queue colaPedidos;
struct listadoble listaMontacargas;

int main(){
    bodega b1 = {"arroz",2,5,30};   
    bodega b2 = {"cerveza",3,3,100};

    pilaBodega.push(&b1);
    pilaBodega.push(&b2);

    producto p1;
    producto p2;
    p1.nombreProducto = b1.tipoProducto;
    p2.nombreProducto = b2.tipoProducto;

    producto ListaBodega[CANTIDAD_COLUMNAS_TOTALES];
    ListaBodega[0] = p1;
    ListaBodega[1] = p1;
    ListaBodega[2] = p2;
    ListaBodega[3] = p2;
    ListaBodega[4] = p2;
    
    for (int i = 0; i < b1.paletasxColumna; i++)
    {
        ListaBodega[0].columnas.push(&b1.unidadesxPaleta);
    }

    for (int i = 0; i < b1.paletasxColumna; i++)
    {
        ListaBodega[1].columnas.push(&b1.unidadesxPaleta);
    }

    for (int i = 0; i < b2.paletasxColumna; i++)
    {
        ListaBodega[2].columnas.push(&b2.unidadesxPaleta);
    }

    for (int i = 0; i < b2.paletasxColumna; i++)
    {
        ListaBodega[3].columnas.push(&b2.unidadesxPaleta);
    }

    for (int i = 0; i < b2.paletasxColumna; i++)
    {
        ListaBodega[4].columnas.push(&b2.unidadesxPaleta);
    }

    cout << ListaBodega[0].nombreProducto << endl;
    cout << ListaBodega[2].nombreProducto << endl;

    for (int i = 0; i < CANTIDAD_COLUMNAS_TOTALES; i++)
    {
        cout << "Columna: " << i << endl;
        while (!ListaBodega[i].columnas.isEmpty())
        {
            //cout << "Columna: " << i << endl;
            cout << (*(int*)ListaBodega[i].columnas.pop()) << endl;
        }
    }
    

/*     cout << (*(int*)ListaBodega[0].columnas.pop()) << endl;
    cout << (*(int*)ListaBodega[1].columnas.pop()) << endl;
    cout << (*(int*)ListaBodega[2].columnas.pop()) << endl;
    cout << (*(int*)ListaBodega[3].columnas.pop()) << endl;
    cout << (*(int*)ListaBodega[4].columnas.pop()) << endl; */

    

    //EJEMPLO DE LA PILA DE BODEGA
    //FUNCIONANDO
/*     while (!pilaBodega.isEmpty())
    {
        struct bodega currentElement = (*(struct bodega*)pilaBodega.pop());
        cout << "Tipo de Producto en Bodega: " << currentElement.tipoProducto << endl;
        cout << "Cantidad de Columnas destinadas: " << currentElement.columnasxTipo << endl;
    } */
    
    pedido pedido1 = {10,false,"arroz",60};
    pedido pedido2 = {11,false,"cerveza",250};

    pedido listaPedidos[2];
    listaPedidos[0] = pedido1;
    listaPedidos[1] = pedido2;

    //colaPedidos.enqueue(&pedido1);
    //colaPedidos.enqueue(&pedido2);

    for (int i = 0; i < 2; i++)
    {
        cout << listaPedidos[i].tipoProducto << listaPedidos[i].cantidad << endl;
    }
    
    //EJEMPLO DE LA COLA DE PEDIDOS
    //FUNCIONANDO
/*     while (!colaPedidos.isEmpty())
    {
        struct pedido currentElement = (*(struct pedido*)colaPedidos.dequeue());
        cout << "#Pedido: " << currentElement.numeroPedido << endl;
        cout << "Tipo de Pedido: " << currentElement.tipoProducto << endl;
    } */

    montacarga carrito;
    for (int i = 0; i < CANTIDAD_MONTACARGAS; i++)
    {
        listaMontacargas.addToBegining(&carrito);
    }

    cout << listaMontacargas.getSize() << endl;

/*     for (nodo* i = pilaBodega.stackList.start; i != nullptr; i = i->next)
    {
        void* genPointer = i->data;
        bodega* pointerBodega = (bodega*)genPointer;
        cout << pointerBodega->tipoProducto << endl;
    } */

}