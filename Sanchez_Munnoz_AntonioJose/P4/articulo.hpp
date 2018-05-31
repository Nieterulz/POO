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
	const Cadena& nombre() const noexcept{return nombre_;}
	const Cadena& apellidos() const noexcept{return apellidos_;}
	const Cadena& direccion() const noexcept{return direccion_;}
private:
	const Cadena nombre_, apellidos_, direccion_;
};

class Articulo
{
public:
	typedef std::set<Autor*> Autores;
	Articulo(const Autores& autores, const Cadena& referencia, const Cadena& titulo,
		       const Fecha& publicacion, double precio):
		autores_(autores),
		referencia_(referencia),
		titulo_(titulo),
		publicacion_(publicacion),
		precio_(precio)
	{}
	const Autores& autores() const{return autores_;}
	Cadena referencia() const{return referencia_;}
	Cadena titulo() const{return titulo_;}
	Fecha f_publi() const{return publicacion_;}
	double precio() const{return precio_;}
	double& precio(){return precio_;}
	virtual void impresion_especifica(std::ostream& os) const = 0;
	class Autores_vacios{};
	virtual ~Articulo(){}
private:
	const Autores autores_;
	Cadena referencia_, titulo_;
	Fecha publicacion_;
	double precio_;
};

std::ostream& operator<<(std::ostream& os, const Articulo& A);

class ArticuloAlmacenable: public Articulo
{
public:
	ArticuloAlmacenable(const Autores& autores, const Cadena& referencia,
		const Cadena& titulo, const Fecha& publicacion, double precio, unsigned existencias = 0)
		:Articulo(autores, referencia, titulo, publicacion, precio), stock_(existencias)
	{}
	unsigned stock() const{return stock_;}
	unsigned& stock(){return stock_;}
protected:
	unsigned stock_;
};

class Libro: public ArticuloAlmacenable
{
public:
	Libro(const Autores& autores, const Cadena& referencia,
		const Cadena& titulo, const Fecha& publicacion, double precio,
		 unsigned n_pag, unsigned existencias = 0):
		 ArticuloAlmacenable(autores, referencia, titulo, publicacion,
			  								 precio, existencias), n_pag_(n_pag)
		 {}
	unsigned n_pag() const{return n_pag_;}
	virtual void impresion_especifica(std::ostream& os) const;
private:
	const unsigned n_pag_;
};

class Cederron: public ArticuloAlmacenable
{
public:
	Cederron(const Autores& autores, const Cadena& referencia,
		const Cadena& titulo, const Fecha& publicacion, double precio,
		 double tam, unsigned existencias = 0):
		 ArticuloAlmacenable(autores, referencia, titulo, publicacion,
			  								 precio, existencias), tam_(tam)
		 {}
	double tam() const{return tam_;}
	virtual void impresion_especifica(std::ostream& os) const;
private:
	const double tam_;
};

class LibroDigital: public Articulo
{
public:
	LibroDigital(const Autores& autores, const Cadena& referencia, const Cadena& titulo,
		       const Fecha& publicacion, double precio, const Fecha& f_expir):
		Articulo(autores, referencia, titulo, publicacion, precio), f_expir_(f_expir)
	{}
	const Fecha& f_expir() const{return f_expir_;}
	virtual void impresion_especifica(std::ostream& os) const;
private:
	const Fecha f_expir_;
};

#endif
