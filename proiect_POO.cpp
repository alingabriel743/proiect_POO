#include <iostream>
#include <string>
#pragma warning(disable:4996)
#include "clase.h"

using namespace std;

int main(int argc, char* argv[]) {
	string comanda;
	getline(cin, comanda);
	try {
		Interpretor interp(comanda, comanda.size());
		cout << interp;
	}
	catch (ExceptieComandaGresita & ex) {
		cout << ex.getMesaj() << endl;
	}

}
