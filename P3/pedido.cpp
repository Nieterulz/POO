#include <iostream>
#include <iomanip>
#include "pedido.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedidos U_P, Pedido_Articulo& P_A, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha)
	:num_(N_pedidos +1), tarjeta_(&tarjeta), fecha_(fecha), total_(0)
{
	if(usuario.n_articulos() == 0)
		throw Vacio(u); //¿Carrito vacio?
	if(tarjeta.titular() != &u)
		throw Impostor(u); //¿Tarjeta mangada?
	if(tarjeta.caducidad() < fp)
		throw Tarjeta::Caducada(tarjeta.caducidad()); // Tarjeta cad
	for(auto c : usuario.compra()) //c es un elemento del map => (pair<Articulo*, unsigned>) 
		if(c.first->stock() < c.second) //No hay bastante en el almacén
		{
			const_cast<Usuario::Articulos&>(usuario.compra()).clear();
			throw SinStock(*c.first);
		}
	Usuario::Articulos carro = usuario.compra();
	for(auto c : carro)
	{
		Articulo* pa = c.first;
		unsigned int cantidad = c.second;
		double precio = pa->precio();
		pa->stock() -= cantidad;
		Pedido_Articulo.pedir(*this, *pa, precio, cantidad);
		total_ += precio*cantidad;
		usuario.compra(*pa, 0);
	}
	U_P.asocia(usuario, *this);
	++N_pedidos;
}
	
std::ostream operator <<(std::ostream& os, const Pedido& P)
{
	os << "Núm. pedido: " << P.numero() << "\n"
	   << "Fecha:" << setfill(' ') << setw(7) << P.fecha() << "\n"
	   << "Pagado con:" << setfill(' ') << setw(1) << P.tarjeta() << "\n"
	   << "Importe:" << setfill(' ') << setw(5) << P.total() << "\n";
	return os;
}