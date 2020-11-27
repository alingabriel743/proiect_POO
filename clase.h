#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
using namespace std;

//enum Comenzi { SELECT = 1, UPDATE = 2, INSERT = 3, DELETE = 4, CREATE = 5, DROP = 6, DISPLAY = 7 };

class ExceptieComandaGresita {
	string mesaj = "";
public:
	ExceptieComandaGresita() {}
	ExceptieComandaGresita(string eroare) {
		this->mesaj = eroare;
	}

	string getMesaj() {
		return this->mesaj;
	}

};

class Select {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char** numeColoane = nullptr;
	char* numeTabela = nullptr;
	char* numeColoanaVerificata = nullptr;
	char* valoare = nullptr; //atoi
public:

	Select(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}
	void Test() {
		for (int i = 0; i < nrParametriIntrare; i++)
			cout << this->parametriIntrare[i] << endl;
	}

	void filtrareElemente() {
		int index = 0;
		while (strcmp(this->parametriIntrare[index + 1], "FROM") != 0) {
			index++;
		}
		this->numeColoane = new char* [index];
		int nrCol = 0;
		for (int j = 1; nrCol < index; nrCol++, j++) {
			this->numeColoane[nrCol] = new char[strlen(this->parametriIntrare[j]) + 1];
			strcpy(this->numeColoane[nrCol], this->parametriIntrare[j]);
		}
		bool existaWhere = false;

		if (index) {
			this->numeTabela = new char[strlen(this->parametriIntrare[index + 2])];
			strcpy(this->numeTabela, this->parametriIntrare[index + 2]);
		}
		index += 3;
		bool existaColoana = false;
		if (index < this->nrParametriIntrare) {
			existaWhere = true;
			for (int i = 0; i < nrCol; i++) {
				if (strcmp(this->numeColoane[i], this->parametriIntrare[index + 1]) == 0) {
					existaColoana = true;
					break;
				}
			}
		}
		if (nrCol == 1) {
			if (existaWhere) {
				cout << "Se va selecta coloana " << this->parametriIntrare[1] << " din tabela " <<
					this->parametriIntrare[3] << " unde valoarea coloanei " << this->parametriIntrare[1] <<
					" este " << this->parametriIntrare[6] << endl;
			}
		}
		else if (nrCol > 1) {
			if (existaWhere) {
				cout << "Se vor selecta coloanele ";
				int k = 1;
				for (k = 1; k <= nrCol; k++) {
					cout << this->parametriIntrare[k] << ", ";
				}
				cout << "din tabela " << this->parametriIntrare[k + 1] << " unde valoarea coloanei " << this->parametriIntrare[k + 3] <<
					" este " << this->parametriIntrare[k + 4] << endl;
			}
		}
		else {
			throw ExceptieComandaGresita();
		}

	}

	friend class Interpretor;
};

class Create {

};

class Update {

};

class Insert {

};

class Delete {

};



class Drop {

};

class Display {

};

class Tabela {
private:
	const int id;
	static int nrTabela;
	//vector de tabele pentru a tine minte existenta lor
public:
	//ceva
};

int Tabela::nrTabela = 0;

class Coloana {
private:
	string nume_coloana;
	string tip;
	string descriere;
	static unsigned int nrColoane;
};
unsigned int Coloana::nrColoane = 0;



class Interpretor {
private:
	char* numeComanda = nullptr;
	int dimensiuneComanda;
	char** parametriComanda = nullptr;
	int nrParametri;
public:
	Interpretor() {
		this->dimensiuneComanda = 0;
		this->nrParametri = 0;
	}
	Interpretor(string comandaIntreaga, int size) : dimensiuneComanda(size) {
		bool temp = false;
		int nrCuvinte = 0;
		for (int j = 0; j < comandaIntreaga.size(); j++) {
			if (comandaIntreaga[j] == ' ' || comandaIntreaga[j] == '(' || comandaIntreaga[j] == '=')
				temp = false;
			else if (!temp) {
				temp = true;
				nrCuvinte++;
			}
		}
		this->nrParametri = nrCuvinte;
		this->parametriComanda = new char* [nrCuvinte];
		char* input = new char[this->dimensiuneComanda + 1];
		int lungimeInput = 0;
		for (lungimeInput; lungimeInput < this->dimensiuneComanda; lungimeInput++) {
			input[lungimeInput] = comandaIntreaga[lungimeInput];
		}
		input[lungimeInput] = '\0';
		char delim[] = " =,()";
		char* numec = strtok(input, delim);

		int i = 0;
		while (numec) {
			this->parametriComanda[i] = new char[strlen(numec) + 1];
			strcpy(this->parametriComanda[i], numec);
			numec = strtok(nullptr, delim);
			if (numec) i++;
		}
		this->numeComanda = this->parametriComanda[0];
	}

	void initializareComenzi() {
		if (strcmp(this->numeComanda, "SELECT") == 0) {
			Select s(this->parametriComanda, this->nrParametri);
			s.Test();
			s.filtrareElemente();
		}
		else if (strcmp(this->numeComanda, "CREATE") == 0) {

		}
	}

	~Interpretor() {
		for (int i = 0; i < this->nrParametri; i++) {
			delete[] this->parametriComanda[i];
		}
		delete[] this->parametriComanda;
	}

	friend class generareObiecte;
	friend class Select;

	// ca sa facem conexiunea folosim si noi un operator
	friend ostream& operator<<(ostream& consola, Interpretor& inte) {
		//consola << inte.nrParametri;
		inte.initializareComenzi();
		//consola << "Buna ziua";
		return consola;
	}

};
