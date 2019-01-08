//------------------------------------------//
//			 Atilla Alpay Nalcaci			//
//				    19510					//
//				 19.12.2018					//
//			  CS300 - Homework 4			//
//------------------------------------------//

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <math.h>

#include "mpq.h"	// Include Modified Priority Queue header.

using namespace std;

void lowerCase(string &s);

int main ()
{
	/**
	* Welcome message.
	*/
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "--########---##----##----##----##---##---------########---##----##---########--" << endl;
	cout << "--##---------##--##-------##--##----##------------##------###---##---##--------" << endl;
	cout << "--########---####-----------##------##------------##------##-##-##---########--" << endl;
	cout << "--------##---##**##---------##------##------------##------##---###---##--------" << endl;
	cout << "--########---##----##-------##------########---########---##----##---########--" << endl;
	cout << "-------------------------------------------------------------------------------" << endl;

	cout << "\n------------------------------------------------------------------" << endl;
	cout << "--To exit the program, enter 'abort', 'exit' or 'x' as file name--" << endl;	
	cout << "------------------------------------------------------------------\n" << endl;

	bool loop = true;

	while (loop)
	{
		/**
		* Local Variables.
		*/
		ifstream inputFile;
		string fileName, check;
		int right, left, size, num, tag, height, last, id;
		int indexval = 1;
		int k = 0;
		int l = 0;
		
		/**
		* Open the file with the 'inputName' that is entered.
		*/
		cout << "Please enter a file name (with the extension): ";		
		cin >> fileName;

		check = fileName;
		lowerCase(check);

		/**
		* If the entered value is 'abort', exit the program.
		*/
		if ((check == "abort") || (check == "exit") || (check == "x"))
		{
			loop = false;
			break;
		}

		inputFile.open(fileName);

		/**
		* If the file does not exist, keep asking for a new name until a valid entry occurs.
		* Check for 'exit' conditions at each step. 
		*/
		while (inputFile.is_open() == false)
		{
			cout << "Unable to open file. Please try again; ";
			cin >> fileName;

			check = fileName;
			lowerCase(check);

			if ((check == "abort") || (check == "exit") || (check == "x"))
			{
				loop = false;
				break;
			}

			inputFile.open(fileName);
		}

		/**
		* If program aborted, break.
		*/
		if (loop == false)
		{
			break;
		}
	
		inputFile >> id;

		/**
		* If there are no buildings, terminate. 
		*/
		if (id == 0)
		{
			inputFile.close();
			cout << 0 << " " << 0 << endl;
			return 0;
		}

		size = ((id * 2) + 1);
		coord * bps = new coord[size];
		coord * bpfirst = new coord(0, 0, 0, true);

		bps[0] = *bpfirst;

		/**
		* Taking the inputs from the file and inserting into the array. 
		*/
		for (k = 0; k < id; k++)
		{
			/**
			* Extracting coordinates and height of the skyscraper. 
			*/
			tag = indexval;
			inputFile >> left >> num >> right;

			bpfirst = new coord(right, tag, num, false);
			bps[indexval + 1] = *bpfirst;

			bpfirst = new coord(left, tag, num, true);
			bps[indexval] = *bpfirst;

			indexval++;
			indexval++;
		}

		/**
		* Sort the array with respect to start and end coordinates. 
		*/
		sort(bps, (bps + size));

		MPQ myheap(size);

		cout << "-----\n";

		/**
		* Main loop for printing the building values.
		*/
		for (l = 0; l < size; l++)
		{
			if (bps[l].begin)
			{
				height = bps[l].point;
				last = myheap.maximum();
				myheap.insertion(height, bps[l].tag);

				/**
				* Output the building if the maximum value has changed.
				*/
				if (last != myheap.maximum()) { cout << bps[l].var << " " << height << "\n"; }
			}

			else 
			{
				last = myheap.maximum();
				height = bps[l].point;
				myheap.Remove(bps[l].tag);

				/**
				* Output the building if the maximum value has changed.
				*/
				if (myheap.maximum() != last) {  cout << bps[l].var << " " << myheap.maximum() << "\n"; }
			}
		}
		
		/**
		* Close input stream and loop.
		*/
		inputFile.close();

		cout << "-----";
		cout << endl;
	}

	cout << "\nExiting..." << endl;

	cin.ignore();
	cin.get();
	return 0;
}

/**
* Function that converts the given string to lowercase.
*/
void lowerCase(string &s) 
{
	int i = 0;

	for (i = 0; i < s.length(); i++)
	{
		if ((s[i] >= 'A') && (s[i] <= 'Z'))
		{
			s[i] = (s[i] + 32);
		}
	}
}
