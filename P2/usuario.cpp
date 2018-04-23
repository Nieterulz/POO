#include "usuario.hpp"

std::ostream& operator <<(std::ostream& os, const Usuario& U)
{
	os << U.id_ << " [" << U.key_.clave() << "] " << U.nombre_ << " " U.apellidos_ << "\n"
				 << U.dir_ << "\n"
				 << "Tarjetas:\n";
	for(Tarjetas::iterator pos = U.tarjet_.begin(); pos != U.tarjet_.end(); pos++)
		os << 

	return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuarios& U)
{
	os << "Carrito de compra de " << U.id_ << " [Artículos: " << U.art_.size() << "]\n"
	   << "	Cant. Artículo\n"
	   << "===========================================================\n";
	for(auto pos = U.art_.begin(); pos != U.art_.end(); pos++)
	{
		os << "	" << pos->second << " [" << pos->first.referencia() << "] " << "\"" << pos->first.titulo() << "\", "
		   << pos->first.f_publi().anno() << ". " << pos->first.precio() << " €\n";
	}
}

Usuario::~Usuario()
{
	for(Tarjetas::iterator pos = tarjet_.begin(); pos != tarjer_.end(); pos++)
		pos->second.anula_titular();
}