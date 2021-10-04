# estructuras-caso3

Estructuras de Datos Lineales

Descripción: 
    Las  bodegas  en  las  distribuidoras  de  productos  normalmente  son  altas  columnas  de  algun  producto  apilados  en 
paletas.  Las  distribuidoras  en  la  mañana  toman  los  pedidos  que  indican  todos  los  productos  que  deben  alistarse. 
Dicha orden es tomada por un montacarga que se dirige a la columna en la bodega, saca la cantidad de paletas que 
sea  necesario  para  completar  el  pedido  y  vuelve  a  poner  en  la  columna  lo  que  sobra  en  la  paleta.  Si  completa  el 
pedido lo marca como terminado y si falta cantidad para cierto producto lo marca como incompleto.

Funcionamiento del programa:
Su programa inicialmente debe recorrer la lista de pedidos y aleatoriamente distribuir todos los pedidos entre los montacargas, metiendo cada orden en la cola respectiva de cada montacarga. Seguidamente en un bucle cada montacarga saca el pedidoa procesar, recorriendo los productos que debe completar, selecciona la pilarespectiva y procede a sacar las paletas de la pila para completar la cantidad solicitada en el pedidode cada producto, cada montacarga dura subiendo y bajando las paletas (push y pop) el tiempo en milisegundos especificado. Si no hay suficiente producto se procede con el siguiente producto hasta terminarlos y se marca el pedido como incompleto, de lo contrario queda en estado completo.

Una vez que hayan terminado todos los montacargas (todos los pedidos), se imprime en pantalla para cada pedido su estado y la cantidad de milisegundos que se demoró en completarse
