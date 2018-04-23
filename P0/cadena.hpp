#ifndef CADENA_HPP_
#define CADENA_HPP_

class Cadena
{
public:
 	explicit Cadena(unsigned tam = 0, char c = ' ');
	Cadena(const char* s) noexcept;
	Cadena(const Cadena& C) noexcept;
	Cadena& operator=(const Cadena& C) noexcept;
	Cadena& operator=(const char* s) noexcept;
	operator const char*() const noexcept;
	Cadena& operator+=(const Cadena& C) noexcept;
	char operator[](unsigned i) const noexcept;
	char& operator[](unsigned i) noexcept;
	char at(unsigned i) const;
	char& at(unsigned i);
	Cadena substr(unsigned i, unsigned t) const;
	unsigned length() const noexcept;
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

inline Cadena::operator const char*() const noexcept
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

#endif