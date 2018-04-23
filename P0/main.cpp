#include "cadena.cpp"

using namespace std;

int main()
{
	Cadena A;
	Cadena B = "OLA K";
	Cadena C = " ASE?";
	A = B + C;
	size_t longitud = A.length();
	cout << A << " =======> " << "longitud " << longitud << endl;
	
	cout << A.substr(0, 5) << endl;

	A[0] = 'E';

}