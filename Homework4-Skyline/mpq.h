//--------------------------------------//
//	   Atilla Alpay Nalcaci		//
//		   19510		//
//		19.12.2018		//
//	    CS300 - Homework 2		//
//  Modified Priority Queue Header File //
//--------------------------------------//

/**
* All class definitions and functions provided below are gathered & edited from lecture slides of 2018/19 Fall term.
*/

#ifndef MPQ_H
#define MPQ_H

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

using namespace std;

/**
* Structure for the elements of modified priority queue.
*/
struct element
{
	int tag;
	int num;

	element ()
	{ }

	element ( int num, int tag ) : num( num ), tag( tag )
	{ }
};

/**
* Structure for arrays that stores the coordinates.
*/
struct coord
{
	int tag;
	int var;
	int point;

	bool begin;

	coord( )
	{ }

	coord( int direction, int tag, int val, bool initiate ) : var( direction ), tag( tag ), point( val ), begin( initiate )
	{ }
};

/**
* Modified Priority Queue Class.
*/
class MPQ
{
	public:
		/**
		* Default constructor.
		*/
		MPQ( const int size ) : mpq( new element[size] ), loc( new int[ size ] ), size( size ), curr( 0 )
		{ }

		/**
		* Destructor.
		*/
		~MPQ ( ) 
		{ delete [ ] loc; }

		void insertion( int point, int tag );
		int Remove( int tag );
		void percolateDown( int val );
		int maximum( );
		bool check( ); 

	protected:
		// None.

	private:

		int * loc;
		int tmp;
		int curr;

		element * mpq;
		const int size;
};

/**
* Extracts the maximum value from the function.
* Returns the maximum value if there exists any.
* Returns 0 otherwise.
*/
int MPQ::maximum( )
{
	if ( !check( ) )
	{ 
		return mpq[ 1 ].num;
	}

	else 
	{ 
		return -1;
	}
}

/**
* Checks if the heap is empty.
* Returns the initialization of current size to zero.
*/
bool MPQ::check( ) 
{ 
	return ( curr == 0 );
}

/**
* Function that removes the element with tag and returns its value.
* Returns zero if no such element exists or if the heap is empty.
* Otherwise, it swaps the element with tag with the last element of the heap.
* Updates the location of descendant.
*/
int MPQ::Remove( int tag )
{
	int tagloc = loc[ tag ];
	int tmp = mpq[ tagloc ].num;

	if ( check( ) || !( loc[ tag ] ) )
	{
		return 0;
	}

	mpq[ tagloc ] = mpq[ curr-- ];
	loc[ mpq[ curr + 1 ].tag ] = tagloc;
    percolateDown( tagloc );
	tmp = mpq[ 1 ].num;							// 'tmp' stores the maximum value.

	return tmp;
}

/**
* Function that perlocates down the modified heap.
* In main loop, it perlocates the hole by comparing left and right descendants.
* After comparison, it either perlocates (if necessary) or skips.
*/
void MPQ::percolateDown( int val )
{
	int descendant;
	int tmp = mpq[ val ].num;
	int tmptag = mpq[ val ].tag;

	do
	{
		descendant = ( val * 2 );

		if( ( descendant != curr ) && ( mpq[ descendant + 1 ].num > mpq[ descendant ].num ) )
		{ 
			descendant++;
		}	
			
		else if( mpq[ descendant ].num > tmp )
		{ 
			mpq[ val ] = mpq[ descendant ];
			loc[ mpq[ descendant ].tag ] = val;
		}

		else
		{ 
			break;
		}

		val = descendant;
	} while( ( val * 2 ) <= curr );

	mpq[ val ].tag =  tmptag;					// After each operation, update the values accordingly.
	loc[ tmptag ] = val;
	mpq[ val ].num = tmp;
}

/**
* Function that inserts the current element into the modified priority queue.
* Creates a hole value and starts perlocation, updates the location variable after each perlocate.
* After execution, sets the hole values appropriately and updates the location.
*/
void MPQ::insertion( int t, int tag )
{
	curr++;

	int newval = curr;							// Integer that holds the current hole value.

	while ( ( t > mpq[ newval / 2 ].num) && ( newval > 1 ) )
	{ 
		mpq[ newval ] = mpq[ newval / 2 ];
		loc[ mpq[ newval / 2 ].tag ] = newval;
		newval /= 2;
	}

	mpq[ newval ].num = t;						// After each operation, update the values accordingly.
	mpq[ newval ].tag = tag;
	loc[ tag ] = newval;

}

/**
* Operator function for comparing the start/end points of the skyscrapers.
*/
bool operator<( const coord & left, const coord & right ) 
{
	if ( left.var < right.var )
	{ 
		return true;
	}

	else if ( left.var == right.var )
	{	
		/**
		* Condition for putting the taller building before the shorter one (for comparing their start points).
		*/
		if ( ( right.begin ) && ( left.begin ) )
		{ 
			return ( right.point < left.point );
		}

		/**
		* Condition for putting the shorter building before the taller one (for comparing their end points).
		*/
		else if ( !( right.begin ) && !( left.begin ) )
		{ 
			return ( right.point > left.point );
		}
		
		/**
		* Condition for comparing the start and end points of two buildings.
		* Places the building with start point before the one with the end point.
		*/
		else
		{
			return ( left.begin );
		}
	}

	/**
	* Return false if the left hand side is taller than the right.
	*/
	else
	{
		return false;
	}
}

#endif
