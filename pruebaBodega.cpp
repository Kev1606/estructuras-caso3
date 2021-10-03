#include <iostream>

#include "bodega.h"
#include "stack.h"
#include "pedido.h"
#include "queue.h"
#include "montacarga.h"
#include "listaGenerica.h"
#include "producto.h"
#include "constantes.h"

using namespace std;

int main(){
    bodega arrayBodega[2] = {{"arroz",2,5,30},{"cerveza",3,3,100}};

    producto ListaBodega[CANTIDAD_COLUMNAS_TOTALES];

    int indiceBodega = 0;
    int cantidad = 30;

    for (int producto = 0; producto < 2; producto++)
    {
        for (int columna = 0; columna < arrayBodega[producto].columnasxTipo; columna++)
        {
            ListaBodega[indiceBodega].nombreProducto = arrayBodega[producto].tipoProducto;
            cout << "Nombre de producto: " << ListaBodega[indiceBodega].nombreProducto << endl;
            cout << "Columna: " << columna <<endl;

            for (int unidades = 0; unidades < arrayBodega[producto].paletasxColumna; unidades++)
            {
                int* cantidad = (int*)malloc(sizeof(int));
                *cantidad = arrayBodega[producto].unidadesxPaleta;
                ListaBodega[indiceBodega].columnas.push(cantidad);
                cout << (*(int*)ListaBodega[indiceBodega].columnas.pop()) << endl;
            }
            indiceBodega++;
        }
    }

    cout << ListaBodega[0].nombreProducto << endl;
    cout << ListaBodega[2].nombreProducto << endl;

    pedido listaPedidos[CANTIDAD_PEDIDOS];
    listaPedidos[0] = {10,false,{"arroz","cerveza"},{60,100}};
    listaPedidos[1] = {11,false,{"cerveza","arroz"},{250,90}};

    for (int pedidos = 0; pedidos < CANTIDAD_PEDIDOS; pedidos++){
        cout << "Numero de pedido: " <<listaPedidos[pedidos].numeroPedido << endl;
        if (listaPedidos[pedidos].estado == false){
            cout << "El estado del pedido es: pendiente" << endl;
        } else{
            cout << "El estado del pedido es: completado" << endl;
        }
        for (int producto = 0; producto < CANTIDAD_PEDIDOS; producto++) {
            cout << "Tipo de producto: " << listaPedidos[pedidos].tipoProducto[producto] << "\tCantidad a retirar: " <<listaPedidos[pedidos].cantidad[producto] << endl;
        }
    } 

    //Montacargas a crearse 
    montacarga carrito1;
    montacarga carrito2;
    montacarga carrito3;
    montacarga carrito4;

    montacarga listaCarrito[CANTIDAD_MONTACARGAS];
    listaCarrito[0]=carrito1;
    listaCarrito[1]=carrito2;
    listaCarrito[2]=carrito3;
    listaCarrito[3]=carrito4;

    int variableRandom;
    int array[2] = {0,1};
    for (int i = 0; i < 2; i++){
        variableRandom = rand()%2;
        while (true) {
            if (array[variableRandom]==-1){
                variableRandom = rand()%2;
            } else {
                array[variableRandom] = -1;
                break;
            }
            if (CANTIDAD_MONTACARGAS==CANTIDAD_PEDIDOS){
                listaCarrito[variableRandom].colaPedido.enqueue(&listaPedidos[variableRandom]);
            }
        }
    }

    for (int i = 0; i < CANTIDAD_MONTACARGAS; i++) {
        if (!listaCarrito[i].colaPedido.isEmpty()) {
            cout << listaCarrito[i].colaPedido.dequeue();
        }else{
            cout << "vacia" << endl;
        }
    }
    
    

}