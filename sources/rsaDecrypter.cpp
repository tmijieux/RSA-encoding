#include <iostream>
using namespace std;

void rsaDecrypter(int message_crypte[], int int_message_decrypte[])
{
	int d = 7;
	int i = 0;
	int l = 0;
	int n = 15;
	unsigned long long int puissanceDeCoupe = 0;

	cout << endl << "message decrypte:  " << endl;

	for (i=0; i<5; i++)
	{
		puissanceDeCoupe = message_crypte[i];
		
		for (l=1; l<d; l++)
		{
			puissanceDeCoupe *= message_crypte[i];
		}
      	int_message_decrypte[i] = puissanceDeCoupe % n;
		cout << int_message_decrypte[i];
	}
	cout << endl;
}
