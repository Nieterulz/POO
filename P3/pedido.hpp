#ifndef PEDIDO_HPP
#define PEDIDO_HPP

class Pedido
{
public:
	Pedido(const Usuario_Pedidos U_P, const Pedido_Articulo P_A, const Usuario& usuario, const Tarjeta& tarjeta, const Fecha& fecha = Fecha());
	int numero() const{return numero_;}
	const Tarjeta* tarjeta(){return tarjeta_;}
	Fecha fecha() const{return fecha_;}
	double total() const{return total_;}
	class Vacio
	{
	public:
		Vacio(const Usuario* usuario):usuario_(usuario){}
		Usuario* usuario() const{return usuario_;}
	private:
		Usuario* usuario_;
	};
	class Impostor
	{
	public:
		Impostor(const Usuario* usuario):usuario_(usuario){}
		Usuario* usuario() const{return usuario_;}
	private:
		Usuario* usuario_;
	};
	class SinStock
	{
	public:
		SinStock(const Articulo* articulo):articulo_(articulo){}
		Articulo* articulo() const{return articulo_;}
	private:
		Articulo *articulo_;
	};
private:	
	static int N_pedidos;
	int num_;
	Tarjeta* tarjeta_;
	Fecha fecha_;
	double total_;
};

std::ostream operator <<(std::ostream& os, const Pedido& P)

#endif