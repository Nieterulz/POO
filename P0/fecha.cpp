#include <ctime>
#include "fecha.hpp"

using namespace std;

Fecha::Invalida::Invalida(const char *s):
	error_(s)
{}

inline bool bisiesto(int a) 
{
	return (a%4==0 && (a%100 != 0 || a%400==0));
}

void Fecha::comprobaciones(int d, int m, int a)
{
	int meses[] = {0, 31, 28+bisiesto(a), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if(a < Fecha::AnnoMinimo || a > Fecha::AnnoMaximo)
		throw Invalida("Año invalido");
	if(m < 0 || m > 12)
		throw Invalida("Mes invalido");
	if(d < 0 || d > meses[m])
		throw Invalida("Dia invalido");
}

const char* Fecha::Invalida::por_que() const
{return error_;}

Fecha::Fecha(int d, int m, int a):
	dia_(d), mes_(m), anno_(a)
{
	if (a==0 || m == 0 || d==0)
	{
		time_t tiempo_calendario = time(nullptr);
		tm* tiempo_descompuesto = localtime(&tiempo_calendario);
		if(d == 0)
			d = tiempo_descompuesto->tm_mday;
		if(m == 0)
			m = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
		if(a == 0)
			a = tiempo_descompuesto->tm_year + 1900; // tm_year: años desde 1900
	}

	comprobaciones(d, m, a);

	dia_ = d;
	mes_ = m;
	anno_ = a;
}

Fecha::Fecha(const char* f)
{
	int d, m, a;

	if(3 == sscanf(f,"%02d/%02d/%04d", &d, &m, &a))
	{
		Fecha aux(d,m,a);
		dia_ = aux.dia_;
		mes_ = aux.mes_;
		anno_ = aux.anno_;
	}
	else
		throw Invalida{"Error de formato(dd/mm/aaaa)"};
}

Fecha& Fecha::operator++()
{
	return (*this +=1);
}

Fecha Fecha::operator++(int)
{
	Fecha t = *this;
	*this += 1;
	return t;
}

Fecha& Fecha::operator--()
{
	return (*this -= 1);
}

Fecha Fecha::operator--(int)
{
	Fecha t = *this;
	*this -= 1;
	return t;
}

Fecha Fecha::operator+(int n) const
{
	Fecha t = *this;

	return (t += n);
}

Fecha Fecha::operator-(int n) const
{
	Fecha t = *this;

	return (t -= n);
}

Fecha& Fecha::operator+=(int n) 
{
	tm tiempo_descompuesto {0};
	tiempo_descompuesto.tm_year = anno_ - 1900;
	tiempo_descompuesto.tm_mon = mes_ - 1;
	tiempo_descompuesto.tm_mday = dia_ + n;
	mktime(&tiempo_descompuesto);

	anno_ = tiempo_descompuesto.tm_year+1900;
	mes_ = tiempo_descompuesto.tm_mon+1;
	dia_ = tiempo_descompuesto.tm_mday;

	if(anno_ > AnnoMaximo)
		throw Invalida{"Error, desbordamiento superior de la fecha."};	
	if(anno_ < AnnoMinimo)
		throw Invalida{"Error, desbordamiento inferior de la fecha."};

	return *this;
}

Fecha& Fecha::operator-=(int n)
{
	return (*this += -n);
}

bool operator==(const Fecha& A, const Fecha& B) noexcept
{
	bool iguales = false;

	if(A.dia() == B.dia() && A.mes() == B.mes() && A.anno() == B.anno())
		iguales = true;

	return iguales;
}

bool operator!=(const Fecha& A, const Fecha& B) noexcept
{ return !(A == B); }

bool operator<(const Fecha& A, const Fecha& B) noexcept
{
	bool menor = false;

	if(A.anno() < B.anno())
		menor = true;
	else
	{
		if(A.anno() == B.anno())
		{
			if(A.mes() < B.mes())
				menor = true;
			else
				if(A.mes() == B.mes())
					if(A.dia() < B.dia())
						menor = true;
		}
	}
	return menor;
}

bool operator>(const Fecha& A, const Fecha& B) noexcept
{return (B < A);}


bool operator<=(const Fecha& A, const Fecha& B) noexcept
{return !(B < A); }

bool operator>=(const Fecha& A, const Fecha& B) noexcept
{return !(A < B);}

Fecha::operator const char*() const noexcept
{
	const char* dias_semana[] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
	const char* meses[] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto",
					"septiembre", "octubre", "noviembre", "diciembre"};

	tm tiempo_descompuesto {0};
	tiempo_descompuesto.tm_year = anno() - 1900;
	tiempo_descompuesto.tm_mon = mes() - 1;
	tiempo_descompuesto.tm_mday = dia();
	mktime(&tiempo_descompuesto);

	static char s[40];
	sprintf(s, "%s %d de %s de %d", dias_semana[tiempo_descompuesto.tm_wday], 
									 tiempo_descompuesto.tm_mday, meses[tiempo_descompuesto.tm_mon], 
									 tiempo_descompuesto.tm_year + 1900);

	return s;
}