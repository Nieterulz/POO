#include "tarjeta.hpp"

/***************************************NUMERO************************************************/
bool luhn(const Cadena& numero);
Numero::Numero(Cadena C)
{
	int spaces = 0;
	for(int i = 0; i<C.length(); i++)
	{
		if(std::isspace(C[i]) || C[i] == '\v' || C[i] == '\r' || C[i] == '\t' || C[i] == '\n')
		{
			spaces++;
			for(int j=i; j<C.length(); j++)
			{
				C[j] = C[j+1];
			}
			i--;
		}
	}

	char *tmp = new char[C.length() - spaces +1];
	strcpy(tmp, C.c_str());
	for(int i=0; i<strlen(tmp); i++)
	{
		if(tmp[i] < '0' || tmp[i] > '9')
		{
			throw Incorrecto(Razon::DIGITOS);
		}
	}

  	if(strlen(tmp)< 13 || strlen(tmp) > 19)
  		throw Incorrecto(Razon::LONGITUD);
  	if(!luhn(tmp))
  		throw Incorrecto(Razon::NO_VALIDO);
	num_ = tmp;
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
		throw Caducada::Caducada(caducidad);
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