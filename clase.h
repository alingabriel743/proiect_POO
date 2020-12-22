#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Stiva {
	char top;
	string comanda;
	char a[1000] = "";
public:
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
	bool isEmpty() {
		return (top < 0);
	}
	friend class VerificareFormatParanteze;
};

class AccesFisierComenzi {
private:
	string numeFisier;
	string* linii;
	int nrLiniiFisier = 0;
public:
	AccesFisierComenzi(char* numeFisier) {
		string numeF(numeFisier);
		this->numeFisier = numeF;
		this->linii = nullptr;
	}

	string* returnareComanda() {
		ifstream fisier(this->numeFisier, ios::in);
		int count = 0;
		if (fisier.is_open()) {
			string comanda;
			while (!fisier.eof()) {
				getline(fisier, comanda);
				count++;
			}
			this->linii = new string[count];
			fisier.clear();
			fisier.seekg(0);
			string buffer;
			for (int i = 0; i < count; i++) {
				getline(fisier, buffer);
				this->linii[i] = buffer;
			}
			this->nrLiniiFisier = count;
			return this->linii;
			fisier.close();
		}
		else { 
			cout << "Nu se deschide"; 
			return nullptr;
		}
		
	}

	string getNumeFisier() {
		return this->numeFisier;
	}

	int getNrLiniiFisier() {
		return this->nrLiniiFisier;
	}

	void citireDinFisier() {
		
	}
};

class VerificareNumeTabel {
	string numeFisier = "";
public:
	VerificareNumeTabel(string nume) {
		this->numeFisier = nume;
	}

	bool existaFisier() {
		ifstream fisier("numeTabeleFisiere.txt", ios::in);
		if (fisier.is_open()) {
			string buffer;
			while (fisier >> buffer) {
				if (buffer == this->numeFisier) {
					return false;
				}
			}
			fisier.close();
			return true;
		}
		else cout << "Fisierul nu s-a deschis";
	}
};

class DisplayFisier {
private:
	char** numeColoane = nullptr;
	char** tipuri = nullptr;
	char** dimensiuni = nullptr;
	char** valori_implicite = nullptr;
	char* numeTabel = nullptr;
	int nrPerechiParametri = 0;  //trb sa le numar

public:
	void showData()
	{
		cout << "Tabela : " << this->numeTabel << endl;
		for (int i = 0; i < this->nrPerechiParametri; i++) {
			cout << "Nume coloana : " << this->numeColoane[i] << endl;
			cout << "Tip : " << this->tipuri[i] << endl;
			cout << "Valori implicite : " << this->valori_implicite << endl;
		}

	}
	void display()
	{
		ifstream fisier;
		fisier.open(this->numeTabel, ios::binary);
		VerificareNumeTabel verif(this->numeTabel);
		if (!verif.existaFisier()) {
			DisplayFisier obj;

			string buffer;
			while (!fisier.eof()) {
				obj.showData();
			}
		}
		else {
			cout << "Fisieul nu exista!";
		
		}
	
	}

};

class CreareFisier {
	char** numeColoane = nullptr;
	char** tipuri = nullptr;
	char** dimensiuni = nullptr;
	char** valori_implicite = nullptr;
	char* numeTabel = nullptr;
	int nrPerechiParametri = 0;

public:
	CreareFisier(char* numeTabel, char** numeC, char** tip, char** dim, char** val_impl, int nrPerechiParametri) {
		this->numeTabel = numeTabel;
		this->numeColoane = numeC;
		this->tipuri = tip;
		this->dimensiuni = dim;
		this->valori_implicite = val_impl;
		this->nrPerechiParametri = nrPerechiParametri;
	}

	void generareFisiere() {

		string numeFisierDescriere(this->numeTabel);
		numeFisierDescriere += "_descriere";
		ofstream tabel(numeFisierDescriere, ios::out | ios::binary | ios::trunc);
		if (tabel.is_open()) {
			for (int i = 0; i < this->nrPerechiParametri; i++) {
				//scriem dimensiunea sirului de caractere pentru a citi ulterior mai usor din fisier
				//transformam buffer din string in c_string
				string buffer(this->numeColoane[i]);
				int dim = buffer.size() + 1;
				tabel.write((char*)&dim, sizeof(int));
				tabel.write(buffer.c_str(), dim * sizeof(char));

				buffer = this->tipuri[i];
				dim = buffer.size() + 1;
				tabel.write((char*)&dim, sizeof(int));
				tabel.write(buffer.c_str(), dim * sizeof(char));

				buffer = this->dimensiuni[i];
				dim = buffer.size() + 1;
				tabel.write(buffer.c_str(), dim * sizeof(char));
				if (strcmp(this->tipuri[i], "integer") == 0) {
					int transf = atoi(this->valori_implicite[i]);
					tabel.write((char*)&transf, sizeof(int));
				}
				else if (!strcmp(this->tipuri[i], "text")) {
					buffer = this->valori_implicite[i];
					dim = buffer.size() + 1;
					tabel.write(buffer.c_str(), dim * sizeof(char));
				}
				else if (!strcmp(this->tipuri[i], "float")) {
					int transf = atof(this->valori_implicite[i]);
					tabel.write((char*)&transf, sizeof(float));
				}
			}
			tabel.close();
		}
		else {
			cout << "Nu s-a deschis";
		}

		string numeFisierDate(this->numeTabel);
		numeFisierDate += "_date";
		ofstream tabelDate(numeFisierDate, ios::out | ios::binary | ios::trunc);
		tabelDate.close();
	}

