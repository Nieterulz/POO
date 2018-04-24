#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>
#include "fecha.hpp"
#include "cadena.hpp"

class Usuario;

class Numero
{
public:
	enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
	Numero(const Cadena& C);
	operator const char*() const{return num_.c_str();}
	class Incorrecto
	{
	public:
		Incorrecto(const Razon& r):r_(r){}
		Razon razon() const {return r_;}
	private:
		Razon r_;	
	};
private:
	Cadena num_;
};

class Tarjeta
{
public:
	enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};
	Tarjeta(const Tipo tipo, const Numero& num, const Usuario& user, const Fecha& caducidad);
	Tarjeta(const Tarjeta& T) = delete;
	Tarjeta& operator =(const Tarjeta& T) = delete;
	class Caducada
	{
	public:
		Caducada(Fecha f):f_(f){}
		const Fecha cuando() const{return f_;}
	private:
		Fecha f_;
	};
	Tipo tipo() const{return tipo_;}
	Numero numero() const {return num_;}
	const Usuario* titular() const {return user_;}
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