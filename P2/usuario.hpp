#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <ostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

class Clave
{
public:
	enum Razon{CORTA, ERROR_CRYPT};
	Clave(const char* s); //Recibe una contraseña sin cifrar
	Cadena clave() const;
	bool verifica(const char* clara);
	class Incorrecta
	{
	public:
		Incorrecta(const Razon r):fallo_(r){};
		Razon razon() const;
	private:
		Razon fallo_;
	};
private:
	Cadena clave_; //contraseña cifrada
};

inline Cadena Clave::clave() const
{return clave_;}

inline Clave::Razon Clave::Incorrecta::razon() const
{return fallo_;}


class Usuario
{
public:
	typedef std::map<Numero, Tarjeta*> Tarjetas;
	typedef std::unordered_map<Articulo*, unsigned int> Articulos;
	Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& dir, const Clave& key);
	Usuario(const Usuario& U) = delete;
	class Id_duplicado
	{
	public:
		Id_duplicado(const Cadena& C):idd_(C){}
		Cadena idd() const{return idd_;}
	private:
		Cadena idd_; 
	};
	const Cadena id() const {return id_;}
	const Cadena nombre() const {return nombre_;}
	const Cadena apellidos() const {return apellidos_;}
	const Cadena direccion() const {return dir_;}
	const Tarjetas& tarjeta() const {return tarjet_;}
	void es_titular_de(const Tarjeta& T);
	void no_es_titular_de(const Tarjeta& T);
	void compra(const Articulo& A, unsigned cantidad = 1);
	const Articulos& compra() const {return art_;}
	unsigned int n_articulos() const{ return art_.size();}
	friend std::ostream& mostrar_carro(std::ostream& os, const Usuario& U);
	friend std::ostream& operator <<(std::ostream& os, const Usuario& U);
	~Usuario();
private:
	static std::unordered_set<Cadena> I;
	Cadena id_, nombre_, apellidos_, dir_;
	Clave key_;
	Tarjetas tarjet_;
	Articulos art_;
};

#endif