#include <iostream>
#include <string>

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
    //int cantidad = 30;

    for (int producto = 0; producto < CANTIDAD_PRODUCTOS; producto++)
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
                //cout << (*(int*)ListaBodega[indiceBodega].columnas.pop()) << endl;
            }
            indiceBodega++;
        }
    }

    //cout << ListaBodega[0].nombreProducto << endl;
    //cout << ListaBodega[2].nombreProducto << endl;
    cout << "\n" << endl;

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
            cout << "Tipo de producto: " << listaPedidos[pedidos].tipoProducto[producto] << "  Cantidad a retirar: " <<listaPedidos[pedidos].cantidad[producto] << endl;
        }
    }
    cout << "\n" << endl;

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

    listaCarrito[0].colaPedido.enqueue(&listaPedidos[0]);
    listaCarrito[1].colaPedido.enqueue(&listaPedidos[1]);

/*     int variableRandom;
    int array[2] = {0,1};
    for (int i = 0; i < 2; i++){
        variableRandom = rand()%2;
        while (true) {
            if (array[variableRandom]==-1){
                variableRandom = rand()%2;
            } else {
                int numeroCarrito=0;
                for (int i = 0; i < CANTIDAD_PEDIDOS; i++)
                {
                    pedido* pedidoAgregar = (pedido*)malloc(sizeof(pedido));
                    pedidoAgregar->numeroPedido = listaPedidos[variableRandom].numeroPedido;
                    if(numeroCarrito < CANTIDAD_MONTACARGAS){
                        listaCarrito[numeroCarrito].colaPedido.enqueue(pedidoAgregar);
                    } else {
                        numeroCarrito = 0;
                        listaCarrito[numeroCarrito].colaPedido.enqueue(pedidoAgregar);
                    }
                    numeroCarrito++;
                }
                array[variableRandom] = -1;
                break;
            }
        }
    } */

    for (int i = 0; i < CANTIDAD_MONTACARGAS; i++) {
        if (!listaCarrito[i].colaPedido.isEmpty()) {
            pedido pedidoVerificado = (*(pedido*)malloc(sizeof(pedido)));
            pedidoVerificado = (*(pedido*)listaCarrito[i].colaPedido.dequeue());
            cout << "Numero de pedido: " << pedidoVerificado.numeroPedido << endl;
            if (pedidoVerificado.estado == false){
                cout << "El estado del pedido es: pendiente" << endl;
            } else{
            cout << "El estado del pedido es: completado" << endl;
            }
            for (int j =0; j < 2; j++){
                cout << "Tipo de producto: " << pedidoVerificado.tipoProducto[j] << "   Cantidad: " << pedidoVerificado.cantidad[j] << endl;
            }
        }else {
            cout << "Este carrito esta vacio" << endl;
        }
    }

    for (int carritos = 0; carritos < CANTIDAD_MONTACARGAS; carritos++)
    {
        pedido pedidoSacar = (*(pedido*)malloc(sizeof(pedido)));
        pedidoSacar = (*(pedido*)listaCarrito[carritos].colaPedido.dequeue());
        if (!pedidoSacar.estado){
            for (int productos = 0; productos < CANTIDAD_PRODUCTOS; productos++)
            {
                int sacados = 0;
                for (int bodega = 0; bodega < CANTIDAD_COLUMNAS_TOTALES; bodega++)
                {
                    if (ListaBodega[bodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0){
                        //bodega arrayBodega[2] = {{"arroz",2,5,30},{"cerveza",3,3,100}};
                        int cantidadASacar = pedidoSacar.cantidad[productos];
                        for (; cantidadASacar > sacados ;)
                        {
                            if (!ListaBodega[bodega].columnas.isEmpty()){
                                int cantidadProcesada = (*(int*)malloc(sizeof(int)));
                                cantidadProcesada = (*(int*)ListaBodega[bodega].columnas.pop());
                                sacados += cantidadProcesada;
                            } else {
                                continue;
                            }
                        }
                        int diferencia = sacados-cantidadASacar;
                        // int* cantidad = (int*)malloc(sizeof(int));
                        // *cantidad = arrayBodega[producto].unidadesxPaleta;
                        if (diferencia != 0){
                            int* diferenciaAMeter = (int*)malloc(sizeof(int));
                            *diferenciaAMeter = diferencia;
                            ListaBodega[bodega].columnas.push(diferenciaAMeter);
                        }                                  
                    } else {
                        if (pedidoSacar.estado == false){
                            cout << pedidoSacar.numeroPedido << "esta incompleto, pero se hizo lo que se pudo :( " << endl;
                            /*
                                NOS FALTA REVISAR DEBAJO DE CADA FOR PARA VER LAS CONDICIONES TERMINANTES
                                
                            */
                        }
                    }

                }
                
                
            }
            
        }
    }
    




}