	void generareFisierTabele() {
		fstream fisiere("numeTabeleFisiere.txt", ios::out | ios::in | ios::app);
		bool exista = false; //presupunem ca nu exista numele fisierului in tabel
		if (fisiere) {
			fisiere.seekg(0, ios::end);
			int dim = fisiere.tellg();
			if (!dim) {
				fisiere << this->numeTabel;
				exista = true;
			}
			else {
				fisiere.clear();
				fisiere.seekg(0);
				
				string buffer;
				string conversie(this->numeTabel);
				int nrParametriExistenti = 0;
				while (fisiere >> buffer) {
					nrParametriExistenti++;
				}
				string* parametri = new string[nrParametriExistenti];
				fisiere.clear();
				fisiere.seekg(0);
				int i = 0;
				while(fisiere >> buffer){
					parametri[i] = buffer;
					i++;
				}
				for (int i = 0; i < nrParametriExistenti; i++) {
					if (conversie == parametri[i]) {
						cout << "Numele tabelului exista deja" << endl;
						exista = true;
						break;
					}
				}
			}
			fisiere.close();
		}
		else cout << "Sa te ia dracul";

		ofstream fisier("numeTabeleFisiere.txt", ios::out | ios::app);
		if (fisier && !exista) {
			fisier << endl << this->numeTabel;
			fisier.close();
		}
		
	}
};

class ScriereFisier {
	char** parametriDeInserat = nullptr;
	int nrParametri = 0;
	string numeTabela = "";
	
public:
	ScriereFisier(char** parametri, int numar, string nume) {
		this->parametriDeInserat = parametri;
		this->nrParametri = numar;
		this->numeTabela = nume;
	}

	//void verificareNumarParametri
};

class DropFisier {
private:
	char* numeTabel = nullptr;
public:
	void DropFis(char* numeTab)
	{
		ifstream fisier;
		VerificareNumeTabel verif(this->numeTabel);
		if (!verif.existaFisier()) {
			remove(this->numeTabel);
		}
		else {
			cout << "Fisierul nu exista!";
		}
	}
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
	int nrPerechiParanteze = 0;
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
				else {
					st.pop();
					this->nrPerechiParanteze++;
				}
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

	int getPerechiParanteze() {
		return this->nrPerechiParanteze;
	}
};

