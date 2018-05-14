#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <map>
#include <functional>

class Pedido_Articulo
{
public:
	struct EsDigito:public std::unary_function<char, bool>
	{
		bool operator()(char c){return issdigit(c)}
	}


	struct OrdenaArticulos:public std::unary_function<>
	{
		
	}

	typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
	typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> pedido_a_articulo;
	typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
	typedef std::map<Articulo*, Pedidos, OrdenaArticulos> articulo_a_pedido;

	Pedido_Articulo();
private:

};

class LineaPedido
{
public:
	explicit LineaPedido(double precio_venta, unsigned cantidad = 1):precio_venta_(precio_venta), cantidad_(cantidad){}
	double precio_venta() const{return precio_venta_;}
	unsigned cantidad() const{return cantidad_;}
private:
	double precio_venta_;
	unsigned cantidad_;
};

std::ostream operator <<(std::ostream& os, const LineaPedido& LP);

#endif