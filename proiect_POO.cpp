#include <iostream>
#include <string>
#pragma warning(disable:4996)
#include "[Proiect][1059][Titeche_Anamaria]clasa.h"

using namespace std;

int main(int argc, char* argv[]) {
	bool tastatura = true; //presupunem ca utilizatorul doreste introducerea comenzilor de la tastatura
	char decizie;
	cout << "Bine ati venit! Doriti sa utilizati un fisier de comenzi sau sa utilizati tastatura? Fisier - F / Tastatura - T" << endl;
	cin >> decizie;
	if (decizie == 'T') {
		bool exit = false; //utilizatorul continua sa introduca comenzi
		char alegere;
		while (!exit) {
			cout << "Introduceti comanda: " << endl;
			cin.ignore(1000, '\n');
			string comanda;
			getline(cin, comanda);
			try {
				cout << "============================" << endl;
				Interpretor interp(comanda, comanda.size());
				cout << interp;
			}
			catch (ExceptieComandaGresita& ex) {
				cout << ex.getMesaj() << endl;
			}
			cout << endl << "Continuati sa introduceti comenzi? D/N" << endl;
			cin >> alegere;
			if (alegere == 'N') exit = true;
			else continue;
		}
	}
	else if (decizie == 'F') {
		AccesFisierComenzi acs(argv[1]);
		//CreareFisier scriere(acs);
		string* comanda = acs.returnareComanda();
		for (int i = 0; i < acs.getNrLiniiFisier(); i++) {
			try {
				cout << "============================" << endl;
				Interpretor interp(comanda[i], comanda[i].size());
				cout << interp;
				cout << endl;
			}
			catch (ExceptieComandaGresita& ex) {
				cout << ex.getMesaj() << endl;
			}
		}
	}

	Users u1("Popescu Andrei", 2), u2("Ana Titeche", 7), u3("Vaduva Alin", 10), u4("John Michaels", 18);
	vector<Users> us(10);
	us.reserve(20);
	cout << "\nDimensiunea vectorului: " << us.size() << " cu extindere pana la " << us.capacity() << " elemente" << endl;
	us[0] = u1;
	us[1] = u2;
	us[3] = u3;
	us.push_back(u4);

	vector<Users>::iterator i;
	for (i = us.begin(); i != us.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;

	list<Users> li = { u1, u2, u3, u4 };
	list<Users>::iterator it;
	Users u5("Silviu", 777);
	li.push_back(u5);
	for (it = li.begin(); it != li.end(); it++) {
		cout << *it << " ";
	}

	/*set<Users> s1 = { u1, u2, u3, u4, u5 };
	set<Users>::iterator its;
	for (its = s1.begin(); its != s1.end(); its++) {
		cout << &its << ", ";
		cout << endl;
	}*/

	map<string, int> mp;
	mp.insert(pair<string, int>("Popescu", 2));
	mp.insert(pair<string, int>("Ana", 7));
	mp.insert(pair<string, int>("Vaduva", 10));
	mp.insert(pair<string, int>("Michaels", 18));
	mp.insert(pair<string, int>("Silviu", 777));

	map<string, int>::iterator itr;
	cout << "\nMapa mp este : \n";
	cout << "\tNUME\tID\n";
	for (itr = mp.begin(); itr != mp.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;

}
