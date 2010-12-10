#include <iostream>
using namespace std;

void rsaCrypter(int int_message_initial[], int message_crypte[])
{
	int i = 0;
	int l = 0;
	int n = 15;
	int d = 7;
	int e = 7;
	unsigned long long int puissanceDeCoupe = 0;
	
	cout << endl << "le message crypte: " << endl;

	for (i=0; i<5; i++)
	{
   		puissanceDeCoupe = int_message_initial[i];

  		for (l=1; l<e; l++)
   		{ 
  			 puissanceDeCoupe *= int_message_initial[i];
    		}
    		message_crypte[i] = puissanceDeCoupe % n;
		cout <<  message_crypte[i] ;
	}
	cout << endl;
}