class Select {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char** numeColoane = nullptr;
	char* numeTabela = nullptr;
	int nrColoane = 0;
	string comandaInitiala = "";

public:
	Select(char** parametriIntrare, int nrParam, string comandaInitiala) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
		this->comandaInitiala = comandaInitiala;
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
		if (!esteFrom) throw ExceptieComandaGresita("Lipseste FROM");
		this->numeColoane = new char* [index];
		int nrCol = 0;
		for (int j = 1; nrCol < index; nrCol++, j++) {
			this->numeColoane[nrCol] = new char[strlen(this->parametriIntrare[j]) + 1];
			strcpy(this->numeColoane[nrCol], this->parametriIntrare[j]);
		}
		this->nrColoane = nrCol;
		if (this->nrColoane) {
			if (index + 3 < this->nrParametriIntrare && (strcmp(this->parametriIntrare[index + 3], "WHERE") != 0))
				throw ExceptieComandaGresita("Lipseste WHERE");


			bool corect = true;
			int nrVirgule = 0;
			for (int i = 0; i < this->comandaInitiala.size(); i++) {
				if (this->comandaInitiala[i] == ',') nrVirgule++;
			}

			if (nrColoane == 1 && nrVirgule == 0) corect = true;
			else if (nrVirgule == this->nrColoane - 1 && nrColoane > 1) corect = true;
			else corect = false;

			bool esteEgal = false;
			int nrEgal = 0;
			for (int i = 0; i < this->comandaInitiala.size(); i++) {
				if (this->comandaInitiala[i] == '=') nrEgal++;
			}
			if (nrEgal == 1) esteEgal = true;

			bool existaWhere = false;
			if (index) {
				this->numeTabela = new char[strlen(this->parametriIntrare[index + 2])];
				strcpy(this->numeTabela, this->parametriIntrare[index + 2]);
			}
			index += 3;

			bool existaColoana = false;
			if (index < this->nrParametriIntrare && strcmp(this->parametriIntrare[index], "WHERE") == 0 && strcmp(this->numeColoane[0], "ALL") != 0) {
				existaWhere = true;
				for (int i = 0; i < nrCol; i++) {
					if (strcmp(this->numeColoane[i], this->parametriIntrare[index + 1]) == 0) {
						existaColoana = true;
						break;
					}
				}
			}

			int nrParametriWhere = 0;
			bool nrCorectParametriWhere = true;
			for (int i = index + 1; i < this->nrParametriIntrare; i++) nrParametriWhere++;
			if (nrParametriWhere != 2) nrCorectParametriWhere = false;

			if (strcmp(this->numeColoane[0], "ALL") == 0 && this->nrColoane == 1) {
				if (esteEgal && nrCorectParametriWhere) {
					cout << "Se vor afisa toate coloanele din tabela " << this->numeTabela << " unde " << this->parametriIntrare[5] << " are valoarea " << this->parametriIntrare[6];
				}
				else if (!esteEgal && nrParametriWhere == 0) cout << "Se vor afisa toate coloanele din tabela " << this->numeTabela;
				else cout << "Eroare";
			}

			else if (nrCol == 1 && corect) {
				if (existaWhere && esteEgal && nrCorectParametriWhere) {
					cout << "Se va selecta coloana " << this->parametriIntrare[1] << " din tabela " <<
						this->parametriIntrare[3] << " unde valoarea coloanei " << this->parametriIntrare[1] <<
						" este " << this->parametriIntrare[6] << endl;
				}
				else {
					cout << "Se va selecta coloana " << this->parametriIntrare[1] << " din tabela " <<
						this->parametriIntrare[3] << endl;
				}

			}
			else if (nrCol > 1 && corect) {
				if (existaWhere && esteEgal && nrCorectParametriWhere) {
					cout << "Se vor selecta coloanele ";
					int k = 1;
					for (k = 1; k <= nrCol; k++) {
						cout << this->parametriIntrare[k] << ", ";
					}
					cout << "din tabela " << this->parametriIntrare[k + 1] << " unde valoarea coloanei " << this->parametriIntrare[k + 3] <<
						" este " << this->parametriIntrare[k + 4] << endl;
				}
				else if (corect) {
					cout << "Se vor selecta coloanele ";
					int k = 1;
					for (k = 1; k <= nrCol; k++) {
						cout << this->parametriIntrare[k] << ", ";
					}
					cout << "din tabela " << this->parametriIntrare[k + 1] << endl;
				}
			}
			else {
				cout << "Eroare";
			}
		}
	}

	bool existaColoane() {
		if (this->nrColoane > 0) return true;
		else return false;
	}

	~Select() {
		for (int i = 0; i < this->nrColoane; i++) {
			if (this->numeColoane[i]) delete[] this->numeColoane[i];
		}
		delete[] this->numeColoane;

	}

	friend class Interpretor;

	char* operator[](int index) {
		if (index > 0 && index < this->nrColoane)
			return this->numeColoane[index];
	}

	friend ostream& operator<<(ostream& os, Select& s) {
		s.filtrareElemente();
		return os;
	}
};

class Create {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char** numeColoane = nullptr;
	char** tipuri = nullptr;
	char** dimensiuni = nullptr;
	char** valori_implicite = nullptr;
	int nrPerechiParametri = 0;
	int nrPerechiParanteze = 0;
	string comandaInitiala = "";

public:

