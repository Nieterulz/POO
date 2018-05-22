#include <iostream>
#include <cstring>
#include <map>
#include <iterator>	

using namespace std;

int main(int argc, char const *argv[])
{
	map<string, int> A;
	
	A.insert(make_pair("antonio", 1));
	A.insert(make_pair("juan", 2));
	A.insert(make_pair("kevin", 3));

	for(map<string, int>::iterator pos = A.begin(); pos != A.end(); pos++)
		cout << pos->first << " = " << pos->second << "\n";
	cout << "=========================================\n";

	map<string, int>::iterator it = A.find("antonio");

	A.erase(it);

	for(map<string, int>::iterator pos = A.begin(); pos != A.end(); pos++)
		cout << pos->first << " = " << pos->second << "\n";	

	return 0;
}
