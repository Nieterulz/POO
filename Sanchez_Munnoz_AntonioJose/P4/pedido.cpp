#include <iostream>
#include <iomanip>
#include "pedido.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& U_P, Pedido_Articulo& P_A, Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha)
	:num_(N_pedidos +1), tarjeta_(&tarjeta), fecha_(fecha), total_(0)
{
	if(usuario.n_articulos() == 0) throw Vacio(usuario);
	if(tarjeta.titular() != &usuario) throw Impostor(usuario);
	if(tarjeta.caducidad() < fecha) throw Tarjeta::Caducada(tarjeta.caducidad()); // Tarjeta

	Usuario::Articulos carro = usuario.compra();
	bool pedido_final_vacio = true;
	for(auto c : carro) //c es un pair<Articulo*,unsigned(cantidad)>
	{
		Articulo* pa = c.first;
		unsigned int cantidad = c.second;
		if(ArticuloAlmacenable* aa =  dynamic_cast<ArticuloAlmacenable* const>(pa))
		{
			if(aa->stock() < cantidad)
			{
				const_cast<Usuario::Articulos&>(usuario.compra()).clear();
				throw SinStock(*c.first);
			}
			double precio = pa->precio();
			aa->stock() -= cantidad;
			P_A.pedir(*this, *aa, precio, cantidad);
			total_ += precio*cantidad;
			pedido_final_vacio = false;
		}
		else //No es un ArticuloAlmacenable
			if(LibroDigital* ld = dynamic_cast<LibroDigital*>(pa))
			{
				if(ld->f_expir() > fecha)
				{
					total_ += (ld->precio() * cantidad);
					P_A.pedir(*this, *ld, ld->precio(), cantidad);
					pedido_final_vacio = false;
				}
			}
			else
				throw std::logic_error("Pedido::Pedido: error, tipo de Articulo desconocido");
			usuario.compra(*(c.first),0);
	}
	if(pedido_final_vacio)
		throw Vacio(usuario);
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
