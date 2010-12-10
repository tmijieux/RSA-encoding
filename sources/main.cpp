#include <iostream>
#include "rsaCrypter.h"
#include "rsaDecrypter.h"						
using namespace std;

int main(int argc, char *argv[])
{

	int i = 0;
	int message_initial[10] = {0,1,2,3,6};
	int message_crypte[10] = {0};	
	int message_decrypte[10] = {0};
	
	bool test = true;
	int choix = 0;
	do
	{
	cout <<"Voulez vous crypter (1) decrypter (2) ou fermer le programme (0) ?"<< endl;
	cin >> choix;

		switch (choix)
		{
			case 1:
			rsaCrypter(message_initial, message_crypte);
			break;
	 
			case 2:
			rsaDecrypter(message_crypte, message_decrypte);
			break;
			
			case 0:
			test = false;
			break;
			
			default:
			cout << "Mauvais caractere !" << endl;
			break;
		}
	} while ( test );
	
	cout << endl << "Bye !" << endl;
	return 0;
}
