#ifndef FECHA_HPP_
#define FECHA_HPP_

#include <iostream>

class Fecha
{
public:
	static const int AnnoMinimo = 1902;
	static const int AnnoMaximo = 2037;
	explicit Fecha(int d=0, int m=0, int a=0);
	Fecha(const char *s);
	class Invalida
	{
	public:
		Invalida(const char* s);
		const char* por_que() const;
	private:
		const char* error_;
	};

	int dia() const noexcept;
	int mes() const noexcept;
	int anno() const noexcept;
	Fecha operator+(int n) const;
	Fecha operator-(int n) const;
	Fecha& operator++();
	Fecha operator++(int);
	Fecha& operator--();
	Fecha operator--(int);
	Fecha& operator+=(int n);
	Fecha& operator-=(int n);
	const char* cadena() const noexcept;
private:
	int dia_, mes_, anno_;
	void comprobaciones(int d, int m, int a);
};

bool operator==(const Fecha& A, const Fecha& B) noexcept;
bool operator!=(const Fecha& A, const Fecha& B) noexcept;
bool operator<(const Fecha& A, const Fecha& B) noexcept;
bool operator<=(const Fecha& A, const Fecha& B) noexcept;
bool operator>(const Fecha& A, const Fecha& B) noexcept;
bool operator>=(const Fecha& A, const Fecha& B) noexcept;
std::istream& operator >>(std::istream &is, Fecha& A);
std::ostream& operator <<(std::ostream &os, const Fecha& A);

inline int Fecha::dia() const noexcept { return dia_; }
inline int Fecha::mes() const noexcept { return mes_; }
inline int Fecha::anno() const noexcept{ return anno_; }

#endif
