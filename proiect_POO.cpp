#include <iostream>
#include <string>
#pragma warning(disable:4996)
//#include "clase.h"

using namespace std;

int main(int argc, char* argv[]) {
	string text;
	getline(cin, text, ';');
	char* input = new char[text.size() + 1];
	int i;
	for (i = 0; i < text.size(); i++) {
		input[i] = text[i];
	}
	input[i + 1] = '\0';

	
	char* token = strtok(input, " ");
	for (int i = 0; i < strlen(token); i++) cout << token[i];

}