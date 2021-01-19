#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <iterator>
#include <sstream>
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
	bool existaTabel() {
		ifstream fisier("numeTabeleFisiere.txt", ios::in);

		if (fisier.is_open()) {
			string buffer;
			while (fisier >> buffer) {
				if (buffer == this->numeFisier) {
					return true;
				}
			}
			fisier.close();
			return false;
		}
		else cout << "Fisierul nu s-a deschis";
	}
};

class ImportFisier {
private:
	string numeFisier;
	int nrParametri = 0;
	string numeTabela = "";
	int nrLiniiTabela = 0;
public:
	ImportFisier(char* numeFisier, int numar, char* nume) {
		this->numeFisier = numeFisier;
		this->nrParametri = numar;
		this->numeTabela = nume;
	}
	void importFis() {
		ifstream fisier((string)this->numeTabela + "_descriere.txt");
		ifstream fiscsv(this->numeTabela + ".csv", ios::in);
		ofstream tabel((string)this->numeTabela + "_date", ios::binary | ios::app);
		if (tabel) {
			string buffer;
			while (getline(fiscsv, buffer)) {
				stringstream input(buffer);
				vector<string> elemente;
				string token = "";
				while (getline(input, token, '#')) {
					elemente.push_back(token);
				}
				for (int i = 0; i < elemente.size(); i++) {
					int dim = elemente[i].size() + 1;
					tabel.write((char*)&dim, sizeof(int));
					tabel.write(elemente[i].c_str(), dim * sizeof(char));
				}
			}
			fisier.close();
			fiscsv.close();
			tabel.close();
		}
	}

};

class VerificareTipuriDate {
	string numeParametru;
public:
	VerificareTipuriDate(char* nume) {
		this->numeParametru = nume;
	}

	bool esteNumeric() {
		int dim = this->numeParametru.size();
		for (int i = 0; i < dim; i++) {
			if (!isdigit(this->numeParametru[i])) {
				return false;
				break;
			}
		}
		return true;
	}

	bool esteLitera() {
		int dim = this->numeParametru.size();
		for (int i = 1; i < dim - 1; i++) {
			if (!isalpha(this->numeParametru[i])) {
				return false;
				break;
			}
		}
		return true;
	}

};

class ScriereFisierDate {
	char** parametriDeInserat = nullptr;
	int nrParametri = 0;
	string numeTabela = "";
	int nrLiniiTabela = 0;
public:
	ScriereFisierDate(char** parametri, int numar, char* nume) {
		this->parametriDeInserat = parametri;
		this->nrParametri = numar;
		this->numeTabela = nume;
	}

