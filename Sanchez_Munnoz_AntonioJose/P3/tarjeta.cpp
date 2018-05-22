#include <cctype>
#include "tarjeta.hpp"
/***************************************NUMERO************************************************/

bool luhn(const Cadena& numero);
Numero::Numero(Cadena C):num_(longCheck(C))
{

	std::function<bool (char)> NoEsDigito = [](char c)->bool{ return !EsDigito()(c); };
	if(std::find_if(num_.begin(), num_.end(), NoEsDigito) != num_.end())
		throw Incorrecto(Razon::DIGITOS);
  if(!luhn(num_))
  	throw Incorrecto(Razon::NO_VALIDO);
}

Cadena quitar_espacios(const Cadena& C)
{
	Cadena aux(C) ;
	std::remove_if(aux.begin(),aux.end()+1,EsBlanco());
	return Cadena(aux.c_str()) ;

}

Cadena longCheck(const Cadena& A)
{
	Cadena aux = quitar_espacios(A) ;
 	if(aux.length() < 13||aux.length()>19)
 		throw Numero::Incorrecto(Numero::Razon::LONGITUD);
	return aux ;
}

bool operator <(const Numero& A, const Numero& B)
{
	if(strcmp(A, B) < 0)
		return true;
	else
		return false;
}
/***************************************TARJETA************************************************/
Tarjeta::Tarjeta(const Tipo tipo, const Numero& num, Usuario& user, const Fecha& caducidad):
	tipo_(tipo), num_(num), user_(&user), caducidad_(caducidad), titular_facial_(user.nombre()+" "+user.apellidos())
{
	Fecha actual;
	user.es_titular_de(*this);
	if(caducidad < actual)
		throw Caducada(caducidad);
}

void Tarjeta::anula_titular()
{
	user_ = nullptr;
}

Tarjeta::~Tarjeta()
{
	if(user_ != nullptr)
	{
		Usuario* us = const_cast<Usuario*>(user_);
		us->no_es_titular_de(*this);
	}
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& T)
{
	os << T.tipo() << "\n"
		<< T.numero() << "\n"
		<< T.titular_facial() << "\n"
		<< "Caduca: " << std::setfill('0') << std::setw(2) << T.caducidad().mes() << "/" << std::setw(2)
		<< (T.caducidad().anno())%100 << "\n";

	return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& T)
{
	switch(T)
	{
		case Tarjeta::Tipo::VISA: os << "VISA"; break;
		case Tarjeta::Tipo::Mastercard: os << "Mastercard"; break;
		case Tarjeta::Tipo::Maestro: os << "Maestro"; break;
		case Tarjeta::Tipo::JCB: os << "JBC"; break;
		case Tarjeta::Tipo::AmericanExpress: os << "AmericanExpress"; break;
	}
	return os;
}

bool operator <(const Tarjeta& A, const Tarjeta& B)
{
	return(A.numero() < B.numero());
}
