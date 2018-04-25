#include "tarjeta.hpp"

/***************************************NUMERO************************************************/
bool luhn(const Cadena& numero);


Numero::Numero(const Cadena& C)
{
	Cadena AUX(C);
	
	for(int i=0; i<AUX.length(); i++)
	{
		if((AUX[i] < '0' || AUX[i] > '9') && AUX[i] != '\0')
			throw Incorrecto(DIGITOS);

		if(AUX[i] == ' ')
		{
			for(int j = i; j<AUX.length(); j++)
				AUX[j] = AUX[j+1];
			i--;
		}
	}

	if(AUX.length() < 13 || AUX.length() > 19)
		throw Incorrecto(LONGITUD);

	num_ = AUX;

	if(!luhn(num_))
		throw Incorrecto(NO_VALIDO);
}

bool operator <(const Numero& A, const Numero& B)
{
	return (strcmp(A, B) < 0);
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
		<< T.titular() << "\n"
		<< "Caduca: " << std::setfill('0') << std::setw(2) << T.caducidad().mes() << "/" << std::setw(2) << T.caducidad().anno() << "\n"; 

	/*os << "+----------------+\n"
	   << "| "<< setiosflags(ios::left) << setw(16) << T.tipo() << "|\n"
	   << "| "<< setiosflags(ios::left) << setw(16) << T.numero() << "|\n"
	   << "| "<< setiosflags(ios::left) << setw(16) << T.titular() << "|\n"
	   << "| Caduca: "<< setiosflags(ios::left) << setw(7) << T.caducidad() << "|\n"*/
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
	return(A.numero()<B.numero());
}