	Create(char** parametriIntrare, int nrParam, string comandaInitiala, int nrPerechiPar) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
		this->comandaInitiala = comandaInitiala;
		this->nrPerechiParanteze = nrPerechiPar;
	}

	void filtrareElemente() {
		if (strcmp(this->parametriIntrare[1], "TABLE") != 0) {
			throw ExceptieComandaGresita("Eroare");
		}
		else {
			if (strcmp(this->parametriIntrare[3], "IF") == 0 && strcmp(this->parametriIntrare[4], "NOT") == 0 && strcmp(this->parametriIntrare[5], "EXISTS") == 0) {
				if (strcmp(this->parametriIntrare[7], "integer") != 0 && strcmp(this->parametriIntrare[7], "float") != 0 && strcmp(this->parametriIntrare[7], "text") != 0) {
					throw ExceptieComandaGresita("Eroare");
				}
				int nrCaracteristi = this->nrParametriIntrare - 6;
				if (nrCaracteristi % 4 != 0) {
					throw ExceptieComandaGresita("Eroare");
				}

				int ind = 6;
				int pereche = 0;
				for (ind = 6; ind < this->nrParametriIntrare; ind++) {
					pereche++;
					if (pereche == 4) {
						pereche = 0;
						this->nrPerechiParametri++;
					}

				}

				this->valori_implicite = new char* [this->nrPerechiParametri];
				this->dimensiuni = new char* [this->nrPerechiParametri];
				this->tipuri = new char* [this->nrPerechiParametri];
				this->numeColoane = new char* [this->nrPerechiParametri];
				nrPerechiParametri = 0;
				for (ind = 6; ind < this->nrParametriIntrare; ind++) {
					pereche++;
					if (pereche == 4) {
						pereche = 0;
						this->valori_implicite[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->valori_implicite[this->nrPerechiParametri], this->parametriIntrare[ind]);
						nrPerechiParametri++;

					}
					else if (pereche == 3) {
						this->dimensiuni[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->dimensiuni[this->nrPerechiParametri], this->parametriIntrare[ind]);

					}
					else if (pereche == 2) {
						this->tipuri[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->tipuri[this->nrPerechiParametri], this->parametriIntrare[ind]);

					}
					else if (pereche == 1) {
						this->numeColoane[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->numeColoane[this->nrPerechiParametri], this->parametriIntrare[ind]);

					}
					
				}
				if (this->nrPerechiParametri != this->nrPerechiParanteze - 1) cout << "Eroare";
				else if (this->nrPerechiParametri == this->nrPerechiParanteze - 1 || (this->nrPerechiParametri == 1 && this->nrPerechiParametri == 1)) {
					cout << "Tabel: " << this->parametriIntrare[2] << endl;
					pereche = 0;
					this->nrPerechiParametri = 0;
					for (ind = 6; ind < this->nrParametriIntrare; ind++) {
						pereche++;
						if (pereche == 4) {
							pereche = 0;
							cout << "Valoare implicita: " << this->valori_implicite[this->nrPerechiParametri] << endl;
							this->nrPerechiParametri++;
						}
						else if (pereche == 3) {
							cout << "Dimensiune " << this->dimensiuni[this->nrPerechiParametri] << endl;
						}
						else if (pereche == 2) {
							cout << "Tip: " << this->tipuri[this->nrPerechiParametri] << endl;
						}
						else if (pereche == 1) {
							cout << "Nume coloana: " << this->numeColoane[this->nrPerechiParametri] << endl;
						}

					}
					CreareFisier crt(this->parametriIntrare[2], this->numeColoane, this->tipuri, this->dimensiuni, this->valori_implicite, this->nrPerechiParametri);
					crt.generareFisiere();
					crt.generareFisierTabele();

				}
				else cout << "Eroare";
			}
			else {
				if (strcmp(this->parametriIntrare[4], "integer") != 0 && strcmp(this->parametriIntrare[4], "float") != 0 && strcmp(this->parametriIntrare[4], "text") != 0) {
					throw ExceptieComandaGresita("Eroare");
				}
				int nrCaracteristi = this->nrParametriIntrare - 3;
				if (nrCaracteristi % 4 != 0) {
					throw ExceptieComandaGresita("Eroare");
				}

				int ind = 3;
				int pereche = 0;
				for (ind = 3; ind < this->nrParametriIntrare; ind++) {
					pereche++;
					if (pereche == 4) {
						pereche = 0;
						this->nrPerechiParametri++;
					}

				}

				this->valori_implicite = new char* [this->nrPerechiParametri];
				this->dimensiuni = new char* [this->nrPerechiParametri];
				this->tipuri = new char* [this->nrPerechiParametri];
				this->numeColoane = new char* [this->nrPerechiParametri];
				nrPerechiParametri = 0;
				for (ind = 3; ind < this->nrParametriIntrare; ind++) {
					pereche++;
					if (pereche == 4) {
						pereche = 0;
						this->valori_implicite[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->valori_implicite[this->nrPerechiParametri], this->parametriIntrare[ind]);
						nrPerechiParametri++;

					}
					else if (pereche == 3) {
						this->dimensiuni[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->dimensiuni[this->nrPerechiParametri], this->parametriIntrare[ind]);

					}
					else if (pereche == 2) {
						this->tipuri[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->tipuri[this->nrPerechiParametri], this->parametriIntrare[ind]);

					}
					else if (pereche == 1) {
						this->numeColoane[this->nrPerechiParametri] = new char[strlen(this->parametriIntrare[ind])];
						strcpy(this->numeColoane[this->nrPerechiParametri], this->parametriIntrare[ind]);

					}

				}
				if (this->nrPerechiParametri != this->nrPerechiParanteze - 1) cout << "Eroare";
				else if (this->nrPerechiParametri == this->nrPerechiParanteze - 1 || (this->nrPerechiParametri == 1 && this->nrPerechiParametri == 1)) {
					cout << "Tabel: " << this->parametriIntrare[2] << endl;
					pereche = 0;
					this->nrPerechiParametri = 0;
					for (ind = 3; ind < this->nrParametriIntrare; ind++) {
						pereche++;
						if (pereche == 4) {
							pereche = 0;
							cout << "Valoare implicita: " << this->valori_implicite[this->nrPerechiParametri] << endl;
							this->nrPerechiParametri++;
						}
						else if (pereche == 3) {
							cout << "Dimensiune " << this->dimensiuni[this->nrPerechiParametri] << endl;
						}
						else if (pereche == 2) {
							cout << "Tip: " << this->tipuri[this->nrPerechiParametri] << endl;
						}
						else if (pereche == 1) {
							cout << "Nume coloana: " << this->numeColoane[this->nrPerechiParametri] << endl;
						}
					}
					CreareFisier crt(this->parametriIntrare[2], this->numeColoane, this->tipuri, this->dimensiuni, this->valori_implicite, this->nrPerechiParametri);
					crt.generareFisiere();
					crt.generareFisierTabele();
				}
				else cout << "Eroare";
			}
		}

	}



	bool existaPerechiParametri() {
		if (this->nrPerechiParametri > 0) return true;
		else return false;
	}

	bool parantezeCorecte() {
		if (this->nrPerechiParametri == 1 && this->nrPerechiParanteze == 1) return true;
		else if (this->nrPerechiParametri == this->nrPerechiParanteze - 1) return true;
		else return false;
	}

	friend class Interpretor;
	friend ostream& operator<<(ostream& os, Create& c) {
		c.filtrareElemente();
		return os;
	}
};

