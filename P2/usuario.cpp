#include <unistd.h>
#include "usuario.hpp"

/***************************************CLAVE************************************************/

Clave::Clave(const char* key)
{
	clave_ = new char[13];
	char* salt = new char[2];
	const char *seedchars = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	salt[0] = seedchars[rand()%64];
	salt[1] = seedchars[rand()%64];
	if(strlen(key) < 5)
		throw Incorrecta(CORTA);
	if((clave_ = crypt(key, salt)) == nullptr)
		throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* clara) const
{
	char* key = new char[13];
	key = crypt(clara,clave_.c_str());
	return (clave_ == key);
}

/***************************************USUARIO************************************************/
Usuario::Usuarios Usuario::I;
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& key):
	id_(id), nombre_(nombre), apellidos_(apellidos), dir_(dir), key_(key)
{
	if(!I.insert(id).second)
		throw Id_duplicado(id_);
}

std::ostream& operator <<(std::ostream& os, const Usuario& U)
{
	os << U.id_ << " [" << U.key_.clave() << "] " << U.nombre_ << " " << U.apellidos_ << "\n"
				 << U.dir_ << "\n"
				 << "Tarjetas:\n";
	for(auto pos = U.tarjet_.begin(); pos != U.tarjet_.end(); pos++)
		os << "<" << pos->first << ", " << pos->second->tipo() << ">\n";

	return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& U)
{
	os << "Carrito de compra de " << U.id_ << " [Artículos: " << U.art_.size() << "]\n"
	   << "	Cant. Artículo\n"
	   << "===========================================================\n";
	for(auto pos = U.art_.begin(); pos != U.art_.end(); pos++)
	{
		os << "	" << pos->second << " [" << pos->first->referencia() << "] " << "\"" << pos->first->titulo() << "\", "
		   << pos->first->f_publi().anno() << ". " << pos->first->precio() << " €\n";
	}

	return os;
}

void Usuario::es_titular_de(Tarjeta& T)
{	
	tarjet_[T.numero()] = &T;
}

void Usuario::no_es_titular_de(Tarjeta& T)
{
	T.anula_titular();
	tarjet_.erase(T.numero());
}

void Usuario::compra(Articulo& A, unsigned cantidad)
{
	if(cantidad)
		art_[&A] = cantidad;
	else
	{
		art_.erase(&A);
	}
}

Usuario::~Usuario()
{
	for(Tarjetas::iterator pos = tarjet_.begin(); pos != tarjet_.end(); pos++)
		pos->second->anula_titular();
}