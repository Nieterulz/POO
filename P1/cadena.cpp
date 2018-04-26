#include <iostream>
#include <cstring>
#include <stdexcept>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(unsigned tam, char c) noexcept:
	s_{new char[tam+1]}, tam_{tam}
{
	unsigned i;

	for(i=0; i < tam_; i++)
	{
		s_[i] = c;
	}
	s_[i] = '\0';
}

Cadena::Cadena(const char* s) noexcept:
	tam_{(unsigned)strlen(s)}
{
	s_ = new char[tam_+1];
	strcpy(s_, s);
}

Cadena::Cadena(const Cadena& C) noexcept:
	s_{new char[C.tam_+1]}, tam_{C.tam_}
{
	strcpy(s_, C.s_);
}

Cadena::Cadena(Cadena&& C):s_(C.s_), tam_(C.tam_)
{
	C.s_ = nullptr;
	C.tam_ = 0;
}

Cadena& Cadena::operator=(Cadena&& C)
{
	if(*this != C)
	{
		tam_ = C.tam_;
		s_ = C.s_;
		C.s_ = nullptr;
		C.tam_ = 0;
	}

	return *this;
}

Cadena& Cadena::operator=(const Cadena& C) noexcept
{
	if(*this != C)
	{		
		tam_ = C.tam_;
		delete[] s_;
		s_ = new char[tam_+1];
		strcpy(s_, C.s_);
	}
	return *this;
}

Cadena& Cadena::operator=(const char* s) noexcept
{
	tam_ = strlen(s);
	delete[] s_;
	s_ = new char[tam_+1];
	strcpy(s_, s);
	return *this;
}

Cadena& Cadena::operator+=(const Cadena& C) noexcept
{
	char *aux = new char[tam_+1];
	strcpy(aux, s_);
	delete[] s_;
	s_ = new char[tam_+C.tam_+1];
	tam_ += C.tam_;
	strcpy(s_, aux);
	delete[] aux;
	strcat(s_, C.s_);

	return *this;
}

char Cadena::at(unsigned i) const
{
	if(i <= tam_ && s_[i] != '\0')
		return s_[i];

	throw out_of_range("Error. Índice fuera del rango de la cadena.");
}

char& Cadena::at(unsigned i)
{
	if(i <= tam_ && s_[i] != '\0')
		return s_[i];

	throw out_of_range("Error. Índice fuera del rango de la cadena.");	
}

Cadena Cadena::substr(unsigned i, unsigned t) const
{
	if(i < tam_)
	{
		if(tam_-i >= t)
		{
			Cadena aux{t};
			unsigned j=0;
			for(j=0; j<t; j++)
			{
				aux.s_[j] = s_[i+j];
			}
			aux.s_[j] = '\0';

			return aux;
		}
		else
			throw out_of_range("Error. La subcadena pedida se sale de los límites de la cadena.");
	}
	else
		throw out_of_range("Error. Posición inicial después del último caracter.");
}

Cadena operator+(const Cadena& A, const Cadena& B) noexcept
{
	char *aux = new char[A.length() + B.length() + 1];
	strcpy(aux,A.c_str());
	strcat(aux, B.c_str());
	Cadena C{aux};
	delete[] aux;
	return C;
}

bool operator<(const Cadena& A, const Cadena& B) noexcept
{
	if(strcmp(A.c_str(), B.c_str()) < 0)
		return true;
	else
		return false;
}

bool operator>(const Cadena& A, const Cadena& B) noexcept
{
	return (B < A);
}

bool operator==(const Cadena& A, const Cadena& B) noexcept
{
	if(strcmp(A.c_str(), B.c_str()) == 0)
		return true;
	else
		return false;
}

bool operator<=(const Cadena& A, const Cadena &B) noexcept
{
	return (A<B || A==B);
}

bool operator>=(const Cadena& A, const Cadena &B) noexcept
{
	return (A>B || A==B);
}

bool operator!=(const Cadena& A, const Cadena &B) noexcept
{
	return !(A==B);
}

istream& operator >>(istream &is, Cadena& A)
{
	int i = 0;
	char c;
	char *s = new char[32];

	while(isspace(is.peek()) && is.good())
		c = is.get();

	while(!isspace(is.peek()) && i < 32 && is.good()) 
	{
		c = is.get();
		s[i] = c;
		i++;
	}
	s[i] = '\0';

	A = Cadena(s);
	delete []s;
	
	return is;
}

ostream& operator <<(ostream &os, const Cadena& A)
{
	os << A.c_str();
	return os;
}