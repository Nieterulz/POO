#include "tarjeta.hpp"

/***************************************NUMERO************************************************/
bool luhn(const Cadena& numero);

Numero::Numero(const Cadena& C)
{
	char* aux = new char[C.length()+1];
	strcpy(aux, C.c_str());
	
	for(int i=0; i<aux.length(); i++)
	{
		if((aux[i] < '0' || aux[i] > '9') && aux[i] != '\0')
			throw Incorrecto(DIGITOS);

		if(aux[i] == ' ')
		{
			for(int j = i; j<aux.length(); j++)
				aux[j] = aux[j+1];
			i--;
		}
	}

	if(strlen(aux) < 13 || strlen(aux) > 19)
		throw Incorrecto(LONGITUD);

	num_(Cadena(aux));

	if(!luhn(num_))
		throw Incorrecto(NO_VALIDO);
}

bool operator <(const Numero& A, const Numero& B)
{
	return (strcmp(A, B) < 0);
}

/***************************************TARJETA************************************************/
Tarjeta::Tarjeta(const Tipo tipo, const Numero& num, const Usuario& user, const Fecha& caducidad)
	tipo_(tipo), num_(num), user_(nullptr) 
{
	user_.es_titular_de(*this);
	if(caducidad < Fecha(actual))
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
		user_.no_es_titular_de(*this);
	}
}

std::ostream& operator <<(ostream& os, const Tarjeta& T)
{
	os << T.tipo() << "\n"
		<< T.numero() << "\n"
		<< T.titular() << "\n"
		<< "Caduca: " << setfill(0) << setw(2) << T.caducidad().mes() << "/" << setw(2) << T.caducidad().anno() << "\n"; 

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