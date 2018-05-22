#include <iostream>
#include <iomanip>
#include "pedido.hpp"

class Pedido;

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& U_P, Pedido_Articulo& P_A, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha)
	:num_(N_pedidos +1), tarjeta_(&tarjeta), fecha_(fecha), total_(0)
{
	if(usuario.n_articulos() == 0)
		throw Vacio(usuario); //¿Carrito vacio?
	if(tarjeta.titular() != &usuario)
		throw Impostor(usuario); //¿Tarjeta mangada?
	if(tarjeta.caducidad() < fecha)
		throw Tarjeta::Caducada(tarjeta.caducidad()); // Tarjeta
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
		P_A.pedir(*this, *pa, precio, cantidad);
		total_ += precio*cantidad;
		usuario.compra(*pa, 0);
	}
	U_P.asocia(usuario, *this);
	++N_pedidos;
}

std::ostream& operator <<(std::ostream& os, const Pedido& P)
{
	os << "Núm. pedido: " << P.numero() << "\n"
	   << "Fecha:       " << P.fecha() << "\n"
	   << "Pagado con:  " << *P.tarjeta() << "\n"
	   << "Importe:     " << std::fixed << std::setprecision(2) << P.total() << " €";
	return os;
}
