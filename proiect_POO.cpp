#include <iostream>
#include <string>
#pragma warning(disable:4996)
#include "clase.h"

using namespace std;

int main(int argc, char* argv[]) {
	string comanda;
	getline(cin, comanda);
    //pentru citirea mai multor comenzi folosim un while(exit)
	Interpretor interp(comanda, comanda.size());
	//interp.initializareComenzi();
	cout << interp;
}