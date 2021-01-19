#include <iostream>
#include <string>
#pragma warning(disable:4996)
#include "clase.h"

using namespace std;

int main(int argc, char* argv[]) {
	bool tastatura = true; 
	char decizie;
	cout << "Bine ati venit! Doriti sa utilizati un fisier de comenzi sau sa utilizati tastatura? Fisier - F / Tastatura - T" << endl;
	cin >> decizie;
	if (decizie == 'T') {
		bool exit = false;
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
			catch (ExceptieComandaGresita & ex) {
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
			catch (ExceptieComandaGresita & ex) {
				cout << ex.getMesaj() << endl;
			}
		}
	}

	Users u1("Popescu Andrei", 2), u2("Titeche Ana", 7), u3("Vaduva Alin", 10), u4("John Michaels", 18);
	vector<Users> us(5);
	us.reserve(6);
	cout << endl;
	cout << "-------------VECTOR-------------" << endl;
	cout << "\nDimensiunea vectorului: " << us.size() << " cu extindere pana la " << us.capacity() << " elemente." << endl;
	Users u5("Silviu", 777);
	us[0] = u1;
	us[1] = u2;
	us[2] = u3;
	us[3] = u4;
	us[4] = u5;
	vector<Users>::iterator i;
	for (i = us.begin(); i != us.end(); i++) {
		cout << *i << " ";
	}
	cout << endl;
	cout << "-------------LIST-------------";
	list<Users> li;
	for (int i = 0; i < 5; i++) {
		li.push_back(us[i]);
	}

	list<Users>::iterator it;
	for (it = li.begin(); it != li.end(); it++) {
		cout << endl;
		cout << *it << " ";
	}

	cout << "--------------SET-------------" << endl;
	Users p[5] = { u1, u2, u3, u4 };
	set<Users> s1;
	s1.insert(p[1]); s1.insert(p[2]); s1.insert(p[3]);
	set<Users>::iterator its;
	its = s1.find(p[3]);
	its != s1.end() ?
		cout << "\nGasit: " << its->nume << endl : cout << "\n Negasit! ";

	map<string, int> mp;
	mp.insert(pair<string, int>("Popescu", 2));
	mp.insert(pair<string, int>("Titeche", 7));
	mp.insert(pair<string, int>("Vaduva", 10));
	mp.insert(pair<string, int>("Michaels", 18));
	mp.insert(pair<string, int>("Silviu", 777));
	cout << endl << "-------------MAP-------------" << endl;
	map<string, int>::iterator itr;
	cout << "\nMapa mp este : \n";
	cout << "\tNUME\tID\n";
	for (itr = mp.begin(); itr != mp.end(); ++itr) {
		cout << '\t' << itr->first
			<< '\t' << itr->second << '\n';
	}
	cout << endl;

}
