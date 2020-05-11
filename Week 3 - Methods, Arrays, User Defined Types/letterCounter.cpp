// letterCounter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//this program will show how to use an array as a counter
//the beginnings of try-catch will be handled
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <string>
#include <string.h>//need for strcpy_s

using namespace std;
int letters[26];
int l;
char let;
int numLetters = 0;
int numLines = 0;
int numWords = 0;

void parseFile(string path);
void countLetters(string line);
void countWords(string line);	//not optimal but better to show the process
void showCounts();

int main()
{
	for (l = 0; l < 26; l++) {
		letters[l] = 0;
	}
	string fileName = "frost.txt";
	cout << "Enter the file name ";
	cin >> fileName;
	parseFile(fileName);
	cout << "Letter counts in " << fileName << endl;
	showCounts();
}
void parseFile(string path) {
	ifstream fin;
	string line = "";
	fin.open(path);
	if (fin.fail())
	{
		cout << path << " did not open" << endl;
		exit(1);
	}
	while (getline(fin, line)) {
		countLetters(line);
		countWords(line);
		numLines++;
	}
	fin.close();
}

void countLetters(string line) {
	//capital A = 65. Subtracting 65 from the letter will get to 
	for (l = 0; l < line.length(); l++) {

		let = toupper(line.at(l));	//convert to uppercase
	//	cout << let;

		if (let >= 65 && let <= 90) {	//verify the item is a letter
			letters[let - 65] ++;
			numLetters++;
		}
	}


}//end of countLetters

void countWords(string line) {
	//strtok_s setup
	//https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strtok-s-strtok-s-l-wcstok-s-wcstok-s-l-mbstok-s-mbstok-s-l?view=vs-2019
	//strcpy_s setup
	//https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strcpy-s-wcscpy-s-mbscpy-s?view=vs-2019

	//convert string to char *
	char* cstr = new char[line.length() + 1];
	strcpy_s(cstr, line.length() + 1, line.c_str());
	//need because strtok wants old school string
	//stringstream uses vectors, I avoided that one on purpose

	//find the first space
	char* token;		//holds location of delimiter in the string
	char* nextToken;	//needed to walk through the string
	token = strtok_s(cstr, " ", &nextToken);
	while (token != NULL) {
		numWords++;
		token = strtok_s(NULL, " ", &nextToken);
					//find each next token in the string
	}

}//end of countWords

void showCounts() {
	cout << left << setw(10) << "Lines" << right << setw(6) << numLines << endl;
	cout << left << setw(10) << "Words" << right << setw(6) << numWords << endl;
	cout << left << setw(10) << "Letters" << right << setw(6) << numLetters << endl;
	for (let = 'A'; let <= 'Z'; let++) {
		cout << left << setw(10) << let << right << setw(6) << letters[let - 65] << endl;
	}
}