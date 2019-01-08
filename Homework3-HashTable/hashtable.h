//--------------------------------------//
//	   Atilla Alpay Nalcaci		//
//		   19510		//
//		19.11.2018		//
//	    CS300 - Homework 3		//
//    	  Hash Table Header File        //
//--------------------------------------//

/**
* All class definitions and functions provided below are gathered & edited from lecture slides of 2018/19 Fall term.
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

bool isPrime( const int & x );
int nextPrime( const int & y );

/**
* Function that checks if the acquired number is prime or not.
*/
bool isPrime( const int & x )
{
	int a;

	for( a = 2; a < x; a++ )
	{
		if( !( x % a ) ) { return false; }
	}
	
	return true;
}

/**
* Function that finds the next smallest prime number after the acquired number.
*/
int nextPrime( const int & y )
{
	int b = y;	

	while( !isPrime( b ) ) { b++; }
	return b;
}

class HashTable
{
	public:
		explicit HashTable( int size = 10000 );

		int find( const int & x ) const;		// Find (returns # of probes)
		
		void clear_Table( );
		int insert( const int & x ); // Insertion function (returns the number of probes).
		int remove( const int & x ); // Deletion function (	"	"	"	"	"	"	" ).

		enum EntryType {ACTIVE, EMPTY, DELETED};

		int size_CurrP( ) const; // Accessor for storing the current size.
		int size_TotalP( ) const; // Accessor for storing the total size.

	private:
		struct HashEntry
		{
			int element;
			EntryType info;

			HashEntry( const int & element = int( ), EntryType information = EMPTY )
				: element(element), info(information) {}
		};

		vector<HashEntry> array;
		int probe_Curr;
		int probe_Tot;

		bool isActive( int currentPos ) const;
		int findPos( const int & x, int & i ) const; // Find Position function which finds the position.
		int rehash( const int & x ) const; // The hashing function for the hash table.
};

/**
* Construct the hash table.
*/
HashTable::HashTable( int size ) : array( nextPrime(size) ), probe_Tot( nextPrime(size) )
{
	clear_Table();
}

/**
* Method that performs quadratic probing resolution.
* Return the position where the search for x terminates.
*/
int HashTable::findPos( const int & x, int & y ) const
{
	int currentPos = rehash( x );

	while( array[currentPos].info == ACTIVE && array[currentPos].element != x )
	{
		currentPos++;
		y++;

		if ( currentPos >= array.size() )
			currentPos -= array.size();
	}

	return currentPos; 
}

/**
* Return true if currentPos exists and is active.
*/
bool HashTable::isActive ( int currentPos ) const
{
	return array[currentPos].info == ACTIVE;
}

/**
* Remove item x from the hash table.
*  x has to be in the table
*/
int HashTable::remove( const int & x )
{
	int temp = 1;

	int currentPos = findPos( x, temp );
	if( !isActive( currentPos ) )
		return ( -1*temp );

	array[currentPos].info = DELETED;
	probe_Curr--;

	return temp;
}

/**
* Find item x in the hash table.
* Return the matching item, or ITEM_NOT_FOUND, if not found.
*/
int HashTable::find ( const int & x ) const
{
        int temp = 1;

        int currentPos = findPos( x, temp );
        if ( isActive(currentPos) )
                return temp;
		
		return ( -1*temp );
}

/**
* Insert item x into the hash table. If the item is
* already present, then do nothing.
*/
int HashTable::insert ( const int & x )
{
	int temp = 1;

	// Insert x as active.
	int currentPos = findPos( x, temp );

	if( isActive(currentPos) )
		return ( -1*temp );

	array[currentPos].element = x;
	array[currentPos].info = ACTIVE;
	probe_Curr++;

	return temp;
}

/**
* Accessor for current size.
*/
int HashTable::size_CurrP( ) const
{
	return (probe_Curr);
}

/**
* Accessor for total size.
*/
int HashTable::size_TotalP( ) const
{
	return (probe_Tot);
}

/**
* Hashing function, takes the modulo size of the acquired number.
*/
int HashTable::rehash( const int & x ) const
{
	return (x % probe_Tot);
}

/**
* Function for emptying the table.
*/
void HashTable::clear_Table( )
{
	probe_Curr = 0;
	for ( auto & entry : array )
		entry.info = EMPTY;
}

#endif
