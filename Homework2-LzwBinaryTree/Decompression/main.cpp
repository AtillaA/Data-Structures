//------------------------------------------//
//			Atilla Alpay Nalcaci			//
//				   19510					//
//				19.11.2018					//
//			CS300 - Homework 2				//
//				Decompressor				//
//------------------------------------------//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/**
* 'dictionaryNode' struct for decompiler.
*/
struct dictionaryNode
{
	string reverse;
	int index;
};

int main()
{
	int next, old, text, k;
	string inputName, printLine, printDecompressed;

	ifstream inputFile, printFile, printBefore;
	ofstream outputFile;
	dictionaryNode dictionary[4096];
	
	k = 0;
	next = 256;

	/**
	* Open the file with the 'inputName' that is entered.
	*/
	cout << "Enter the name of the file that you would like to decompress; ";
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
	outputFile.open("decompout");  // Create an output file and name it as 'decompout'.

	/**
	* Add all the elements to our dictionary.
	*/
	for (k = 0; k < 256; k++)
	{
		dictionary[k].reverse = k;
		dictionary[k].index = 1;
	}

	/**
	* Executed only for first code.
	*/
	inputFile >> text;
	outputFile << dictionary[text].reverse;

	/**
	* Executed for the rest.
	*/
	old = text;

	/**
	* Main loop for parsing the elements in order.
	*/
	while (inputFile >> text)
	{
		/**
		* If 'code' is in dictionary.
		*/
		if(dictionary[text].index)
		{
			outputFile << dictionary[text].reverse;
			dictionary[next].index = 1;
			dictionary[next].reverse = dictionary[old].reverse + dictionary[text].reverse.at(0);
			next++;
		}

		/**
		* If 'code' is not in dictionary.
		*/
		else
		{
			dictionary[next].index = 1;
			dictionary[next].reverse = dictionary[old].reverse + dictionary[old].reverse.at(0);
			next++;
			outputFile << dictionary[old].reverse + dictionary[old].reverse.at(0);
		}

		old = text;
	}

	/**
	* Clean up the tree and fstream variables.
	*/
	inputFile.close();
	outputFile.close();

	/**
	* Print the original file.
	*/
	cout << "Before decompression: " << endl;
	printBefore.open(inputName);

	while(!printBefore.eof())
	{
		getline (printBefore, printLine);
		cout << printLine << "\n";
	}

	/**
	* Print the decompressed file.
	*/
	cout << endl;
	cout << "After decompression: " << endl;
	printFile.open("decompout");

	while(!printFile.eof())
	{
		getline(printFile, printDecompressed);
		cout << printDecompressed << "\n";
	}

	/**
	* Close ifstreams.
	*/
	printBefore.close();
	printFile.close();

	cout << endl;
	cout << "Decompressed and saved as 'decompout'." << endl;
	cout << "\nExiting..." << endl;

	// *** You can find the decompressed file under this projects repository. ***
	
	cin.ignore();
	cin.get();
	return 0;
}