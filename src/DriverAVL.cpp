//============================================================================
// Name        : 279Group3.cpp
// Author      : Matt Borkowski
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[]) {
	Dictionary dict;
	string word;
	if(argc != 2){
		cout << "wrong input!"<< endl;
		return 0;
	}
	ifstream input_file("dict.txt");
	if (!input_file.is_open()) {
		cout << "Invalid File";
		return 0;
	}
	while (getline(input_file, word)) {
		dict.AddEntry(word);
	}
	input_file.close();

	ifstream spell_check(argv[1]);
	if (!spell_check.is_open()) {
		cout << "Invalid File";
		return 0;
	}
	while (getline(spell_check, word)) {
		dict.FindEntry(word);
	}
	spell_check.close();
	return 0;
}
