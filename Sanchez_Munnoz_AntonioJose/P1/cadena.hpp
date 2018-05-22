#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iterator>
#include <functional>

class Cadena
{
public:
 	explicit Cadena(unsigned tam = 0, char c = ' ') noexcept;
	Cadena(const char* s) noexcept;
	Cadena(const Cadena& C) noexcept;
	//Cadena(const Cadena& c, unsigned iniPos, unsigned nCar);
	Cadena(Cadena&& C);
	Cadena& operator=(Cadena&& C);
	Cadena& operator=(const Cadena& C) noexcept;
	Cadena& operator=(const char* s) noexcept;
	const char* c_str() const;
	Cadena& operator+=(const Cadena& C) noexcept;
	char operator[](unsigned i) const noexcept;
	char& operator[](unsigned i) noexcept;

	char at(unsigned i) const;
	char& at(unsigned i);
	Cadena substr(unsigned i, unsigned t) const;
	unsigned length() const noexcept;
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	
	iterator begin(){return s_;};
	const_iterator cbegin() const {return s_;};
	const_iterator begin() const{return cbegin();};

	iterator end(){return s_ + tam_;};
	const_iterator cend() const {return s_ + tam_;};
	const_iterator end() const {return cend();};
	
	reverse_iterator rbegin(){return reverse_iterator(end());};
	const_reverse_iterator rbegin() const{return const_reverse_iterator(end());};
	reverse_iterator rend(){return reverse_iterator(begin());};
	const_reverse_iterator rend() const{return const_reverse_iterator(begin());};
	const_reverse_iterator crbegin() const {return const_reverse_iterator(end());};
	const_reverse_iterator crend() const {return const_reverse_iterator(begin());};

	~Cadena() noexcept;
private:
	char* s_;
	unsigned tam_;
};

Cadena operator+(const Cadena& A, const Cadena& B) noexcept;
bool operator<(const Cadena& A, const Cadena& B) noexcept;
bool operator>(const Cadena& A, const Cadena& B) noexcept;
bool operator==(const Cadena& A, const Cadena& B) noexcept;
bool operator<=(const Cadena& A, const Cadena &B) noexcept;
bool operator>=(const Cadena& A, const Cadena &B) noexcept;
bool operator!=(const Cadena& A, const Cadena &B) noexcept;
std::istream& operator >>(std::istream &is, Cadena& A);
std::ostream& operator <<(std::ostream &os, const Cadena& A);

inline const char* Cadena::c_str() const
{return s_;}

inline unsigned Cadena::length() const noexcept
{ return tam_;}
inline Cadena::~Cadena() noexcept
{
	delete[] s_;
}
inline char Cadena::operator[](unsigned i) const noexcept
{return s_[i];}

inline char& Cadena::operator[](unsigned i) noexcept
{return s_[i];}

namespace std {
	template <> struct hash<Cadena> {
		size_t operator()(const Cadena& cad) const
		{ // conversión const char* ->string
			return hash<string>{}(cad.c_str());
		}
	};
}

#endif