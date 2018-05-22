#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "fecha.hpp"
#include "cadena.hpp"

class Articulo
{
public:
	Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned existencias);
	Cadena referencia() const;
	Cadena titulo() const;
	Fecha f_publi() const;
	double precio() const;
	double& precio();
	unsigned stock() const;
	unsigned& stock();

private:
	Cadena referencia_, titulo_;
	Fecha publicacion_;
	double precio_;
	unsigned existencias_;
};

inline Articulo::Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& publicacion, double precio, unsigned existencias):
		referencia_(referencia),
		titulo_(titulo),
		publicacion_(publicacion),
		precio_(precio),
		existencias_(existencias){}

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

inline unsigned Articulo::stock() const
{return existencias_;}

inline unsigned& Articulo::stock()
{return existencias_;}

#endif