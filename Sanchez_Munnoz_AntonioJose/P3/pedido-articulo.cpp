#include <iostream>
#include <iomanip>
#include "pedido-articulo.hpp"

bool Pedido_Articulo::OrdenaArticulos::operator() (const Articulo* A, const Articulo* B) const
{
	return A->referencia() < B->referencia();
}

bool Pedido_Articulo::OrdenaPedidos::operator() (const Pedido* A, const Pedido* B) const
{
	return A->numero() < B->numero();
}

std::ostream& operator <<(std::ostream& os, const LineaPedido& LP)
{
	os << std::fixed << std::setprecision(2) << LP.precio_venta() << " €\t" << LP.cantidad();
	return os;
}

void Pedido_Articulo::pedir(Pedido& P, Articulo& A, double precio, unsigned cantidad)
{
	pe_art_[&P].insert(std::make_pair(&A, LineaPedido(precio, cantidad)));
	art_pe_[&A].insert(std::make_pair(&P,LineaPedido(precio,cantidad)));
}

void Pedido_Articulo::pedir(Articulo& A, Pedido& P, double precio, unsigned cantidad)
{
	pedir(P, A, precio, cantidad);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& P)
{
	return pe_art_[&P];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& A)
{
	return art_pe_[&A];
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream &os)
{
	double total_ventas = 0.0;
	for(auto i = pe_art_.begin(); i != pe_art_.end(); i++)
	{
		os << "Pedido núm. " << i->first->numero() << "\n"
			 << "Cliente: " << i->first->tarjeta()->titular()->nombre()
			 << "Fecha: " << i->first->fecha() << "\n"
			 << i->second;
			 total_ventas += i->first->total();
	}
	os << "TOTAL VENTAS\t" << total_ventas << " €";
	return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream &os)
{
	for(auto i = art_pe_.begin(); i != art_pe_.end(); i++)
	{
		os << "Ventas de [" << i->first->referencia() << "] \"" << i->first->titulo() << "\"\n"
		 	 << i->second;
	}
	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP)
{
	double total = 0.0;
	os << "  PVP   Cantidad        Artículo\n"
		 << "==================================================================\n";
	for(auto i = IP.begin(); i != IP.end(); i++)
	{
		os << i->second.precio_venta() << " € " << i->second.cantidad() << "               [" << i->first->referencia() << "] \""
			<< i->first->titulo() << "\"\n";
		total += (i->second.precio_venta()*i->second.cantidad());
	}
	os << "==================================================================\n"
		 << "Total   " << total << " €" << "\n";
	return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& P)
{
	double precio_total = 0.0;
	int cantidad_total = 0;
	os << "[Pedidos: " << P.size() << "]\n"
	 	 << "==================================================================\n"
		 << "  PVP   Cantidad        Fecha de venta\n";
	for(auto const &i : P)
	{
		os << i.second << "         " << i.first->fecha() << "\n";
		precio_total += (i.second.precio_venta() * i.second.cantidad());
		cantidad_total += i.second.cantidad();
	}
	os << "==================================================================\n"
		 << precio_total << " €       " << cantidad_total << "\n";

	return os;
}
