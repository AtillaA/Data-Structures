//--------------------------------------//
//	   Atilla Alpay Nalcaci		//
//		   19510		//
//		5.12.2018		//
//	    CS300 - Homework 3		//
//--------------------------------------//

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include "hashtable.h"

using namespace std;

/**
* Structure for arrays that store the total number of probes and transactions.
*/
struct initialize
{
	double curr_prb;
	int trans_no;
};

int type_Def(const int & foo, const int & selection);
void create_Files(double** fail_ins_arr, double** succ_ins_arr, double** fail_del_arr, double** succ_del_arr, double** fail_find_arr, double** succ_find_arr, int totalSize);

/**
* To define different types of ratios, which are 6:1:1, 4:2:2 and 2:1:5.
*/
int type_Def(const int & selection, const int & temp)
{       
	/**
	* Ratio (6:1:1)
	*/
    if (selection == 1)
    {       
		if (temp <= 5) { return 1; }
		else if (temp <= 6)	{ return 2; }
		else { return 3; }
    }

	/**
	* Ratio (2:1:5)
	*/
	else if (selection == 3)
	{       
		if (temp <= 1) { return 1; }
		else if (temp <= 2) { return 2; }
		else { return 3; }
    }

	/**
	* Ratio (4:2:2)
	*/
    else if (selection == 2)
    {       
		if (temp <= 3) { return 1; }
		else if (temp <= 5) { return 2; }
		else { return 3; }
    }

	/**
	* Error case.
	*/
    else
	{
		cout << "This should not have happened. Check the type definition function!" << endl;
		return 0;
	}
}

/**
* Creates the .csv files for insertion/deletion/location operations under the repository.
*/
void create_Files(double** fail_ins_print, double** succ_ins_print, double** fail_del_print, double** succ_del_print, double** fail_find_print, double** succ_find_print, int finalSize)
{
	int z = 0;
	double row;
	ofstream fail_ins, succ_ins, fail_del, succ_del, fail_find, succ_find;

	/**
	* Create empty files for each operation.
	*/
	succ_ins.open("insertion_success.csv");
	succ_ins << fixed;

	succ_del.open("deletion_success.csv");
	succ_del << fixed;

	succ_find.open("find_success.csv");
	succ_find << fixed;

	fail_del.open("deletion_fail.csv");
	fail_del << fixed;

	fail_find.open("find_fail.csv");
	fail_find << fixed;

	fail_ins.open("insertion_fail.csv");
	fail_ins << fixed;
	
	/**
	* File creation loop.
	* Creates files from ofstream objects in .csv format.
	*/
	for (z = 0; z <= finalSize; z++)
	{
		row = (double) z / finalSize;
		/**
		* Arrays are seperated with comma since semi-column did not work in Excel 2013.
		*/
		fail_ins << row << "," << (fail_ins_print[1][z]) << "," << (fail_ins_print[2][z]) << "," << (fail_ins_print[3][z]) << endl;

		succ_ins << row << "," << (succ_ins_print[1][z]) << "," << (succ_ins_print[2][z]) << "," << (succ_ins_print[3][z]) << endl;

		fail_del << row << "," << (fail_del_print[1][z]) << "," << (fail_del_print[2][z]) << "," << (fail_del_print[3][z]) << endl;

		succ_del << row << "," << (succ_del_print[1][z]) << "," << (succ_del_print[2][z]) << "," << (succ_del_print[3][z]) << endl;

		fail_find << row << "," << (fail_find_print[1][z]) << "," << (fail_find_print[2][z]) << "," << (fail_find_print[3][z]) << endl;

		succ_find << row << "," << (succ_find_print[1][z]) << "," << (succ_find_print[2][z]) << "," << (succ_find_print[3][z]) << endl;
	}

	fail_ins.close();
	succ_ins.close();
	fail_del.close();
	succ_del.close();
	fail_find.close();
	succ_find.close();

	cout << "Files have been created." << endl;
}