class Update {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:

	Update(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		int contor = 1;
		int index = 0;
		bool esteSet = true;
		while (strcmp(this->parametriIntrare[contor], "SET") != 0) {
			index++;
			contor++;
			if (contor >= this->nrParametriIntrare) {
				esteSet = false;
				break;
			}
		}
		if (!esteSet) {
			throw ExceptieComandaGresita("Eroare");
		}
		if (index != 1) {
			throw ExceptieComandaGresita("Eroare");
		}

		bool esteWhere = true;
		contor = 3;
		index = 0;
		while (strcmp(this->parametriIntrare[contor], "WHERE") != 0) {
			index++;
			contor++;
			if (contor >= this->nrParametriIntrare) {
				esteWhere = false;
				break;
			}
		}
		if (!esteWhere) {
			throw ExceptieComandaGresita("Eroare");
		}

		if (index != 2) {
			throw ExceptieComandaGresita("Eroare");
		}

		int NrRestulParametrilor = this->nrParametriIntrare - 6;
		if (NrRestulParametrilor != 2) {
			throw ExceptieComandaGresita("Eroare");
		}
		else {
			cout << "Tabela: " << parametriIntrare[1] << endl;
			cout << "Coloana: " << parametriIntrare[3] << endl;
			cout << "Valoare: " << parametriIntrare[4] << endl;
			cout << "Filtru: " << parametriIntrare[6] << endl;
			cout << "Vloare filtru: " << parametriIntrare[7] << endl;
		}

	}

	friend class Interpretor;

	friend ostream& operator<<(ostream& consola, Update& up) {

		consola << "Tabela: " << up.parametriIntrare[1] << endl;
		consola << "Coloana: " << up.parametriIntrare[3] << endl;
		consola << "Valoare: " << up.parametriIntrare[4] << endl;
		consola << "Filtru: " << up.parametriIntrare[6] << endl;
		consola << "Vloare filtru: " << up.parametriIntrare[7] << endl;
		return consola;
	}

	friend bool operator>(Update c1, Update c2) {
		if ((int)c1.parametriIntrare[7] > (int)c2.parametriIntrare[7])
			return true;
		else return false;
	}
};

class Insert {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	int nrParametriInserare;
	char* numeTabela = nullptr;
	string comandaInitiala = "";
	char** parametriInsert = nullptr;
public:

