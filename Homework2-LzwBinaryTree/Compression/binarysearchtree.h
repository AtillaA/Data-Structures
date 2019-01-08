//--------------------------------------//
//	   Atilla Alpay Nalcaci		//
//		   19510		//
//		19.11.2018		//
//	    CS300 - Homework 2		//
//    Binary Search Tree Header File    //
//--------------------------------------//

/**
* All class definitions and functions provided below are gathered & edited from lecture slides of 2018/19 Fall term.
*/

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <string>

using namespace std;

template<class T, class B>
struct BinaryNode 
{
	T lzw;
	B index;

	BinaryNode<T, B> *left;
	BinaryNode<T, B> *right;

	BinaryNode(const T & theElement, const B & theId, BinaryNode<T, B> *lt, BinaryNode<T, B> *rt)
		:lzw( theElement ), index( theId ), left( lt ), right( rt )
	{}
};

template<class T, class B>
class BinarySearchTree
{
	public:
		explicit BinarySearchTree( const B & notFound );
		~BinarySearchTree();
		const B & find ( const T & a ) const;
		BinaryNode<T, B> * findMin( BinaryNode<T, B> * t ) const;
		void makeEmpty();
		void insert( const T & a, const B & x );
		void remove( const T & a );

	private:
		BinaryNode<T, B> *root;		
		const B ITEM_NOT_FOUND;
		const B & elementAt( BinaryNode<T, B> *t ) const;
		void insert( const T & a, const B & x, BinaryNode<T, B> * & t ) const;
		void remove( const T & a, BinaryNode<T, B> * & t ) const;
		BinaryNode<T, B> * find( const T & a, BinaryNode<T, B> *t ) const;
		void makeEmpty( BinaryNode<T, B> * & t ) const;
};

/**
* Construct the tree.
*/
template<class T, class B>
BinarySearchTree<T, B>::BinarySearchTree( const B & notFound ) :
	ITEM_NOT_FOUND(notFound), root(NULL)
{}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template<class T, class B>
const B & BinarySearchTree<T, B>::elementAt ( BinaryNode<T, B> * t ) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->index;
}


/**
* Find item s in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template<class T, class B>
const B & BinarySearchTree<T, B>::find( const T & a ) const
{
	return elementAt( find(a, root) );
}

/**
* Internal method to find an item in a subtree.
* s is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template<class T, class B>
BinaryNode<T, B> * BinarySearchTree<T, B>::find( const T & a, BinaryNode<T, B> * t ) const
{
	if ( t == NULL )
		return NULL;
	else if ( a < t->lzw )
		return find( a, t->left );
	else if ( t->lzw < a )
		return find( a, t->right );
	else
		return t;    // Match
}

/**
* Internal method to find the minimum item in a subtree.
* t is the node that roots the tree.
*/
template<class T, class B>
BinaryNode<T, B> * BinarySearchTree<T, B>::findMin( BinaryNode<T, B> * t ) const
{
	while ( t->left != NULL )  // no left subtree
		t = t->left;
	if ( t == NULL )  // not found
		return NULL;
	return t;
}

/**
* Insert s and x into the tree; duplicates are ignored.
*/
template<class T, class B>
void BinarySearchTree<T, B>::insert(const T & a, const B & x)
{
	insert( a, x, root );
}

/**
* Internal method to insert into a subtree.
* s and x are the items to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template<class T, class B>
void BinarySearchTree<T, B>::insert(const T & a, const B & x, BinaryNode<T, B> * & t) const
{
	if ( t == NULL ) //  create a new node at the right place
		t = new BinaryNode<T, B>( a, x, NULL, NULL );	
	else if ( a < t->lzw )
		insert( a, x, t->left );  // insert at the left or
	else if ( t->lzw < a )
		insert( a, x, t->right );	 // right subtree
	else
		;  // Duplicate; do nothing
}

/**
* Remove s from the tree. Nothing is done if x is not found.
*/
template<class T, class B>
void BinarySearchTree<T, B>::remove( const T & a )
{
	remove( a, root );
}

/**
* Internal method to remove from a subtree.
* s is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template<class T, class B>
void BinarySearchTree<T, B>::remove( const T & a, BinaryNode<T, B> * & t ) const
{
	if ( t == NULL )
		return;   // Item not found; do nothing
	if ( a < t->lzw )
		remove( a, t->left );
	else if ( t->lzw < a )
		remove( a, t->right );
	else if ( t->left != NULL && t->right != NULL ) // Two children
	{
		t->lzw = findMin( t->right )->lzw;
		t->index = findMin( t->right )->index;
		remove( t->lzw, t->right );
	}
	else // one or no children
	{
		BinaryNode<T, B> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
}

/**
* Make the tree logically empty.
*/
template<class T, class B>
void BinarySearchTree<T, B>::makeEmpty( )
{
	makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template<class T, class B>
void BinarySearchTree<T, B>::makeEmpty( BinaryNode<T, B> * & t ) const
{
	if (t != NULL)
	{
		makeEmpty( t->left );
		makeEmpty( t->right );
		delete t;
	}
	
	t = NULL;
}

/**
* Destructor for the tree.
*/
template<class T, class B>
BinarySearchTree<T, B>::~BinarySearchTree( )
{
	makeEmpty( );
}

#endif