int main()
{
	/**
	* Hash table creation.
	*/
	HashTable theTable;
	int tableSize = theTable.size_TotalP();

    double** ins_fail_array = new double* [4];
	double** ins_succ_array = new double* [4];
	double** del_fail_array = new double* [4];
	double** del_succ_array = new double* [4];
	double** find_fail_array = new double* [4];
	double** find_succ_array = new double* [4];

	/**
	* Loop variable creation.
	*/
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	int n = 0;

	int x = 0;
	int y = 0;

	cout << "In progress..." << endl;

	
	/**
	* To keep 6 tables of M+1 entries.
	* One for each combination of the type of transaction and outcome.
	*/
	for(i = 1; i <= 3; i++) { ins_fail_array[i] = new double [tableSize + 1]; }
	for(j = 1; j <= 3; j++) { ins_succ_array[j] = new double [tableSize + 1]; }
	for(k = 1; k <= 3; k++) { del_fail_array[k] = new double [tableSize + 1]; }
	for(l = 1; l <= 3; l++) { del_succ_array[l] = new double [tableSize + 1]; }
	for(m = 1; m <= 3; m++) { find_fail_array[m] = new double [tableSize + 1]; }
	for(n = 1; n <= 3; n++) { find_succ_array[n] = new double [tableSize + 1]; }

	for(int x = 1; x <= 3; x++)
	{
		/**
		* Variable creation.
		*/
		int temp, cast, size, random, foo;
		int T_amount = 0;

		/**
		* Array creation for each operation.
		*/
		initialize* ins_fail_entry = new initialize [tableSize + 1];
		initialize* ins_succ_entry = new initialize [tableSize + 1];
		initialize* del_fail_entry = new initialize [tableSize + 1];
		initialize* del_succ_entry = new initialize [tableSize + 1];
		initialize* find_fail_entry = new initialize [tableSize + 1];
		initialize* find_succ_entry = new initialize [tableSize + 1];

		/**
		* Clear table after each operation batch.
		*/
		theTable.clear_Table();
		srand(1);

		/**
		* Main loop for insertion/deletion/find of values.
		* Insertion => 1 | Deletion => 2 | Find => 3
		* Returns a negative value if fails the operation.
		*/
		while ((theTable.size_CurrP() < tableSize) && (T_amount++ < 1000000)) // Loop will travel until table is full or 1M transactions had been made.
		{
			random = rand() % 100000; // Random number generator.
			foo = rand() % 8; // Random operation generator.

			cast = type_Def(x, foo);
			size = theTable.size_CurrP();

			/**
			* Deletion condition.
			*/
			if(cast == 2)
			{
				temp = theTable.remove(random);
				
				/**
				* Unsuccessful deletion.
				*/
				if (temp < 0)
                {
					del_fail_entry[size].curr_prb = ((del_fail_entry[size].curr_prb) - temp);
					del_fail_entry[size].trans_no = ((del_fail_entry[size].trans_no) + 1);
                }
                
				/**
				* Successful deletion.
				*/
				else if (temp > 0)
                {
					del_succ_entry[size].curr_prb = ((del_succ_entry[size].curr_prb) + temp);
					del_succ_entry[size].trans_no = ((del_succ_entry[size].trans_no) + 1);
                }
                
				/**
				* Error case (deletion).
				*/
				else { cout << "This should not have happened. Check the deletion!" << endl; }
			}

			/**
			* Insertion condition.
			*/
			else if (cast == 1)
			{
				temp = theTable.insert(random);

				/**
				* Unsuccessful insertion.
				*/
				if (temp < 0)
				{
					ins_fail_entry[size].curr_prb = ((ins_fail_entry[size].curr_prb) - temp);
					ins_fail_entry[size].trans_no = ((ins_fail_entry[size].trans_no) + 1);
				}

				/**
				* Successful insertion.
				*/
				else if	(temp > 0)
				{
					ins_succ_entry[size].curr_prb = ((ins_succ_entry[size].curr_prb) + temp);
					ins_succ_entry[size].trans_no = ((ins_succ_entry[size].trans_no) + 1);
				}

				/**
				* Error case (insertion).
				*/
				else { cout << "This should not have happened. Check the insertion!" << endl; }
			}

			/**
			* Location (find) condition.
			*/
			else if	(cast == 3)
			{
				temp = theTable.find(random);
				
				/**
				* Successful location (find).
				*/
				if (temp > 0)
				{
					find_succ_entry[size].curr_prb = ((find_succ_entry[size].curr_prb) + temp);
                    find_succ_entry[size].trans_no = ((find_succ_entry[size].trans_no) + 1);
                }

				/**
				* Unsuccessful location.
				*/
                else if (temp < 0)
                {
					find_fail_entry[size].curr_prb = ((find_fail_entry[size].curr_prb) - temp);
                    find_fail_entry[size].trans_no = ((find_fail_entry[size].trans_no) + 1);
				}
				
				/**
				* Error case (location).
				*/
				else { cout << "This should not have happened. Check the find!" << endl; }
			}

			/**
			* Error case (Fatal).
			*/
			else { cout << "Main condition has failed. Check the code!" << endl; }
		}

		/**
		* Loop for getting the average values for each load factor.
		*/
		for (y = 0; y < tableSize+1; y++)
		{
			/**
			* For successful location.
			*/
			if (find_succ_entry[y].trans_no != 0) { find_succ_array[x][y] = (find_succ_entry[y].curr_prb / find_succ_entry[y].trans_no); }

			/**
			* For successful insertion.
			*/
			if (ins_succ_entry[y].trans_no != 0) { ins_succ_array[x][y] = (ins_succ_entry[y].curr_prb / ins_succ_entry[y].trans_no); }

			/**
			* For successful deletion.
			*/
			if (del_succ_entry[y].trans_no != 0) { del_succ_array[x][y] = (del_succ_entry[y].curr_prb / del_succ_entry[y].trans_no); }

			/**
			* For unsuccessful location.
			*/
			if (find_fail_entry[y].trans_no != 0) { find_fail_array[x][y] = (find_fail_entry[y].curr_prb / find_fail_entry[y].trans_no); }

			/**
			* For unsuccessful insertion.
			*/
			if (ins_fail_entry[y].trans_no != 0) { ins_fail_array[x][y] = (ins_fail_entry[y].curr_prb / ins_fail_entry[y].trans_no); }

			/**
			* For unsuccessful deletion.
			*/
			if (del_fail_entry[y].trans_no != 0) { del_fail_array[x][y] = (del_fail_entry[y].curr_prb / del_fail_entry[y].trans_no); }
		}
	}

	cout << "All operations have succesfully been carried out." << endl;
	cout << "Creating files." << endl;

	/**
	* Create files by sending the corresponding arrays to void function.
	*/
	create_Files(ins_fail_array, ins_succ_array, del_fail_array, del_succ_array, find_fail_array, find_succ_array, tableSize);

	cout << "Completed!" << endl;
	cout << "Exiting..." << endl;

	cin.ignore();
	cin.get();
	return 0;
}
