#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
using namespace std;

class Stiva {
	char top;
	string comanda;
public:
	char a[1000] = "";

	Stiva() { top = -1; }
	Stiva(string comanda) {
		this->comanda = comanda;
	}
	void push(char x) {
		if (top >= (1000 - 1)) {
			cout << "Stack Overflow";
		}
		else a[++top] = x;

	}
	void pop() {
		if (top < 0) {
			cout << "Stack Underflow";
		}
		else {
			char x = a[top--];
		}
	}
	void peek() {
		if (top < 0) {
			cout << "Stack is empty";
		}
		else {
			char x = a[top];
		}
	}
	bool isEmpty() {
		return (top < 0);
	}

	friend class VerificareFormatParanteze;
};

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

class VerificareFormatParanteze {
	string comanda;
public:
	VerificareFormatParanteze(string ncomanda) : comanda(ncomanda) {
	}
	bool ArePair(char opening, char closing) {
		if (opening == '(' && closing == ')') return true;
		return false;
	}
	bool isBalanced() {
		Stiva st;
		for (int i = 0; i < this->comanda.size(); i++) {
			if (this->comanda[i] == '(')
				st.push(this->comanda[i]);
			else if (this->comanda[i] == ')')
				if (st.isEmpty() || !ArePair(st.a[st.top], this->comanda[i])) return false;
				else st.pop();
		}
		return st.isEmpty() ? true : false;
	}
	bool existaParanteze() {
		for (int i = 0; i < this->comanda.size(); i++) {
			if (this->comanda[i] == '(' || this->comanda[i] == ')') {
				return true;
			}
		}
		return false;
	}

	bool existaEgal() {
		for (int i = 0; i < this->comanda.size(); i++) {
			if (this->comanda[i] == '=') return true;
		}
		return false;
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


	void filtrareElemente() {
		int index = 0;
		int contor = 1;
		bool esteFrom = true;
		while (strcmp(this->parametriIntrare[contor], "FROM") != 0) {
			index++;
			contor++;
			if (contor >= this->nrParametriIntrare) {
				esteFrom = false;
				break;
			}
		}
		if (!esteFrom) throw ExceptieComandaGresita("Comanda introdusa este gresita");
		this->numeColoane = new char* [index];
		int nrCol = 0;
		for (int j = 1; nrCol < index; nrCol++, j++) {
			this->numeColoane[nrCol] = new char[strlen(this->parametriIntrare[j]) + 1];
			strcpy(this->numeColoane[nrCol], this->parametriIntrare[j]);
		}

		if (index + 3 < this->nrParametriIntrare && (strcmp(this->parametriIntrare[index + 3], "WHERE") != 0))
			throw ExceptieComandaGresita("Comanda introdusa este gresita");
		bool existaWhere = false;

		if (index) {
			this->numeTabela = new char[strlen(this->parametriIntrare[index + 2])];
			strcpy(this->numeTabela, this->parametriIntrare[index + 2]);
		}
		index += 3;
		bool existaColoana = false;
		if (index < this->nrParametriIntrare && strcmp(this->parametriIntrare[index], "WHERE") == 0) {
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
			else {
				cout << "Se va selecta coloana " << this->parametriIntrare[1] << " din tabela " <<
					this->parametriIntrare[3] << endl;
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
			else {
				cout << "Se vor selecta coloanele ";
				int k = 1;
				for (k = 1; k <= nrCol; k++) {
					cout << this->parametriIntrare[k] << ", ";
				}
				cout << "din tabela " << this->parametriIntrare[k + 1] << endl;

			}
		}
		else {
			throw ExceptieComandaGresita();
		}
	}
	friend class Interpretor;
	friend class VerificareFormat;
	friend class Stiva;
};

class Create {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char** numeColoane = nullptr;
	string* tipuri = nullptr;
	int* dimensiuni = nullptr;
	string* valori_implicite = nullptr;

public:
	Create(char** parametriIntrare, int nrParametri) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParametri;
	}
	void setNumeColoane() {

	}

	void verificareSintaxa() {

	}
	void generareTabela() {
		int index = 2;
	}
	friend class Interpretor;
};

class Update {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:

