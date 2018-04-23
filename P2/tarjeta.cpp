#include "tarjeta.hpp"

Tarjeta::Tarjeta(Tipo tipo, Numero num, Usuario user, Fecha caducidad)
{
	if(caducidad < Fecha(actual))
		throw Caducada::Caducada(caducidad);
	tipo_ = tipo;
	num_ = num;
	user_ = user;
	user_.es_titualr_de(*this);
	caducidad_ = caducidad;
}

void Tarjeta::anula_titular()
{
	user_ = nullptr;
}

Tarjeta::~Tarjeta()
{
	if(user_ != nullptr)
	{
		user_.no_es_titular_de(*this);
	}
}

std::ostream& operator <<(ostream& os, const Tarjeta& T)
{
	os << T.tipo() << "\n"
		<< T.numero() << "\n"
		<< T.titular() << "\n"
		<< "Caduca: " << T.caducidad().mes() << "/" << setw(2) << T.caducidad().anno() << "\n"; 

	/*os << "+----------------+\n"
	   << "| "<< setiosflags(ios::left) << setw(16) << T.tipo() << "|\n"
	   << "| "<< setiosflags(ios::left) << setw(16) << T.numero() << "|\n"
	   << "| "<< setiosflags(ios::left) << setw(16) << T.titular() << "|\n"
	   << "| Caduca: "<< setiosflags(ios::left) << setw(7) << T.caducidad() << "|\n"*/
	return os;
}

std::ostream& operator <<(ostream& os, const Tarjeta::Tipo& T)
{
	switch(T)
	{
		case VISA: os << "VISA"; break;
		case Mastercard: os << "Mastercard"; break;
		case Maestro: os << "Maestro"; break;
		case JCB: os << "JBC"; break;
		case AmericanExpress: os << "AmericanExpress"; break;
	}
	return os;
}

bool operator <(const Tarjeta& A, const Tarjeta& B)
{
	return(A.numero()<B.numero());
}