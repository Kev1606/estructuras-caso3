// TECNOLOGICO DE COSTA RICA //
/*

    Curso: Estructuras de Datos
    Profesor: Rodrigo Núñez Núñez
    Grupo: 04

    Caso #3
    Fecha: 03 de Octubre del 2021
    Autor: Kevin Vinicio Núñez Cruz (2021118002)
           Joctan Antonio Porras Esquivel (2021069671)

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

    for (int producto = 0; producto < CANTIDAD_PRODUCTOSXPEDIDO; producto++)
    {
        for (int columna = 0; columna < arrayBodega[producto].columnasxTipo; columna++)
        {
            ListaBodega[indiceBodega].nombreProducto = arrayBodega[producto].tipoProducto;

            for (int unidades = 0; unidades < arrayBodega[producto].paletasxColumna; unidades++)
            {
                int* cantidad = (int*)malloc(sizeof(int));
                *cantidad = arrayBodega[producto].unidadesxPaleta;
                ListaBodega[indiceBodega].columnas.push(cantidad);
            }
            indiceBodega++;
        }
    }

    cout << "\n" << endl;

    pedido listaPedidos[CANTIDAD_PEDIDOS];
    listaPedidos[0] = {10,false,{"arroz","cerveza"},{60,200}};
    listaPedidos[1] = {11,false,{"cerveza","arroz"},{450,90}};
    listaPedidos[2] = {12,false,{"cerveza","arroz"},{300,15}};
    listaPedidos[3] = {13,false,{"arroz","cerveza"},{15,50}};

    for (int pedidos = 0; pedidos < CANTIDAD_PEDIDOS; pedidos++){
        cout << "Numero de pedido: " <<listaPedidos[pedidos].numeroPedido << endl;
        if (listaPedidos[pedidos].estado == false){
            cout << "El estado del pedido es: pendiente" << endl;
        } else{
            cout << "El estado del pedido es: completado" << endl;
        }
        for (int producto = 0; producto < CANTIDAD_PRODUCTOSXPEDIDO; producto++) {
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
    listaCarrito[2].colaPedido.enqueue(&listaPedidos[2]);
    listaCarrito[0].colaPedido.enqueue(&listaPedidos[3]);

// LOGICA QUE EVALUA LAS COLAS DE PEDIDOS DE LOS MONTACARGAS Y COMPLETA DICHOS PEDIDOS
    //ciclo que recorre la lista de montacargas
    for (int carritos = 0; carritos < CANTIDAD_MONTACARGAS; carritos++)
    {
        //Revisa si las colas de los carritos estan vacias
        for (; listaCarrito[carritos].colaPedido.isEmpty() == false;) {
            bool saleDeTry = false;
            bool esCompleto = true;
            pedido pedidoSacar = (*(pedido*)malloc(sizeof(pedido)));
            pedidoSacar = (*(pedido*)listaCarrito[carritos].colaPedido.dequeue());
            int duracionMontacarga = 0;     //lo que dura cada montacarga en subir y bajar pedidos
            if (!pedidoSacar.estado){

                //ciclo que recorre los productos de la cola de pedidos
                for (int productos = 0; productos < CANTIDAD_PRODUCTOSXPEDIDO; productos++)
                {
                    int sacados = 0;    //acumulador de la cantidad del producto que se va sacando
                    int cantidadASacar = pedidoSacar.cantidad[productos];   //cantidad del producto necesitado en el pedido
                    int sumarIndiceBodega = 0;  //variable que funciona a la hora de que la columna este vacia

                    //ciclo que recorre las columnas de la bodega
                    for (int bodega = 0; bodega < CANTIDAD_COLUMNAS_TOTALES; bodega++)
                    {
                        //pregunta si el nombre del producto es igual al tipo de producto a sacar en el pedido
                        if (ListaBodega[bodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0){ 
                            //ciclo que pregunta si la cantidad necesitada del producto en el pedido es mayor a la cantidad que estamos sacando
                            for (; cantidadASacar > sacados ;)
                            {
                                //pregunta si la columna donde estamos esta vacia
                                if (!ListaBodega[bodega].columnas.isEmpty()){
                                    int cantidadProcesada = (*(int*)malloc(sizeof(int)));
                                    cantidadProcesada = (*(int*)ListaBodega[bodega].columnas.pop());  //sacamos una paleta
                                    duracionMontacarga+= DURACION_BAJADA_SUBIDA;    //aumentamos la duracion del montacarga
                                    sacados += cantidadProcesada;   //le sumamos la paleta a la cantidad que vamos sacando
                                } else {
                                    try
                                    {
                                        sumarIndiceBodega = 1;  //seteamos a 1 para avanzar de columna
                                        // este bloque revisa la siguiente columna
                                        if (ListaBodega[bodega+sumarIndiceBodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0) {
                                            for (; cantidadASacar > sacados ;) {
                                                if (!ListaBodega[bodega+sumarIndiceBodega].columnas.isEmpty()){
                                                    if (ListaBodega[bodega+sumarIndiceBodega].nombreProducto.compare(pedidoSacar.tipoProducto[productos]) == 0){
                                                        int cantidadProcesada = (*(int*)malloc(sizeof(int)));
                                                        cantidadProcesada = (*(int*)ListaBodega[bodega+sumarIndiceBodega].columnas.pop());
                                                        duracionMontacarga+= DURACION_BAJADA_SUBIDA;
                                                        sacados += cantidadProcesada;
                                                    } else {
                                                        sacados = cantidadASacar;   //a esta altura la columna esta vacia (sin paletas)
                                                        saleDeTry = true;           //es para que el pedido quede incompleto
                                                    }
                                                } else {
                                                    // si esta vacia la columna avanza a la siguiente
                                                    sumarIndiceBodega++;
                                                    //pregunta si la columna siguiente no existe 
                                                    if (bodega+sumarIndiceBodega == CANTIDAD_COLUMNAS_TOTALES){
                                                        throw (0);  //envia la ejecucion al catch
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    catch(int e)
                                    {
                                        esCompleto = false;     //el pedido estaria incompleto
                                        saleDeTry = true;
                                        sacados = cantidadASacar;
                                    }
                                            
                                }
                            }
                            int diferencia = sacados-cantidadASacar;  
                            //se verifica si la diferencia es 0 y si no le hace un push de esa cantidad a la columna correspondiente
                            if (diferencia != 0 & diferencia > 0){
                                int* diferenciaAMeter = (int*)malloc(sizeof(int));
                                *diferenciaAMeter = diferencia;
                                ListaBodega[bodega+sumarIndiceBodega].columnas.push(diferenciaAMeter);
                                duracionMontacarga+= DURACION_BAJADA_SUBIDA;    //y suma el mismo valor de duracion
                                //verificamos si todos los productos del pedido se completaron
                                if (esCompleto == false){
                                    //nothing
                                } else {
                                    esCompleto = true;
                                }                    
                                break;
                            } else {
                                //verifica si sale del try entonces salio incompleto
                                if (!saleDeTry){
                                    esCompleto = true;
                                } else{
                                    esCompleto = false;
                                }
                                break;
                            }                                  
                        }
                    }
                }
                //Respuestas finales con base a los pedidos
                if (esCompleto){
                    cout << "El pedido numero: " << pedidoSacar.numeroPedido << "  Tardo en completarse: " << duracionMontacarga << " milisegundos" << endl;
                } else{
                    cout << "El pedido numero: " << pedidoSacar.numeroPedido << "  Tardo, aunque no se completo todo: " << duracionMontacarga << " milisegundos" << endl;
                }
            }
        }
        if (listaCarrito[carritos].colaPedido.isEmpty()) {
                cout << "Ya no quedan pedidos a realizarse en el carrito\n" << endl;
            }          
    }
    cout << "Ya no quedan carritos" << endl;
}    