	friend class Interpretor;
};

class Insert {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:

	Insert(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		if (strcmp(this->parametriIntrare[1], "INTO") != 0) {
			throw ExceptieComandaGresita();
		}
		else {
			int contor = 2;
			int index = 0;
			bool esteValues = true;
			while (strcmp(this->parametriIntrare[contor], "VALUES") != 0) {
				index++;
				contor++;
				if (contor >= this->nrParametriIntrare) {
					esteValues = false;
					break;
				}
			}
			if (!esteValues) {
				throw ExceptieComandaGresita();
			}

			if (index != 1) {
				throw ExceptieComandaGresita();
			}

			int NrRestulParametrilor = this->nrParametriIntrare - 4;
			if (NrRestulParametrilor == 0) {
				throw ExceptieComandaGresita();
			}
			else {
				cout << "Tabela: " << parametriIntrare[2] << endl;
				cout << "Coloane:  " << NrRestulParametrilor << endl;
				for (int i = 0; i < NrRestulParametrilor; i++)
					cout << "Coloana " << i + 1 << " value: " << parametriIntrare[i + 4] << endl;
			}

		}
	}

	friend class Interpretor;
	friend class VerificareFormat;
	friend class Stiva;
};

class Delete {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:

	friend class Interpretor;
};


class Drop {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:
	Drop(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		if (nrParametriIntrare != 3) {
			throw ExceptieComandaGresita();
		}
		if (strcmp(this->parametriIntrare[1], "TABLE") != 0) {
			throw ExceptieComandaGresita();
		}
		else {
			cout << "Se va sterge tabela: " << parametriIntrare[2];
		}
	}

	friend class Interpretor;
	friend class VerificareFormat;
	friend class Stiva;
};

class Display {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:
	Display(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		if (nrParametriIntrare != 3) {
			throw ExceptieComandaGresita();
		}
		if (strcmp(this->parametriIntrare[1], "TABLE") != 0) {
			throw ExceptieComandaGresita();
		}
		else {
			cout << "Se va afisa tabela: " << parametriIntrare[2];
		}
	}

	friend class Interpretor;
	friend class VerificareFormat;
	friend class Stiva;
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
	string comandaInitiala = "";
public:
	Interpretor() {
		this->dimensiuneComanda = 0;
		this->nrParametri = 0;
	}
	Interpretor(string comandaIntreaga, int size) : dimensiuneComanda(size) {
		this->comandaInitiala = comandaIntreaga;
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
		strcpy(input, comandaIntreaga.c_str());
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
			VerificareFormatParanteze verif(this->comandaInitiala);
			if (verif.existaParanteze()) {
				if (verif.isBalanced()) {
					Select s(this->parametriComanda, this->nrParametri);
					s.filtrareElemente();
				}
				else cout << "Parantezele nu sunt corespunzatoare";
			}
			else cout << "Nu exista paranteze";

		}
		else if (strcmp(this->numeComanda, "CREATE") == 0) {
			// Create c();
		}
		else if (strcmp(this->numeComanda, "UPDATE") == 0) {
			// Update u();
		}
		else if (strcmp(this->numeComanda, "INSERT") == 0) {
			Insert i(this->parametriComanda, this->nrParametri);
			i.filtrareElemente();
		}
		else if (strcmp(this->numeComanda, "DELETE") == 0) {
			//Delete del();
		}
		else if (strcmp(this->numeComanda, "DROP") == 0) {
			Drop dr(this->parametriComanda, this->nrParametri);
			dr.filtrareElemente();
		}
		else if (strcmp(this->numeComanda, "DISPLAY") == 0) {
			Display dis(this->parametriComanda, this->nrParametri);
			dis.filtrareElemente();
		}
		else {
			throw ExceptieComandaGresita("Missing keyword");
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
