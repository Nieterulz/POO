#include <unistd.h>
#include "usuario.hpp"

/***************************************CLAVE************************************************/

class SNA
{
public:
	SNA() {std::srand(std::time(nullptr));}
};
SNA sna;

Clave::Clave(const char* key)
{
	clave_ = new char[13];
	char* salt = new char[2];
	const char *seedchars = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	salt[0] = seedchars[rand()%64];
	salt[1] = seedchars[rand()%64];
	if(strlen(key) < 5)
		throw Incorrecta(CORTA);
	if(const char* encrypt = crypt(key, salt))
		clave_ = encrypt;
	else
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
		throw Id_duplicado(id);
}

std::ostream& operator << (std::ostream&os,const Usuario& user)
{
  os << user.id_ << "[" << user.key_.clave().c_str() << "]" << user.nombre_
      << user.apellidos_ << std::endl << user.dir_ << std::endl << "Tarjetas:" << std::endl;
  auto iter = user.tarjetas().begin();
   while(iter != user.tarjetas().end()) {
     os << *iter->second << std::endl;
     iter++;
   }
  return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
	os << "Carrito de compra de " << user.id() << " [Artículos: "
	 << user.n_articulos() << "]" << std::endl;
	 os << " Cant. Artículo" << std::endl
	    << std::setw(95) << std::setfill('=') << '\n'  << std::setfill(' ');
	int tmp = user.n_articulos();
	while(tmp > 0)
	{
		for (auto& i : user.compra())
		{
			os << std::setw(4) << i.second << "   "
			<< "[" << (*i.first).referencia() << "] \""
			<< (*i.first).titulo() << "\", " << (*i.first).f_publi().anno()
			<< ". " << std::fixed << std::setprecision(2) << (*i.first).precio()
			<< " €" << std::endl;
			--tmp;
		}
	}
	return os;
}

void Usuario::es_titular_de(Tarjeta& T)
{	if(T.titular() == this)
		tarjet_[T.numero()] = &T;
}

void Usuario::no_es_titular_de(Tarjeta& T)
{
	T.anula_titular();
	tarjet_.erase(T.numero());
}

void Usuario::compra(Articulo& A, unsigned int cantidad)
{
	if(cantidad == 0)
		art_.erase(&A);
	else
		art_[&A] = cantidad;
}

Usuario::~Usuario()
{
	for(Tarjetas::iterator pos = tarjet_.begin(); pos != tarjet_.end(); pos++)
		pos->second->anula_titular();
	I.erase(id_);
}
