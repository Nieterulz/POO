#include <ostream>
#include "articulo.hpp"

std::ostream& operator<<(std::ostream& os, const Articulo& A)
{
	os << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_publi().anno() << ". " 
			  << A.precio() << " €\n";
	return os; 
}
