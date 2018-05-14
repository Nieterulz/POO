#include <iostream>
#include <iomanip>
#include "pedido-articulo.hpp"

std::ostream operator <<(std::ostream& os, const LineaPedido& LP)
{
	os << std::fixed << setprecision(2) << LP.precio_venta() << " €\t" << LP.cantidad() << endl; 
	return os;
}