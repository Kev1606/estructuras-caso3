#include <iostream>

using namespace std;

struct pedido {
    int numeroPedido;
    bool estado;            // false estado pendiente y true estado completado
    string tipoProducto;        
    int cantidad;
};