	Insert(char** parametriIntrare, int nrParam, string comandaInitiala) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
		this->comandaInitiala = comandaInitiala;
	}

	void setNumeTabela() {
		this->numeTabela = this->parametriIntrare[2];
	}

	void filtrareElemente() {

		if (strcmp(this->parametriIntrare[1], "INTO") != 0) {
			throw ExceptieComandaGresita("Eroare");
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
				throw ExceptieComandaGresita("Eroare");
			}

			if (index != 1) {
				throw ExceptieComandaGresita("Eroare");
			}

			int nrParametriInsert = this->nrParametriIntrare - 4;
			if (nrParametriInsert == 0) throw ExceptieComandaGresita("Eroare");
			this->nrParametriInserare = nrParametriInsert;
			bool corect = true;
			int nrVirgule = 0;
			for (int i = 0; i < this->comandaInitiala.size(); i++) {
				if (this->comandaInitiala[i] == ',') nrVirgule++;
			}
			if (nrParametriInsert == 1 && nrVirgule == 0) corect = true;
			else if (nrVirgule == nrParametriInsert - 1 && nrParametriInsert > 1) corect = true;
			else corect = false;

			this->parametriInsert = new char* [nrParametriInsert];
			if (nrParametriInsert == 0 || !corect) {
				throw ExceptieComandaGresita("Eroare");
			}
			else {
				cout << "Tabela: " << parametriIntrare[2] << endl;
				cout << "Coloane:  " << nrParametriInsert << endl;
				for (int i = 0; i < nrParametriInsert; i++) {
					cout << "Coloana " << i + 1 << " value: " << parametriIntrare[i + 4] << endl;
					this->parametriInsert[i] = this->parametriIntrare[i+4];
				}
			}

		}
	}

	bool existaParametri() {
		if (this->nrParametriIntrare > 0) return true;
		else return false;
	}

	~Insert() {
		if (this->numeTabela) delete[] this->numeTabela;
	}

	friend class Interpretor;



};

class Delete {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;

public:

	Delete(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		if (strcmp(this->parametriIntrare[1], "FROM") != 0) {
			throw ExceptieComandaGresita();
		}
		else {
			int contor = 2;
			int index = 0;
			bool esteWhere = true;
			while (strcmp(this->parametriIntrare[contor], "WHERE") != 0) {
				index++;
				contor++;
				if (contor >= this->nrParametriIntrare) {
					esteWhere = false;
					break;
				}
			}
			if (!esteWhere) {
				throw ExceptieComandaGresita("Eroare");
			}
			if (index != 1) {
				throw ExceptieComandaGresita("Eroare");
			}

			int NrRestulParametrilor = this->nrParametriIntrare - 4;
			if (NrRestulParametrilor != 2) {
				throw ExceptieComandaGresita("Eroare");
			}
			else {
				cout << "Tabela: " << parametriIntrare[2] << endl;
				cout << "Coloana filtru: " << parametriIntrare[4] << " cu valoarea " << parametriIntrare[5];
			}

		}
	}

	friend class Interpretor;

	friend ostream& operator<<(ostream& consola, Delete& del) {

		consola << "Tabela: " << del.parametriIntrare[2] << endl;
		consola << "Coloana filtru: " << del.parametriIntrare[4] << " cu valoarea " << del.parametriIntrare[5];

		return consola;
	}

	friend bool operator<(Delete c1, Delete c2) {
		if (strcmp(c1.parametriIntrare[5], c2.parametriIntrare[5]) != 0)
			return true;
		else return false;
	}
};

class Drop {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char* numeTabela = nullptr;

public:
	Drop(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		if (nrParametriIntrare != 3) {
			throw ExceptieComandaGresita("Eroare");
		}
		if (strcmp(this->parametriIntrare[1], "TABLE") != 0) {
			throw ExceptieComandaGresita("Eroare");
		}
		else {
			cout << "Se va sterge tabela: " << parametriIntrare[2];
		}
	}

	void setNumeTabela() {
		if (nrParametriIntrare == 3 && (strcmp(this->parametriIntrare[1], "TABLE") == 0)) {
			this->numeTabela = new char[strlen(this->parametriIntrare[2]) + 1];
			strcpy(this->numeTabela, this->parametriIntrare[2]);
		}
	}
	~Drop() {
		if (this->numeTabela) delete[] this->numeTabela;
	}
	friend class Interpretor;

	friend ostream& operator<<(ostream& consola, Drop& dr) {

		consola << "Se va sterge tabela: " << dr.parametriIntrare[2];

		return consola;
	}

	friend bool operator<(Drop c1, Drop c2) {
		if (strcmp(c1.parametriIntrare[5], c2.parametriIntrare[5]) != 0)
			return true;
		else return false;
	}

	char* operator[](int index) {
		return this->parametriIntrare[index];
	}
};