	void setNrLiniiTabela() {
		ifstream fisier(this->numeTabela + "_descriere.txt");
		string buffer;
		while (getline(fisier, buffer)) {
			this->nrLiniiTabela++;
		}
	}
	void scriereDate() {
		VerificareNumeTabel verif(this->numeTabela);
		if (verif.existaTabel()) {  // merge chiar daca e !
			fstream fisier(this->numeTabela + "_date", ios::in | ios::out | ios::binary | ios::app);
			//trebuie sa verificam daca exista deja this-:numeFisier_descrire.txt
			ifstream desc(this->numeTabela + "_descriere.txt", ios::in);
			if (fisier) {
				if (this->nrLiniiTabela == this->nrParametri * 4) {
					for (int i = 0; i < this->nrParametri; i++) {
						int j = 0;
						string buffer;
						string cuvinte[4];
						while (j < 4) {
							getline(desc, buffer);
							cuvinte[j] = buffer;
							j++;
						}
						if (cuvinte[1] == "integer" || cuvinte[1] == "float") {
							VerificareTipuriDate verif(this->parametriDeInserat[i]);
							string transf(this->parametriDeInserat[i]);
							int dim = transf.size() + 1;
							fisier.write((char*)&dim, sizeof(int));
							fisier.write(transf.c_str(), dim * sizeof(char));
						}
						else if (cuvinte[1] == "text") {
							string temp(this->parametriDeInserat[i]);
							int dim = temp.size() + 1;
							fisier.write((char*)&dim, sizeof(int));
							fisier.write(temp.c_str(), dim * sizeof(char));
						}
						else {
							cout << "Tipul nu este text" << endl;;
						}
					}

				}
				else {
					cout << "Numar parametri gresit" << endl;
				}
				desc.close();
				fisier.close();
				//cout << "merge";
			}
			else cout << "nu merge";
		}
		else cout << "Fisierul in care doriti sa inserati nu exista" << endl;
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
		numeFisierDescriere += "_descriere.txt";
		fstream tabel(numeFisierDescriere, ios::out | ios::app);
		if (tabel.is_open()) {
			tabel.seekg(0, ios::end);
			int dim = tabel.tellg();
			if (!dim) {
				tabel << this->numeColoane[0] << endl;
				tabel << this->tipuri[0] << endl;
				tabel << this->dimensiuni[0] << endl;
				tabel << this->valori_implicite[0];
			}
			tabel.clear();
			tabel.seekg(0);
			for (int i = 1; i < this->nrPerechiParametri; i++) {
				tabel << endl << this->numeColoane[i];
				tabel << endl << this->tipuri[i];
				tabel << endl << this->dimensiuni[i];
				tabel << endl << this->valori_implicite[i];
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
				while (fisiere >> buffer) {
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
		else cout << "Nu s-a deschis";

		ofstream fisier("numeTabeleFisiere.txt", ios::out | ios::app);
		if (fisier && exista==false) {
			fisier << endl << this->numeTabel;
			fisier.close();
		}

	}
};

class DisplayFisier {
private:
	char* numeTabel = nullptr;
	int nrPerechiParametri = 0; 

public:
	DisplayFisier(char* nume) {
		this->numeTabel = nume;
	}
	void display() {
		string numeFisierDescriere(this->numeTabel);
		numeFisierDescriere += "_descriere.txt";
		ifstream tabel(numeFisierDescriere, ios::in);
		string temp(this->numeTabel);
		ofstream disp(temp + "_display.txt");
		if (tabel.is_open()) {
			while (!tabel.eof()) {
				string buffer;
				for (int i = 0; i < 4; i++) {
					getline(tabel, buffer);
					cout << buffer << " ";
					disp << buffer << " ";
				}
				disp << endl;
				cout << endl;
			}
			tabel.close();
		}
		else {
			cout << "Nu s-a deschis";
		}

	}

};

class DropFisier {
private:
	char* numeTabel = nullptr;
public:
	DropFisier(char* nume) {
		this->numeTabel = nume;
	}
	void DropFis() {
		//ifstream fisier;
		VerificareNumeTabel verif(this->numeTabel);
		string temp1(this->numeTabel);
		string temp2(this->numeTabel);
		if (verif.existaTabel()) {
			temp1 += "_descriere.txt";
			temp2 += "_date";
			remove(temp1.c_str());
			remove(temp2.c_str());
		}
		else {
			cout << "Fisierul nu exista!";
		}
		string* vectorSortat = nullptr;
		int nrTabele = 0;
		ifstream tabele("numeTabeleFisiere.txt", ios::in);
		if (tabele) {
			string buffer;
			while (tabele >> buffer) {
				nrTabele++;
			}
			string* nume = new string[nrTabele];
			vectorSortat = new string[nrTabele - 1];
			tabele.clear();
			tabele.seekg(0);
			int i = 0;
			while (getline(tabele, buffer)) {
				nume[i] = buffer;
				i++;
			}
			string temp(this->numeTabel);
			for (int i = 0, j = 0; i < nrTabele; i++) {
				if (temp != nume[i]) {
					vectorSortat[j] = nume[i];
					j++;
				}
			}
			tabele.close();
		}
		ofstream tabele1("numeTabeleFisiere.txt", ios::out | ios::trunc);
		if (tabele1) {
			for (int i = 0; i < nrTabele - 1; i++)
				tabele1 << vectorSortat[i];
		}

	}
};

class SelectFisier {
	char** numeColoane = nullptr;
	char* numeTabel = nullptr;
	int nrPerechiParametri = 0;
	int nrColoane = 0;
	char* numeColoanaWhere = nullptr;
	string* numeColoaneDesc = nullptr;
	int nrColoaneDesc = 0;
	char* valoareDeFiltrat = nullptr;
	int nrFisiereSelect = 0;
public:
	SelectFisier(char** coloane, char* tabel, int nrcol, char* numeColWhere, char* valoareFiltru, int nrSelect) {
		this->numeColoane = coloane;
		this->numeTabel = tabel;
		this->nrColoane = nrcol;
		this->numeColoanaWhere = numeColWhere;
		this->valoareDeFiltrat = valoareFiltru;
		this->nrFisiereSelect = nrSelect;
	}

	SelectFisier(char** coloane, char* tabel, int nrcol, int nrSelect) {
		this->numeColoane = coloane;
		this->numeTabel = tabel;
		this->nrColoane = nrcol;
		this->nrFisiereSelect = nrSelect;
	}

	void setNrPerechiParametri() {
		string temp(this->numeTabel);
		ifstream desc(temp + "_descriere.txt", ios::in);
		if (desc) {
			int contor = 0;
			string buffer;
			while (getline(desc, buffer)) {
				if (contor == 3) {
					this->nrPerechiParametri++;
					contor = 0;
				}
				contor++;
			}
			desc.close();
		}
		else cout << "Nu s-a deschis" << endl;
	}
	void setNumeColoaneDesc() {
		string temp(this->numeTabel);
		ifstream desc(temp + "_descriere.txt", ios::in, ios::trunc);
		this->numeColoaneDesc = new string[this->nrPerechiParametri];
		if (desc) {
			int contor = 0;
			int i = 0;
			string buffer;
			while (getline(desc, buffer)) {
				if (contor == 4) contor = 0;
				if (contor == 0) {
					this->numeColoaneDesc[i] = buffer;
					i++;
				}
				contor++;
			}
			this->nrColoaneDesc = i;
			desc.close();
		}
		else cout << "Nu s-a deschis" << endl;
	}
	void afisareDinFisier() {
		string temp(this->numeTabel);
		ifstream fisier(temp + "_date", ios::binary | ios::in, ios::trunc);
		if (fisier) {
			int nrParametriFisier = 0;
			char buffer[100];
			int dim;
			while (fisier.read((char*)&dim, sizeof(int))) {
				fisier.read(buffer, dim * sizeof(char));
				//cout << buffer << " ";
				nrParametriFisier++;
			}
			string* parametriDinFisier = new string[nrParametriFisier];
			fisier.clear();
			fisier.seekg(0);
			int i = 0;
			while (fisier.read((char*)&dim, sizeof(int))) {
				fisier.read(buffer, dim * sizeof(char));
				parametriDinFisier[i] = buffer;
				i++;
			}
			if (this->numeColoanaWhere != nullptr && strcmp(this->numeColoane[0], "ALL") != 0) {
				for (int i = 0; i < this->nrColoane; i++) {
					for (int j = 0; j < this->nrPerechiParametri; j++) {
						if (this->numeColoane[i] == this->numeColoaneDesc[j]) { //verifica daca exista coloana in descriere
							int p = j; //periodic
							int inc = 0;
							bool exista = false; //pp ca nu exista 
							//inc poate avea valori 0,1,2 -> ne folosim de ele relativ la p
							while (inc < this->nrPerechiParametri) {
								if (this->numeColoanaWhere == this->numeColoaneDesc[inc]) {
									exista = true;
									break;
								}
								inc++;
							}
							if (exista) {
								string sel = "SELECT_";
								string str = to_string(this->nrFisiereSelect);
								ofstream select(sel + str + ".txt", ios::out | ios::app, ios::trunc);
								cout << endl << this->numeColoaneDesc[j] << ": ";
								select << this->numeColoaneDesc[j] << ": ";
								while (p < nrParametriFisier) {
									string temp(this->valoareDeFiltrat);
									if (parametriDinFisier[inc] == temp) {
										select << parametriDinFisier[p] << " ";
										cout << parametriDinFisier[p] << " ";
									}
									inc += this->nrColoaneDesc;
									p += this->nrColoaneDesc;
								}
							}
							else {
								cout << "Coloana de filtrat nu exista!";
							}
						}
					}
				}
			}
			else if (this->numeColoanaWhere == nullptr && strcmp(this->numeColoane[0], "ALL") != 0) {
				for (int i = 0; i < this->nrColoane; i++) {
					for (int j = 0; j < this->nrPerechiParametri; j++) {
						if (this->numeColoane[i] == this->numeColoaneDesc[j]) {
							int p = j;
							string sel = "SELECT_";
							string str = to_string(this->nrFisiereSelect);
							ofstream select(sel + str + ".txt", ios::out | ios::app, ios::trunc);
							cout << endl << this->numeColoaneDesc[j] << ": ";
							select << this->numeColoaneDesc[j] << ": ";
							while (p < nrParametriFisier) {
								cout << parametriDinFisier[p] << " ";
								select << parametriDinFisier[p] << " ";
								p += this->nrColoaneDesc;
							}
							select << endl;
						}
					}
					cout << endl;
				}
			}
			else if (this->numeColoanaWhere == nullptr && strcmp(this->numeColoane[0], "ALL") == 0) {
				fisier.clear();
				fisier.seekg(0);
				for (int i = 0; i < this->nrColoaneDesc; i++) {
					int p = i;
					string sel = "SELECT_";
					string str = to_string(this->nrFisiereSelect);
					ofstream select(sel + str + ".txt", ios::out | ios::app, ios::trunc);
					cout << endl << this->numeColoaneDesc[i] << ": ";
					select << this->numeColoaneDesc[i] << ": ";
					while (p < nrParametriFisier) {
						cout << parametriDinFisier[p] << " ";
						select << parametriDinFisier[p] << " ";
						p += this->nrColoaneDesc;
					}
					select << endl;
				}
			}
			else if (this->numeColoanaWhere != nullptr && strcmp(this->numeColoane[0], "ALL") == 0) {
				for (int i = 0; i < this->nrColoaneDesc; i++) {
					int p = i;
					int inc = 0;
					bool exista = false; //pp ca nu exista 
					//inc poate avea valori 0,1,2 -> ne folosim de ele relativ la p
					while (inc < this->nrPerechiParametri) {
						if (this->numeColoanaWhere == this->numeColoaneDesc[inc]) {
							exista = true;
							break;
						}
						inc++;
					}
					if (exista) {
						string sel = "SELECT_";
						string str = to_string(this->nrFisiereSelect);
						ofstream select(sel + str + ".txt", ios::out | ios::app, ios::trunc);
						cout << endl << this->numeColoaneDesc[i] << ": ";
						select << this->numeColoaneDesc[i] << " ";
						while (p < nrParametriFisier) {
							string temp(this->valoareDeFiltrat);
							if (parametriDinFisier[inc] == temp) {
								cout << parametriDinFisier[p] << " ";
								select << parametriDinFisier[p] << " ";
							}
							inc += this->nrColoaneDesc;
							p += this->nrColoaneDesc;
						}
						select << endl;
					}
					else {
						cout << "Coloana de filtrat nu exista!";
					}
				}
			}
			fisier.close();
		}
	}
	friend class Select;
	friend class Intepretor;
};

class UpdateFisier {
	char* numeTabel = nullptr;
	char* numeColoana = nullptr;
	char* valoareColoana = nullptr;
	char* coloanaWhere = nullptr;
	char* valoareWhere = nullptr;
	int nrPerechiParametri = 0;
	int nrColoaneDesc = 0;
	int nrParametriDinFisier = 0;
	string* numeColoaneDesc = nullptr;
	string* parametriModificati = nullptr;

public:
	UpdateFisier(char* nume, char* coloana, char* valCol, char* colWhere, char* valWhere) {
		this->numeTabel = nume;
		this->numeColoana = coloana;
		this->valoareColoana = valCol;
		this->coloanaWhere = colWhere;
		this->valoareWhere = valWhere;
	}

	void setNrPerechiParametri() {
		string temp(this->numeTabel);
		ifstream desc(temp + "_descriere.txt", ios::in);
		if (desc) {
			int contor = 0;
			string buffer;
			while (getline(desc, buffer)) {
				if (contor == 3) {
					this->nrPerechiParametri++;
					contor = 0;
				}
				contor++;
			}
			desc.close();
		}
		else cout << "Nu s-a deschis" << endl;
	}
	void setNumeColoaneDesc() {
		string temp(this->numeTabel);
		ifstream desc(temp + "_descriere.txt", ios::in);
		this->numeColoaneDesc = new string[this->nrPerechiParametri];
		if (desc) {
			int contor = 0;
			int i = 0;
			string buffer;
			while (getline(desc, buffer)) {
				if (contor == 4) contor = 0;
				if (contor == 0) {
					this->numeColoaneDesc[i] = buffer;
					i++;
				}
				contor++;
			}
			this->nrColoaneDesc = i;
			desc.close();
		}
		else cout << "Nu s-a deschis" << endl;
	}
	void modificareParametriFisierInitial() {
		string temp(this->numeTabel);
		ifstream fisier(temp + "_date", ios::binary | ios::in);
		if (fisier) {
			int nrParametriFisier = 0;
			char buffer[100];
			int dim;
			while (fisier.read((char*)&dim, sizeof(int))) {
				fisier.read(buffer, dim * sizeof(char));
				//cout << buffer << " ";
				nrParametriFisier++;
			}
			this->nrParametriDinFisier = nrParametriFisier;
			string* parametriDinFisier = new string[nrParametriFisier];
			fisier.clear();
			fisier.seekg(0);
			int i = 0;
			while (fisier.read((char*)&dim, sizeof(int))) {
				fisier.read(buffer, dim * sizeof(char));
				parametriDinFisier[i] = buffer;
				i++;
			}
			if (this->coloanaWhere != nullptr) {
				for (int j = 0; j < this->nrPerechiParametri; j++) {
					if (this->numeColoana == this->numeColoaneDesc[j]) {
						int p = j;
						int inc = 0;
						bool exista = false; //pp ca nu exista 
						//inc poate avea valori 0,1,2 -> ne folosim de ele relativ la p
						while (inc < this->nrPerechiParametri) {
							if (this->coloanaWhere == this->numeColoaneDesc[inc]) {
								exista = true;
								break;
							}
							inc++;
						}
						if (exista) {
							while (p < nrParametriFisier) {
								string temp(this->valoareWhere);
								if (parametriDinFisier[inc] == temp) {
									parametriDinFisier[p] = (string)this->valoareColoana;
								}
								inc += this->nrColoaneDesc;
								p += this->nrColoaneDesc;
							}
						}
						else {
							cout << "Coloana de filtrat nu exista!";
						}
					}
				}
				this->parametriModificati = new string[nrParametriFisier];
				for (int i = 0; i < nrParametriFisier; i++) {
					this->parametriModificati[i] = parametriDinFisier[i];
				}
			}
		}
	}

	void modificareFisierInitial() {
		ofstream fisier((string)this->numeTabel + "_date", ios::out | ios::trunc);
		if (fisier) {
			for (int i = 0; i < this->nrParametriDinFisier; i++) {
				int dim = this->parametriModificati[i].size() + 1;
				fisier.write((char*)&dim, sizeof(int));
				fisier.write(this->parametriModificati[i].c_str(), dim * sizeof(char));
			}
			fisier.close();
		}
	}

};

class DeleteFisier {
	char* numeTabel = nullptr;
	char* coloanaWhere = nullptr;
	char* valoareWhere = nullptr;
	int nrPerechiParametri = 0;
	int nrColoaneDesc = 0;
	int nrParametriDinFisier = 0;
	string* numeColoaneDesc = nullptr;
	string* parametriModificati = nullptr;
	int lg = 0;
public:
	DeleteFisier(char* numeTabel, char* colWhere, char* valWhere) {
		this->numeTabel = numeTabel;
		this->coloanaWhere = colWhere;
		this->valoareWhere = valWhere;
	}
	void setNrPerechiParametri() {
		string temp(this->numeTabel);
		ifstream desc(temp + "_descriere.txt", ios::in);
		if (desc) {
			int contor = 0;
			string buffer;
			while (getline(desc, buffer)) {
				if (contor == 3) {
					this->nrPerechiParametri++;
					contor = 0;
				}
				contor++;
			}
			desc.close();
		}
		else cout << "Nu s-a deschis" << endl;
	}

	void setNumeColoaneDesc() {
		string temp(this->numeTabel);
		ifstream desc(temp + "_descriere.txt", ios::in);
		this->numeColoaneDesc = new string[this->nrPerechiParametri];
		if (desc) {
			int contor = 0;
			int i = 0;
			string buffer;
			while (getline(desc, buffer)) {
				if (contor == 4) contor = 0;
				if (contor == 0) {
					this->numeColoaneDesc[i] = buffer;
					i++;
				}
				contor++;
			}
			this->nrColoaneDesc = i;
			desc.close();
		}
		else cout << "Nu s-a deschis" << endl;
	}

	void modificareParametriFisierInitial() {
		string temp(this->numeTabel);
		ifstream fisier(temp + "_date", ios::binary | ios::in);
		if (fisier) {
			int nrParametriFisier = 0;
			char buffer[100];
			int dim;
			while (fisier.read((char*)&dim, sizeof(int))) {
				fisier.read(buffer, dim * sizeof(char));
				nrParametriFisier++;
			}
			this->nrParametriDinFisier = nrParametriFisier;
			string* parametriDinFisier = new string[nrParametriFisier];
			fisier.clear();
			fisier.seekg(0);
			int i = 0;
			while (fisier.read((char*)&dim, sizeof(int))) {
				fisier.read(buffer, dim * sizeof(char));
				parametriDinFisier[i] = buffer;
				i++;
			}
			fstream deleteFis("test.txt", ios::in | ios::out | ios::trunc);
			if (this->coloanaWhere != nullptr) {
				for (int i = 0; i < this->nrColoaneDesc; i++) {
					int p = i;
					int inc = 0;
					bool exista = false; //pp ca nu exista 
					//inc poate avea valori 0,1,2, etc. -> ne folosim de ele relativ la p
					while (inc < this->nrPerechiParametri) {
						if (this->coloanaWhere == this->numeColoaneDesc[inc]) {
							exista = true;
							break;
						}
						inc++;
					}
					if (exista) {
						string atr(this->numeTabel);
						cout << endl << this->numeColoaneDesc[i] << ": ";
						while (p < nrParametriFisier) {
							string temp(this->valoareWhere);
							if (parametriDinFisier[inc] == temp) {
								deleteFis << parametriDinFisier[p] << endl;
								//parametriDinFisier[p] = "0";
								inc += this->nrColoaneDesc;
								p += this->nrColoaneDesc;
							}
							else {
								cout << parametriDinFisier[p] << " ";
								inc += this->nrColoaneDesc;
								p += this->nrColoaneDesc;
							}
						}
					}
					else {
						cout << "Coloana de filtrat nu exista!";
					}
					deleteFis << endl;
				}
			}

			deleteFis.close();
			cout << endl;

			ifstream citire("test.txt", ios::in);
			vector<string> dateDeSters;
			string temporary;
			while (getline(citire, temporary)) {
				if (!temporary.empty()) dateDeSters.push_back(temporary);
				else break;
			}
			for (int i = 0; i < dateDeSters.size(); i++) {
				int pozitie = 0;
				while (pozitie < nrParametriFisier) {
					if (dateDeSters[i] == parametriDinFisier[pozitie]) break;
					else pozitie++;
				}
				int punctStart = pozitie;
				int contor = 0;
				while (contor < this->nrPerechiParametri && punctStart < nrParametriFisier) {
					parametriDinFisier[punctStart + contor] = "/";
					contor++;
				}
			}
			fisier.close();
			deleteFis.close();
			remove("test.txt");
			vector<string> dateDeInserat;
			for (int i = 0; i < this->nrParametriDinFisier; i++) {
				if (parametriDinFisier[i] != "/") {
					dateDeInserat.push_back(parametriDinFisier[i]);
				}
			}
			ofstream file(temp + "_date", ios::binary | ios::trunc | ios::out);
			for (int i = 0; i < dateDeInserat.size(); i++) {
				int dim = dateDeInserat[i].size() + 1;
				file.write((char*)&dim, sizeof(int));
				file.write(dateDeInserat[i].c_str(), dim * sizeof(char));
			}
			file.close();


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

class Comanda {
	int lungime = 0;
	Comanda* var[10];
public:
	virtual void printTab() = 0;
	virtual int nrParam() = 0;
	void VectorPointer() {
		this->lungime = 10;
		vector<Comanda> vect;
		Comanda* var[10];
		for (int i = 0; i < 10; i++) {
			vect[i] = *var[i];
		}
	}
};

class Create {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare = 0;
	char** numeColoane = nullptr;
	char** tipuri = nullptr;
	char** dimensiuni = nullptr;
	char** valori_implicite = nullptr;
	char* numeTabel = nullptr;
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
					cout << endl << "Tabel: " << this->parametriIntrare[2] << endl;
					this->numeTabel = this->parametriIntrare[2];
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
							cout << endl << "Nume coloana: " << this->numeColoane[this->nrPerechiParametri] << endl;
						}

					}
					CreareFisier crt(this->parametriIntrare[2], this->numeColoane, this->tipuri, this->dimensiuni, this->valori_implicite, this->nrPerechiParametri);
					VerificareNumeTabel verif(this->numeTabel);
					if (!verif.existaTabel()) {
						crt.generareFisiere();
						crt.generareFisierTabele();
					}
					else {
						cout << "Tabelul exista deja" << endl;
					}

				}
				else cout << "Eroare"<<endl ;
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
					cout <<endl << "Tabel: " << this->parametriIntrare[2] << endl;
					this->numeTabel = this->parametriIntrare[2];
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
							cout <<endl << "Nume coloana: " << this->numeColoane[this->nrPerechiParametri] << endl;
						}
					}
					CreareFisier crt(this->parametriIntrare[2], this->numeColoane, this->tipuri, this->dimensiuni, this->valori_implicite, this->nrPerechiParametri);
					VerificareNumeTabel verif(this->numeTabel);
					crt.generareFisierTabele();
					crt.generareFisiere();
					/*if (!verif.existaTabel()){

					}
					else {
						cout << "Tabelul exista deja" << endl;
					}*/
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

	//void getPerechiParametri

	friend class Interpretor;
	friend class ScriereFisierDate;

	friend ostream& operator<<(ostream& os, Create& c) {
		c.filtrareElemente();
		return os;
	}
};

class Update : public Comanda {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char* numeTabela = nullptr;
	char* numeColoana = nullptr;
	char* valoareColoana = nullptr;
	char* numeColWhere = nullptr;
	char* valoareWhere = nullptr;
public:

