#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char const *argv[])
{
	char* s;
	char* tmp;

	cin >> s;
	while((tmp=strchr(s,' ')))
		strcpy(tmp,tmp+1);

	cout << tmp;

	return 0;
}
