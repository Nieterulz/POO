#ifndef NUMERO_HPP
#define NUMERO_HPP

#include "cadena.hpp"

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

#endif