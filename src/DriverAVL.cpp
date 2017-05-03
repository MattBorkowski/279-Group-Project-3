//============================================================================
// Name        : 279Group3.cpp
// Author      :
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Dictionary.cpp"
using namespace std;
Dictionary dict; //AVL Tree
char letters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' }; //used for adding letters
int import(string filename); //import method pointer
list<string> getPossible(string userInput);
int main(int argc, char *argv[]) {
	string word;
	if (argc != 2) { //exits program if the user input is wrong
		cout << "Invalid input!" << endl;
		return 0;
	}
	ifstream spell_check(argv[1]);
	if (!spell_check.is_open()) {
		cout << "Invalid File";
		return 0;
	}
	while (getline(spell_check, word)) {
		list<string> results = getPossible(word);
		for(int i = 0; i < results.size(); i++){
			cout << results[i] <<", ";
		}
		cout << endl;
	}
	spell_check.close();
}
//returns 0 if failure, 1 if success
int import(string filename) {
	string word;
	ifstream myfile;
	myfile.open(filename);
	if (myfile.is_open()) {
		while (getline(myfile, word)) {
			if (!dict.FindEntry(word)) //AVL tree crashes if we add an item twice, so maybe don't do that
				dict.AddEntry(word);
		}
		myfile.close();
		return 1;
	} else {
		return 0;
	}
}
;

list<string> getPossible(string userInput) {
	if (import("bigdict.txt") || import("dict.txt")) { //added the two possible dictionaries may have to remove!
		list<string> possibleResults;
		if (!dict.FindEntry(userInput)) {
			//add a letter
			for (int i = 0; i < 26; i++) { //adds every possible letter to every possible position
				for (int j = 0; j < userInput.size(); j++) {
					string dup = userInput;
					if (dict.FindEntry(dup.insert(j, 1, letters[i]))) { //if letter makes a word, add it to list
						possibleResults.push_front(dup);
					}
				}
			}
			//remove one letter
			for (int j = 0; j < userInput.size(); j++) {
				string dup = userInput;
				if (dict.FindEntry(dup.erase(j, 1))) {
					possibleResults.push_front(dup); //removes one letter and looks for the word
				}
			}
		}
		//switch adjacent characters
		for (int j = 0; j < userInput.size(); j++) {
			string dup = userInput;
			swap(dup[j], dup[j + 1]); //switches adjacent characters
			if (dict.FindEntry(dup)) {
				possibleResults.push_front(dup);
			}
		}
		for (int j = 0; j < userInput.size(); j++) { //do this twice
			string dup = userInput;
			swap(dup[j + 1], dup[j]);
			if (dict.FindEntry(dup)) {
				possibleResults.push_front(dup);
			}
		}
		possibleResults.unique(); //removes duplicates
		return possibleResults;
	};
