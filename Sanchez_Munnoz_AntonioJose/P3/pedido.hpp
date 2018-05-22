#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido
{
public:
	Pedido(Usuario_Pedido& U_P, Pedido_Articulo& P_A, Usuario& usuario,const Tarjeta& tarjeta, const Fecha& fecha = Fecha());
	int numero() const{return num_;}
	const Tarjeta* tarjeta() const {return tarjeta_;}
	Fecha fecha() const{return fecha_;}
	double total() const{return total_;}
	static int n_total_pedidos(){return N_pedidos;}
	class Vacio
	{
	public:
		Vacio(Usuario& usuario):usuario_(&usuario){}
		Usuario& usuario() const{return *usuario_;}
	private:
		Usuario* usuario_;
	};
	class Impostor
	{
	public:
		Impostor(Usuario& usuario):usuario_(&usuario){}
		Usuario& usuario() const{return *usuario_;}
	private:
		Usuario* usuario_;
	};
	class SinStock
	{
	public:
		SinStock(Articulo& articulo):articulo_(&articulo){}
		Articulo& articulo() const{return *articulo_;}
	private:
		Articulo *articulo_;
	};
private:
	static int N_pedidos;
	int num_;
	const Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& P);

#endif