class Display {
private:
	char** parametriIntrare = nullptr;
	char* numeTabela = nullptr;
	int nrParametriIntrare;

public:
	Display(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void filtrareElemente() {

		if (nrParametriIntrare != 3) {
			throw ExceptieComandaGresita("Eroare");
		}
		if (strcmp(this->parametriIntrare[1], "TABLE") != 0) {
			throw ExceptieComandaGresita("Eroare");
		}
		else {
			cout << "Se va afisa tabela: " << parametriIntrare[2];
		}
	}

	void setNumeTabela() {
		if (nrParametriIntrare == 3 && (strcmp(this->parametriIntrare[1], "TABLE") == 0)) {
			this->numeTabela = new char[strlen(this->parametriIntrare[2]) + 1];
			strcpy(this->numeTabela, this->parametriIntrare[2]);
		}
	}

	friend class Interpretor;
	~Display() {
		delete[] this->numeTabela;
	}
	friend ostream& operator<<(ostream& consola, Display& dis) {

		consola << "Se va afisa tabela: " << dis.parametriIntrare[2];

		return consola;
	}

	friend bool operator<(Display c1, Display c2) {
		if (strcmp(c1.parametriIntrare[5], c2.parametriIntrare[5]) != 0)
			return true;
		else return false;
	}

	char* operator[](int index) {
		return this->parametriIntrare[index];
	}
};

class BazaDeDate {
private:
	Tabela* tabela;  //relatie has-a
	const int id;
};

class Coloana {
private:
	string nume_coloana;
	string tip;
	string descriere;
public:

	Coloana() {
		this->nume_coloana = "";
		this->tip = "";
		this->descriere = "";

	}

	Coloana(string nume_c, string desc) {
		this->nume_coloana = nume_c;
		this->descriere = desc;
	}

	Coloana(string nume_c, string tipul, string desc) :nume_coloana(nume_c), tip(tipul), descriere(desc) {

	}
	Coloana(const Coloana& c) {
		this->nume_coloana = c.nume_coloana;
		this->descriere = c.descriere;
		this->tip = c.tip;
	}

	string getNumeColoana() {
		return this->nume_coloana;
	}

	string getTip() {
		return this->tip;
	}

	string getDescriere() {
		return this->descriere;
	}

	void setNumeColoana(string nume_c) {
		if (nume_c != "") {
			this->nume_coloana = nume_c;
		}

	}

	void setDescriere(string descr) {
		if (descr != "") {
			this->descriere = descr;
		}

	}

	void setTip(string tipul) {
		if (tipul != "") {
			this->tip = tipul;
		}

	}

	friend ostream& operator<<(ostream& consola, Coloana& col) {

		consola << "Nume coloana: " << col.nume_coloana << endl;
		consola << "Tipul: " << col.tip << endl;
		consola << "Descriere: " << col.descriere << endl;

		return consola;
	}

	friend istream& operator>>(istream& input, Coloana& col) {
		cout << "Nume coloana: ";
		input >> col.nume_coloana;
		cout << "Tipul: ";
		input >> col.tip;
		cout << "Descriere: ";
		input >> col.descriere;
		return input;
	}

	void operator=(Coloana& c) {
		this->nume_coloana = c.nume_coloana;
		this->tip = c.tip;
		this->descriere = c.descriere;
	}

	bool operator!() {
		if (this->nume_coloana == "") {
			return true;
		}
		else return false;
	}

	bool operator==(Coloana& c) {
		if (this->nume_coloana == c.nume_coloana && this->tip == c.tip && this->descriere == c.descriere)
			return true;
		else return false;

	}
	//prefixata
	Coloana operator--() {
		this->nume_coloana = "";
		this->descriere = "";
		this->tip = "";
		return *this;
	}
	//postfixata
	Coloana operator--(int) {
		this->nume_coloana = "";
		this->descriere = "";
		this->tip = "";
		return *this;
	}
	friend class Tabela;
};

class Tabela {
private:
	const int id;
	string numeTabela;
	static int nrTabela;
	Coloana* coloane; //descriere relatie has-a
	int nrColoane;

public:

	Tabela() : id(nrTabela) {
		this->numeTabela = "";
		this->nrColoane = 0;
		nrTabela++;
	}

	Tabela(string nume) : id(nrTabela) {
		this->numeTabela = nume;
		nrTabela++;
	}

	Tabela(string nume, int numar_c) : id(nrTabela) {
		this->numeTabela = nume;
		this->nrColoane = numar_c;
		nrTabela++;
	}

	Tabela(const Tabela& t) : id(nrTabela) {
		this->numeTabela = t.numeTabela;
		this->nrColoane = t.nrColoane;

	}

	string getNumeTabela() {
		return this->numeTabela;
	}

	int getNrColoane() {
		return this->nrColoane;
	}

	void setNumeTabela(string numeT) {
		if (numeT != "")
			this->numeTabela = numeT;
	}

	void setNrColoane(int nr) {
		if (nr != 0)
			this->nrColoane = nr;
	}

	friend ostream& operator<<(ostream& consola, Tabela& tab) {

		consola << "Nume tabela: " << tab.numeTabela << endl;
		consola << "Numar tabela: " << tab.nrTabela << endl;
		consola << "Numar coloane: " << tab.nrColoane << endl;

		return consola;
	}

