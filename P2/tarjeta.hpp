#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"
#include "numero.hpp"


class Tarjeta
{
public:
	enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};
	Tarjeta(Tipo tipo, Numero num, Usuario user, Fecha caducidad);
	Tarjeta(const Tarjeta& T) = delete;
	class Caducada
	{
	public:
		Caducada(Fecha f):f_(f){}
		const Fecha cuando() const{return f_;};
	private:
		Fecha f_;
	};
	Tipo tipo() const{return tipo_;}
	Numero numero() const {return num_;}
	Usuario titular() const {return user_;}
	Fecha caducidad() const {return caducidad_;}
	Cadena titular_facial() const {return titular_facial_;}
	void anula_titular();

	~Tarjeta();
private:
	Tipo tipo_;
	Numero num_;
	const Usuario* user_;
	Fecha caducidad_;
	Cadena titular_facial_;

};

#endif