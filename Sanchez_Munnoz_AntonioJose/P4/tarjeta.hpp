#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <functional>
#include "usuario.hpp"
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Usuario;

struct EsBlanco:public std::unary_function<char, bool>
{
	bool operator()(char c){return isspace(c);};
};

struct EsDigito:public std::unary_function<char, bool>
{
	bool operator()(char c){return isdigit(c);};
};

class Numero
{
public:
	enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
	Numero(Cadena C);
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

Cadena longCheck(const Cadena& A);
Cadena quitar_espacios(const Cadena& A);

class Tarjeta
{
public:
	enum Tipo{VISA, Mastercard, Maestro, JCB, AmericanExpress};
	Tarjeta(const Tipo tipo, const Numero& num, Usuario& user, const Fecha& caducidad);
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

bool operator <(const Tarjeta& A, const Tarjeta& B);
bool operator <(const Numero& A, const Numero& B);
std::ostream& operator <<(std::ostream& os, const Tarjeta& T);
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& T);

#endif
