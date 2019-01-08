//--------------------------------------//
//	   Atilla Alpay Nalcaci		//
//		   19510		//
//		19.11.2018		//
//	    CS300 - Homework 2		//
//		Compressor		//
//--------------------------------------//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "binarysearchtree.h"

using namespace std;

int main()
{
	int range = 256;
	int finalNum, temp;
	string inputName, inputLine, printLine, printCompressed, newPhrase, prevPhrase;
	char eachChar;

	ifstream inputFile, printFile, printBefore;
	ofstream outputFile;
	BinarySearchTree<string, int> dictionary(-1);

	/**
	* Open the file with the 'inputName' that is entered.
	*/
	cout << "Enter the name of the file which you would like to compress; ";
	cin >> inputName;
	inputFile.open(inputName);

	/**
	* If the file does not exist, ask for a new name until a valid entry occurs.
	*/
	while (inputFile.is_open() == false)
	{
		cin.clear();
		cout << "Unable to open file, please try again; ";
		cin >> inputName;
		inputFile.open(inputName);
	}

	cout << endl;
	outputFile.open("compout");  // Create an output file and name it as 'compout'.

	/**
	* Main loop that reads the file character by character.
	*/
	while (inputFile.get(eachChar))
	{
		if (static_cast<int>(eachChar) == 13) { continue; }			

		newPhrase.push_back(eachChar);				// Add the character 'each' to the string newPhrase in order to store.
		temp = dictionary.find(newPhrase);			// Find the 'newPhrase' in BST and equalize the local variable 'temp' to it.

		if (temp == -1 && newPhrase.length() > 1)		// If the 'newPhrase' is not in the 'dictionary',
		{
			dictionary.insert(newPhrase, range++);		// then add it to the 'dictionary'.

			if (prevPhrase.length() == 1) { finalNum = prevPhrase.at(0); } // Resolve a code for 'oldPhrase'.
			else { finalNum = dictionary.find(prevPhrase); }
				
			outputFile << finalNum << " ";				// Print the code of the first compression.
			newPhrase = eachChar;					// 'newPhrase' is now equal to the last character in the string.
		}

		prevPhrase = newPhrase;						// 'oldPhrase' is now equal to 'newPhrase'. 
	}

	/**
	* If the file have travelled through the main loop, for the last output.
	*/
	if (prevPhrase.length() == 1) { finalNum = prevPhrase.at(0); }
	else { finalNum = dictionary.find(prevPhrase); }
	
	outputFile << finalNum;

	/**
	* Clean up the tree and fstream variables.
	*/
	dictionary.makeEmpty();
	inputFile.close();
	outputFile.close();

	/**
	* Print the original file.
	*/
	cout << "Before compression: " << endl;
	printBefore.open(inputName);

	while (!printBefore.eof())
	{
		getline (printBefore, printLine);
		cout << printLine << "\n";
	}

	cout << endl;

	/**
	* Print the compressed file.
	*/
	cout << "After compression: " << endl;
	printFile.open("compout");

	while (!printFile.eof())
	{
		getline (printFile, printCompressed);
		cout << printCompressed << "\n";
	}

	/**
	* Close ifstreams.
	*/
	printBefore.close();
	printFile.close();

	cout << endl;
	cout << "Compressed and saved as 'compout'." << endl;
	cout << "\nExiting..." << endl;

	// *** You can find the compressed file under this projects repository. ***

	cin.ignore();
	cin.get();
	return 0;
}
