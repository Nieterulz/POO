#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include <set>
#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Autor
{
public:
	Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) noexcept
		:nombre_(nombre), apellidos_(apellidos), direccion_(direccion){}
	const Cadena& nombre() const{return nombre_;}
	const Cadena& apellidos() const{return apellidos_;}
	const Cadena& direccion() const{return direccion_;}
private:
	Cadena nombre_, apellidos_, direccion_;
};

class Articulo
{
public:
	typedef std::set<Autor*> Autores;
	Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio);
	//Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned existencias);
	Cadena referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();
	virtual void impresion_especifica(std::ostream& os) = 0;
	//unsigned stock() const; // Quitar y añadir a la clase ArticuloAlmacenable
	//unsigned& stock();
	class Autores_vacio{};
private:
	const Autores autores_;
	Cadena referencia_, titulo_;
	Fecha publicacion_;
	double precio_;
	//unsigned existencias_;
};

class ArticuloAlmacenable: public Articulo
{
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned existencias);
	unsigned stock() const;
	unsigned& stock();
private:
	unsigned existencias_;
};

//Metodos de la clase Articulo
inline Articulo::Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio):
		autores_(autores),
		referencia_(referencia),
		titulo_(titulo),
		publicacion_(publicacion),
		precio_(precio){}

inline Cadena Articulo::referencia() const
{return referencia_;}

inline Cadena Articulo::titulo() const
{return titulo_;}

inline Fecha Articulo::f_publi() const
{return publicacion_;}

inline double Articulo::precio() const
{return precio_;}

inline double& Articulo::precio()
{return precio_;}

//Metodos de la clase AtriculoAlmacenable
inline ArticuloAlmacenable::ArticuloAlmacenable()

inline unsigned ArticuloAlmacenable::stock() const
{return existencias_;}

inline unsigned& ArticuloAlmacenable::stock()
{return existencias_;}

#endif
