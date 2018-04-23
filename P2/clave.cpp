#include <cstdlib>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include "clave.hpp"

Clave::Clave(const char* key)
{
	clave_ = new char[13];
	char* salt = new char[2];
	const char *seedchars = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	salt[0] = seedchars[rand()%strlen(seedchars)];
	salt[1] = seedchars[rand()%strlen(seedchars)];
	if(strlen(key) < 5)
		throw Incorrecta(CORTA);
	if((clave_ = crypt(key, salt)) == nullptr)
		throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* clara)
{
	char* key = new char[13];
	key = crypt(clara,clave_.c_str());
	return (clave_ == key);
}