	Update(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void printTab() {
		cout << "Tabela selectata pentru actualizare este " << this->numeTabela << endl;
		cout << "Se actualizeaza coloana: " << this->numeColoana << endl;
		cout << "Avand conditia " << this->numeColWhere << " = " << this->valoareWhere << endl;
	}

	int nrParam() {
		for (int i = 0; i < nrParametriIntrare; i++) {
			cout << "Parametri comenzii introdusi sunt:" << endl;
			cout << this->parametriIntrare[i];
		}
		cout << endl;
		return 1;
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
			cout << "Valoare filtru: " << parametriIntrare[7] << endl;
			this->numeTabela = this->parametriIntrare[1];
			this->numeColoana = this->parametriIntrare[3];
			this->valoareColoana = this->parametriIntrare[4];
			this->numeColWhere = this->parametriIntrare[6];
			this->valoareWhere = this->parametriIntrare[7];
			UpdateFisier fis(this->numeTabela, this->numeColoana, this->valoareColoana, this->numeColWhere, this->valoareWhere);
			fis.setNrPerechiParametri();
			fis.setNumeColoaneDesc();
			fis.modificareParametriFisierInitial();
			fis.modificareFisierInitial();
		}

	}

	friend class Interpretor;

	friend ostream& operator<<(ostream& consola, Update& up) {

		consola << "Tabela: " << up.parametriIntrare[1] << endl;
		consola << "Coloana: " << up.parametriIntrare[3] << endl;
		consola << "Valoare: " << up.parametriIntrare[4] << endl;
		consola << "Filtru: " << up.parametriIntrare[6] << endl;
		consola << "Valoare filtru: " << up.parametriIntrare[7] << endl;
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
				this->numeTabela = this->parametriIntrare[2];
				cout << "Coloane:  " << nrParametriInsert << endl;
				for (int i = 0; i < nrParametriInsert; i++) {
					cout << "Coloana " << i + 1 << " value: " << parametriIntrare[i + 4] << endl;
					this->parametriInsert[i] = this->parametriIntrare[i + 4];
				}
				ScriereFisierDate scrie(this->parametriInsert, this->nrParametriInserare, this->numeTabela);
				scrie.setNrLiniiTabela();
				scrie.scriereDate();
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

class Delete : public Comanda {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char* numeTabel = nullptr;
	char* coloanaWhere = nullptr;
	char* valoareWhere = nullptr;

public:

	Delete(char** parametriIntrare, int nrParam) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
	}

	void printTab() {
		cout << "Tabela pentru care se sterge o inregistrare este: " << this->numeTabel << endl;
		cout << "Inregistrarea " << this->valoareWhere << " din coloana " << this->coloanaWhere << " va fi eliminata" << endl;
	}

	int nrParam() {
		cout << "Parametri comenzii DELETE sunt in numar de: "; return this->nrParametriIntrare;
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
				this->numeTabel = this->parametriIntrare[2];
				this->coloanaWhere = this->parametriIntrare[4];
				this->valoareWhere = this->parametriIntrare[5];
				cout << "Tabela: " << parametriIntrare[2] << endl;
				cout << "Coloana filtru: " << parametriIntrare[4] << " cu valoarea " << parametriIntrare[5];
				DeleteFisier del(this->numeTabel, this->coloanaWhere, this->valoareWhere);
				del.setNrPerechiParametri();
				del.setNumeColoaneDesc();
				del.modificareParametriFisierInitial();

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

class Import {
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char* numeTabela = nullptr;
	char* numeFisier = nullptr;
public:
	Import(char** parametri, int nr) {
		this->parametriIntrare = parametri;
		this->nrParametriIntrare = nr;
	}

	void filtrareElemente() {
		if (this->nrParametriIntrare - 1 != 2) {
			throw ExceptieComandaGresita("Eroare");
		}
		else {
			cout << "Se vor insera coloanele din fisierul " << parametriIntrare[2] << " in tabela " << parametriIntrare[1] << endl;
			this->numeTabela = this->parametriIntrare[1];
			this->numeFisier = this->parametriIntrare[2];
			ImportFisier import(this->numeFisier, this->nrParametriIntrare, this->numeTabela);
			import.importFis();
		}
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
			this->numeTabela = this->parametriIntrare[2];
			DropFisier drop(this->numeTabela);
			drop.DropFis();

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
			cout << "Se va afisa tabela: " << parametriIntrare[2] << endl;
			this->numeTabela = this->parametriIntrare[2];
			DisplayFisier disp(this->numeTabela);
			disp.display();
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

class Tabela : public Coloana {
private:
	int id;
	string numeTabela;
	static int nrTabela;
	Coloana* coloane; //descriere relatie has-a
	int nrColoane;
public:
	Tabela(int Id, string Nume, string Tip) : Coloana(Nume, Tip) {
		this->id = Id;
	}

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
protected:
	int id = 0;
	static int nrUsers;
	int* Modificari = nullptr;
	int noEntries;
	int sectiuniAlocate[15];
	int* pe = nullptr;
public:
	string nume;
	Users() : id(nrUsers++) {
		this->noEntries = 0;
		this->nume = "None";

	}
	Users(string nume, int nrModificari) : id(nrUsers++) {
		this->nume = nume;
		this->noEntries = nrModificari;

	}
	Users(string nume, int* modificariAduse, int noEntries) : id(nrUsers++) {
		this->nume = nume;
		this->noEntries = noEntries;
		this->Modificari = modificariAduse;
	}

	Users(const Users& u) : id(nrUsers++) {
		this->nume = u.nume;
		this->Modificari = new int[u.noEntries];
		/*for (int i = 0; i < u.noEntries; i++) Modificari[i] = u.Modificari[i];*/
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

	friend ostream& operator<<(ostream& os, Users& u) {
		os << u.nume << endl;
		os << u.noEntries << endl;
		return os;
	}
	void operator=(Users& c) {
            this->id = c.id;
            this->nrUsers = c.nrUsers;
            this->nume = c.nume;
            this->noEntries = c.noEntries;
           /* for (int i = 0; i < this->noEntries; i++) {
                this->Modificari[i] = c.Modificari[i];
            } */
            for (int i = 0; i < 15; i++) {
                this->sectiuniAlocate[i] = c.sectiuniAlocate[i];
            }
        }
	bool operator <(const Users& u) const {
          if(noEntries < u.noEntries) {
              return true;
          }

          return false;
       }

};
int Users::nrUsers = 0;

class BazaDeDate : public Users {
	Tabela* tabela;  //relatie has-a
	int cod = 0;
	string nume = " ";
public:
	BazaDeDate(string Nume, int* Modif, int Cod) : Users(Nume, *Modif) {
		this->cod = Cod;
	}
};

class Select : public Comanda {
private:
	char** parametriIntrare = nullptr;
	int nrParametriIntrare;
	char** numeColoane = nullptr;
	char* numeTabela = nullptr;
	int nrColoane = 0;
	string comandaInitiala = "";
	char* coloanaConditieWhere = nullptr;
	static int nrSelect;

public:
	Select(char** parametriIntrare, int nrParam, string comandaInitiala) {
		this->parametriIntrare = parametriIntrare;
		this->nrParametriIntrare = nrParam;
		this->comandaInitiala = comandaInitiala;
	}

	void printTab() {
		cout << "------------" << this->numeTabela << "------------" << endl;
		for (int i = 0; i < nrColoane; i++) {
			cout << numeColoane[i] << "   " << endl;
		}
	}

	int nrParam() {
		cout << "Numarul parametrilor este: ";
		return nrParametriIntrare;
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
					this->coloanaConditieWhere = this->parametriIntrare[5];
					nrSelect++;
					SelectFisier sel(this->numeColoane, this->numeTabela, this->nrColoane, this->coloanaConditieWhere, this->parametriIntrare[6], nrSelect);
					this->coloanaConditieWhere = this->parametriIntrare[5];
					sel.setNrPerechiParametri();
					sel.setNumeColoaneDesc();
					sel.afisareDinFisier();

				}
				else if (!esteEgal && nrParametriWhere == 0) {
					cout << "Se vor afisa toate coloanele din tabela " << this->numeTabela;
					nrSelect++;
					SelectFisier sel(this->numeColoane, this->numeTabela, this->nrColoane, nrSelect);
					sel.setNrPerechiParametri();
					sel.setNumeColoaneDesc();
					sel.afisareDinFisier();

				}
				else cout << "Eroare";
			}

			else if (nrCol == 1 && corect) {
				if (existaWhere && esteEgal && nrCorectParametriWhere) {
					cout << "Se va selecta coloana " << this->parametriIntrare[1] << " din tabela " <<
						this->parametriIntrare[3] << " unde valoarea coloanei " << this->parametriIntrare[5] <<
						" este " << this->parametriIntrare[6] << endl;
					this->coloanaConditieWhere = this->parametriIntrare[5];
					nrSelect++;
					SelectFisier sel(this->numeColoane, this->numeTabela, this->nrColoane, this->coloanaConditieWhere, this->parametriIntrare[6], nrSelect);
					sel.setNrPerechiParametri();
					sel.setNumeColoaneDesc();
					sel.afisareDinFisier();
				}
				else {
					cout << "Se va selecta coloana " << this->parametriIntrare[1] << " din tabela " <<
						this->parametriIntrare[3] << endl;
					nrSelect++;
					SelectFisier sel(this->numeColoane, this->numeTabela, this->nrColoane, nrSelect);
					sel.setNrPerechiParametri();
					sel.setNumeColoaneDesc();
					sel.afisareDinFisier();
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
					this->coloanaConditieWhere = this->parametriIntrare[k + 3];
					nrSelect++;
					SelectFisier sel(this->numeColoane, this->numeTabela, this->nrColoane, this->coloanaConditieWhere, this->parametriIntrare[k + 4], nrSelect);
					sel.setNrPerechiParametri();
					sel.setNumeColoaneDesc();
					sel.afisareDinFisier();
				}
				else if (corect) {
					cout << "Se vor selecta coloanele ";
					int k = 1;
					for (k = 1; k <= nrCol; k++) {
						cout << this->parametriIntrare[k] << ", ";
					}
					cout << "din tabela " << this->parametriIntrare[k + 1] << endl;
					nrSelect++;
					SelectFisier sel(this->numeColoane, this->numeTabela, this->nrColoane, nrSelect);
					sel.setNrPerechiParametri();
					sel.setNumeColoaneDesc();
					sel.afisareDinFisier();
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
	friend class SelectFisier;

	char* operator[](int index) {
		if (index > 0 && index < this->nrColoane)
			return this->numeColoane[index];
	}

	friend ostream& operator<<(ostream& os, Select& s) {
		s.filtrareElemente();
		return os;
	}
};
int Select::nrSelect = 0;

class Interpretor {
private:
	char* numeComanda = nullptr;
	int dimensiuneComanda;
	char** parametriComanda = nullptr;
	int nrParametri = 0;
	string comandaInitiala = "";
public:
	Interpretor() {
		this->dimensiuneComanda = 0;
		this->nrParametri = 0;
	}
	Interpretor(string comandaIntreaga, int size) : dimensiuneComanda(size) {
		this->comandaInitiala = comandaIntreaga;
		/*bool temp = false;
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
		this->parametriComanda = new char* [nrCuvinte];*/

		char* input = new char[this->dimensiuneComanda + 1];
		strcpy(input, comandaIntreaga.c_str());
		char delim[] = " =,()";
		bool existaSpatiu = false;
		for (int i = 0; i < strlen(input); i++) {
			if (input[i] == '\"') {
				for (int j = i + 1; j < strlen(input); j++) {
					if (input[j] == ' ') {
						input[j] = '_';
						existaSpatiu = true;
					}
					else if (input[j] == '\"') {
						i = j;
						break;
					}
				}
			}
		}
		bool temp = false;
		int nrCuvinte = 0;
		for (int j = 0; j < strlen(input); j++) {
			if (input[j] == ' ' || input[j] == '(' || input[j] == '=' || input[j] == ',')
				temp = false;
			else if (!temp) {
				temp = true;
				nrCuvinte++;
			}
		}

		this->nrParametri = nrCuvinte;
		this->parametriComanda = new char* [nrCuvinte];

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
		else if (strcmp(this->numeComanda, "IMPORT") == 0) {
			Import imp(this->parametriComanda, this->nrParametri);
			imp.filtrareElemente();
		}
		else {
			throw ExceptieComandaGresita("Eroare");
		}
	}

	/*~Interpretor() {
		for (int i = 0; i < this->nrParametri; i++) {
			if (this->parametriComanda[i]) delete[] this->parametriComanda[i];
		}
		delete[] this->parametriComanda;
	}*/
	friend class Select;
	friend class SelectFisier;
	friend ostream& operator<<(ostream& consola, Interpretor& inte) {
		inte.initializareComenzi();
		return consola;
	}

	char*& operator[](int index) {
		return this->parametriComanda[index];
	}
};
