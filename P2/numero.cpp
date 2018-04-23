#include <cstring>
#include <cstddef>
#include "numero.hpp"

bool luhn(const Cadena& numero);

Numero::Numero(const Cadena& C)
{
	char* aux = new char[C.length()+1];
	strcpy(aux, C.c_str());
	
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