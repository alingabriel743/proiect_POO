#include <iostream>
#include <string>
#pragma warning(disable:4996)
#include "clase.h"

using namespace std;

int main(int argc, char* argv[]) {
	AccesFisier acs(argv[1]);
	//CreareFisier scriere(acs);
	string* comanda = acs.returnareComanda();
	for (int i = 0; i < acs.getNrLiniiFisier(); i++) {
		try {
			Interpretor interp(comanda[i], comanda[i].size());
			cout << interp;
		}
		catch (ExceptieComandaGresita & ex) {
			cout << ex.getMesaj() << endl;
		}
	}
}
