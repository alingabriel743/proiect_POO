#pragma once
#include <iostream>
#include <string>

using namespace std;


void tipComanda(char* tip) {
	char delimiter[] = " ";
	char* token = strtok(tip, delimiter);
	while (token) {

	}
	if (strcmp(tip, "SELECT")) {
		Select();
	}
	else if (strcmp(tip, "UPDATE")) {
		Update();
	}
}

class tipComanda {
private:
	char* nume_comanda = nullptr;
public:
	tipComanda(const char* nume) {
		//this->nume_comanda = nume;
	}
	tipComanda(const tip_comanda& tip) {
		this->nume_comanda = tip.nume_comanda;
	}
	switch (this->nume_comanda) {
		case1: "SELECT";
	}

};

class Select {

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

class Coloana {
private:
	string nume_coloana;
	string tip;
	string descriere;
};