	friend istream& operator>>(istream& input, Tabela& tab) {

		cout << "Nume tabela: ";
		input >> tab.numeTabela;
		cout << "Numar tabela: ";
		input >> tab.nrTabela;
		cout << "Numar coloane: ";
		input >> tab.nrColoane;

		return input;
	}

	Tabela operator+(const Tabela& t) {
		this->nrColoane += t.nrColoane;
		return *this;
	}

	void operator=(Tabela& t) {
		this->numeTabela = t.numeTabela;
		this->nrTabela = t.nrTabela;
		this->nrColoane = t.nrColoane;
	}

	bool operator==(Tabela& t) {
		if (this->numeTabela == t.numeTabela && this->nrTabela == t.nrTabela && this->nrColoane == t.nrColoane)
			return true;
		else return false;
	}

	void operator++() {
		this->nrColoane++;
	}
	void operator++(int) {
		this->nrColoane++;
	}
};
int Tabela::nrTabela = 0;

class Users {
private:
	const int id;
	static int nrUsers;
	int* Modificari = nullptr;
	string nume;
	int noEntries;
	int sectiuniAlocate[15];
public:
	Users() : id(nrUsers) {
		this->noEntries = 0;
		this->nume = "None";
		nrUsers++;
	}
	Users(string nume, int nrModificari) : id(nrUsers) {
		this->nume = nume;
		this->noEntries = nrModificari;
		nrUsers++;
	}
	Users(string nume, int* modificariAduse, int noEntries) : id(nrUsers) {
		this->nume = nume;
		this->noEntries = noEntries;
		this->Modificari = modificariAduse;
	}

	Users(const Users& u) : id(nrUsers) {
		this->nume = u.nume;
		this->Modificari = new int[u.noEntries];
		for (int i = 0; i < u.noEntries; i++) Modificari[i] = u.Modificari[i];
		this->noEntries = u.noEntries;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	void setIntrati(int nr) {
		this->noEntries = nr;
	}

	~Users() {
		if (this->Modificari) delete[] this->Modificari;
	}

	friend istream& operator>>(istream& os, Users& u) {
		os >> u.nume;
		os >> u.noEntries;
		return os;
	}

};

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
			if (comandaIntreaga[j] == ' ' || comandaIntreaga[j] == '(' || comandaIntreaga[j] == '=' || comandaIntreaga[j] == ',')
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
					Select s(this->parametriComanda, this->nrParametri, this->comandaInitiala);
					cout << s;
					if (!s.existaColoane()) {
						cout << "Eroare";
						this->nrParametri -= 1;
					}
				}
				else cout << "Eroare";
			}
			else if (strcmp(this->parametriComanda[1], "ALL") == 0) {
				Select s(this->parametriComanda, this->nrParametri, this->comandaInitiala);
				s.filtrareElemente();
			}
			else cout << "Eroare";
		}

		else if (strcmp(this->numeComanda, "CREATE") == 0) {
			VerificareFormatParanteze verif(this->comandaInitiala);
			if (verif.existaParanteze()) {
				if (verif.isBalanced()) {
					Create c(this->parametriComanda, this->nrParametri, this->comandaInitiala, verif.getPerechiParanteze());
					c.filtrareElemente();
					if (!c.existaPerechiParametri()) {
						cout << "Eroare";
						this->nrParametri -= 1;
					}
				}
				else cout << "Eroare";
			}
			else cout << "Eroare";
		}
		else if (strcmp(this->numeComanda, "UPDATE") == 0) {
			Update u(this->parametriComanda, this->nrParametri);
			u.filtrareElemente();
		}
		else if (strcmp(this->numeComanda, "INSERT") == 0) {
			Insert i(this->parametriComanda, this->nrParametri, this->comandaInitiala);
			VerificareFormatParanteze verif(this->comandaInitiala);
			if (verif.isBalanced()) {
				if (verif.existaParanteze()) {
					i.filtrareElemente();
					if (!i.existaParametri()) {
						this->nrParametri -= 1;
					}
				}
				else cout << "Eroare";
			}
			else cout << "Eroare";
		}
		else if (strcmp(this->numeComanda, "DELETE") == 0) {
			Delete del(this->parametriComanda, this->nrParametri);
			del.filtrareElemente();
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
			throw ExceptieComandaGresita("Eroare");
		}
	}

	~Interpretor() {
		for (int i = 0; i < this->nrParametri; i++) {
			if (this->parametriComanda[i]) delete[] this->parametriComanda[i];
		}
		delete[] this->parametriComanda;
	}
	friend class Select;
	friend ostream& operator<<(ostream& consola, Interpretor& inte) {
		inte.initializareComenzi();
		return consola;
	}

	char*& operator[](int index) {
		return this->parametriComanda[index];
	}

};


