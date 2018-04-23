#ifndef CLAVE_HPP
#define CLAVE_HPP

#include "cadena.hpp"

class Clave
{
public:
	enum Razon{CORTA, ERROR_CRYPT};
	Clave(const char* s); //Recibe una contraseña sin cifrar
	Cadena clave() const;
	bool verifica(const char* clara);
	class Incorrecta
	{
	public:
		Incorrecta(const Razon r):fallo_(r){};
		Razon razon() const;
	private:
		Razon fallo_;
	};
private:
	Cadena clave_; //contraseña cifrada
};

inline Cadena Clave::clave() const
{return clave_;}

inline Clave::Razon Clave::Incorrecta::razon() const
{return fallo_;}


#endif