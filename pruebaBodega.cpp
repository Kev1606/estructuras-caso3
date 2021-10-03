// TECNOLOGICO DE COSTA RICA //
/*

    Curso: Estructuras de Datos
    Profesor: Rodrigo Núñez Núñez
    Grupo: 04

    Caso #3
    Fecha: 03 de Octubre del 2021
    Autor: Kevin Vinicio Núñez Cruz (2021118002)
           Joctan Antonio Porras Esquivel (2021)

*/

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
            //cout << "Nombre de producto: " << ListaBodega[indiceBodega].nombreProducto << endl;
            //cout << "Columna: " << columna <<endl;

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
    listaPedidos[1] = {11,false,{"cerveza","arroz"},{850,90}};

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

    // se asignan los pedidos a la cola de pedidos de los carritos
    listaCarrito[0].colaPedido.enqueue(&listaPedidos[0]);
    listaCarrito[1].colaPedido.enqueue(&listaPedidos[1]);

/*     for (int i = 0; i < CANTIDAD_MONTACARGAS; i++) {
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
    } */

// LOGICA QUE EVALUA LAS COLAS DE PEDIDOS DE LOS MONTACARGAS Y COMPLETA DICHOS PEDIDOS
    for (int carritos = 0; carritos < CANTIDAD_MONTACARGAS; carritos++)
    {
        if (listaCarrito[carritos].colaPedido.isEmpty()) {
            cout << "Ya no quedan pedidos a realizarse" << endl;
            break;
        }
        bool parteTry = false;
        bool esCompleto = true;
        pedido pedidoSacar = (*(pedido*)malloc(sizeof(pedido)));
        pedidoSacar = (*(pedido*)listaCarrito[carritos].colaPedido.dequeue());
        int duracionMontacarga = 0;
        if (!pedidoSacar.estado){
            // listaPedidos[0] = {10,false,{"arroz","cerveza"},{300,100}};
            // listaPedidos[1] = {11,false,{"cerveza","arroz"},{750,90}};
            for (int productos = 0; productos < CANTIDAD_PRODUCTOS; productos++)
            {
                int sacados = 0;
                int cantidadASacar = pedidoSacar.cantidad[productos];
                int sumarIndiceBodega = 0;

                for (int bodega = 0; bodega < CANTIDAD_COLUMNAS_TOTALES; bodega++)
                {
                    if (ListaBodega[bodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0){
                        //bodega arrayBodega[2] = {{"arroz",2,5,30},{"cerveza",3,3,100}};
                        //cantidadASacar = pedidoSacar.cantidad[productos];
                        for (; cantidadASacar > sacados ;)
                        {
                            //cout << "momentos: " << sacados << endl;
                            if (!ListaBodega[bodega].columnas.isEmpty()){
                                int cantidadProcesada = (*(int*)malloc(sizeof(int)));
                                cantidadProcesada = (*(int*)ListaBodega[bodega].columnas.pop());
                                duracionMontacarga+= DURACION_BAJADA_SUBIDA;
                                //cout << "sumas: " << duracionMontacarga << endl;
                                sacados += cantidadProcesada;
                            } else {
                                try
                                {
                                    sumarIndiceBodega = 1;
                                    if (ListaBodega[bodega+sumarIndiceBodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0) {
                                        for (; cantidadASacar > sacados ;) {
                                            //cout << "momentos: "<< sacados << endl;
                                            if (!ListaBodega[bodega+sumarIndiceBodega].columnas.isEmpty()){
                                                if (ListaBodega[bodega+sumarIndiceBodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0){
                                                    int cantidadProcesada = (*(int*)malloc(sizeof(int)));
                                                    cantidadProcesada = (*(int*)ListaBodega[bodega+sumarIndiceBodega].columnas.pop());
                                                    //cout << "\ncuanto suma  \n" << cantidadProcesada << endl;
                                                    duracionMontacarga+= DURACION_BAJADA_SUBIDA;
                                                    //cout << "sumas: " << duracionMontacarga << endl;
                                                    sacados += cantidadProcesada;
                                                } else {
                                                    sacados = cantidadASacar;
                                                    parteTry = true;
                                                }
                                            } else {
                                                sumarIndiceBodega++;
                                            }
                                            //break;
                                        }
                                    }
                                }
                                catch(exception& e)
                                {
                                    esCompleto = false;
                                    parteTry = true;
                                }
                                           
                            }
                        }
                        int diferencia = sacados-cantidadASacar;
                        // int* cantidad = (int*)malloc(sizeof(int));
                        // *cantidad = arrayBodega[producto].unidadesxPaleta;
                        if (diferencia != 0 & diferencia > 0){
                            int* diferenciaAMeter = (int*)malloc(sizeof(int));
                            *diferenciaAMeter = diferencia;
                            ListaBodega[bodega+sumarIndiceBodega].columnas.push(diferenciaAMeter);
                            duracionMontacarga+= DURACION_BAJADA_SUBIDA;
                            esCompleto = true;
                            break;
                        } else {
                            if (!parteTry){
                                esCompleto = true;
                            } else{
                                esCompleto = false;
                            }
                            //esCompleto = true;
                            break;
                        }                                  
                    } else {
                        if (sacados < cantidadASacar){
                            esCompleto = false;
                        }
                    }
                }
                //cout << "salimos de producto   " << duracionMontacarga << endl;
            }
            if (esCompleto){
                cout << "El pedido numero: " << pedidoSacar.numeroPedido << "  Tardo en completarse: " << duracionMontacarga << " milisegundos" << endl;
            } else{
                cout << "El pedido numero: " << pedidoSacar.numeroPedido << "  Tardo, aunque no se completo todo: " << duracionMontacarga << " milisegundos" << endl;
            }
        }          
    }
}    