#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <map>
#include <functional>
#include "articulo.hpp"
#include "pedido.hpp"

class Pedido;

class LineaPedido
{
public:
	explicit LineaPedido(double precio_venta, unsigned int cantidad = 1):precio_venta_(precio_venta), cantidad_(cantidad){}
	double precio_venta() const{return precio_venta_;}
	unsigned cantidad() const{return cantidad_;}
private:
	double precio_venta_;
	unsigned int cantidad_;
};

std::ostream& operator <<(std::ostream& os, const LineaPedido& LP);

class Pedido_Articulo
{
public:
	struct OrdenaArticulos: public std::binary_function<Articulo*, Articulo*, bool>
	{
		bool operator() (const Articulo* A, const Articulo* B) const;
	};

	struct OrdenaPedidos: public std::binary_function<Pedido*, Pedido*, bool>
	{
		bool operator() (const Pedido* A, const Pedido* B) const;
	};
	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedido_a_articulo;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
	typedef std::map<Articulo*, Pedidos, OrdenaArticulos> articulo_a_pedido;

	void pedir(Pedido& P, Articulo& A, double precio, unsigned cantidad=1);
	void pedir(Articulo& A, Pedido& P, double precio, unsigned cantidad=1);
	const ItemsPedido& detalle(Pedido& P);
	Pedidos ventas(Articulo& A);
	std::ostream& mostrarDetallePedidos(std::ostream &os);
	std::ostream& mostrarVentasArticulos(std::ostream &os);

private:
	pedido_a_articulo pe_art_;
	articulo_a_pedido art_pe_;
};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& IP);
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& P);

#endif
