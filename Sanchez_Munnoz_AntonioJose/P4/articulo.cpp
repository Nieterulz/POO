#include <ostream>
#include <iomanip>
#include "articulo.hpp"

std::ostream& operator<<(std::ostream& os, const Articulo& A)
{
	auto i = A.autores().begin();
	os << "[" << A.referencia() << "] \"" << A.titulo() << "\", de " << (*i)->apellidos();
	for(++i; i != A.autores().end(); i++)
	{
		os << ", " << (*i)->apellidos();
	}
	os << ". " << A.f_publi().anno() << ". " << std::fixed << std::setprecision(2) << A.precio() << " €\n\t";
	A.impresion_especifica(os);
	return os;
}

void Libro::impresion_especifica(std::ostream &os) const
{
	os << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::ostream &os) const
{
	os << (unsigned)tam_ << " MB, " << stock_ << " unidades.";
}

void LibroDigital::impresion_especifica(std::ostream &os) const
{
	os << "A la venta hasta el " << f_expir_ << ".";
}
