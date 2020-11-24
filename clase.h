#pragma once
#include <iostream>
#include <string>
using namespace std;



enum Comenzi {SELECT = 1, UPDATE = 2, INSERT = 3, DELETE = 4, CREATE = 5, DROP = 6, DISPLAY = 7};

class Interpretor {
private:
	char* comanda = nullptr;
	int dimensiune;
	char** restComanda = nullptr;
public:
	Interpretor() {
		dimensiune = 0;
	}
	Interpretor(string comandaIntreaga, int size) : dimensiune(size) {
		char* input = new char[this->dimensiune + 1];
		int i;
		for (i = 0; i < this->dimensiune; i++) {
			input[i] = comandaIntreaga[i];
		}
		input[i + 1] = '\0';
		char* numeComanda = strtok(input, " ");

		this->comanda = numeComanda;
		int nrCuvinte = 1;
		for (int j = strlen(this->comanda)+2; j < comandaIntreaga.size(); j++) {
			if (comandaIntreaga[j] == ' ') nrCuvinte++;
		}
		this->restComanda = new char*[nrCuvinte];
		char* restInput = new char[this->dimensiune - (strlen(this->comanda) + 1)];
		int k = 0;
		int cont = 0;
		for (cont,k = strlen(this->comanda) + 1; k < comandaIntreaga.size(); k++, cont++) {
			restInput[cont] = comandaIntreaga[k];
		}
		restInput[k + 1] = '\0';

		for (int i = 0; i < nrCuvinte; i++) {
			this->restComanda[i] = strtok(restInput, " ");
		}

		for (int i = 0; i < nrCuvinte; i++) {
			for (int j = 0; j < strlen(this->restComanda[i]); j++) {
				cout << this->restComanda[i][j];
			}
			cout << endl;
		}

		//cout << nrCuvinte;
		//for (int i = 0; i < strlen(this->comanda); i++) cout << this->comanda[i];

	}
	void tipComanda() {
		if (strcmp(this->comanda, "SELECT")) {
			//Select select;
		}

	}
	friend class Select;
	friend class Update;
	friend class Insert;
	friend class Delete;
	friend class Create;
	friend class Drop;
	friend class Display;

};


class Select {
private:
	char** numeColoane = nullptr;
	char* numeTabela = nullptr;

public:
	friend class Interpreter;
};

class Update {

};

class Insert {

};

class Delete{

};

class Create {

};

class Drop {

};

class Display {

};

class Tabela {
private:
	const int id;
	static int nrTabela;
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