#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
#include <iostream>
using namespace std;

template <class Object>
class List;     // Incomplete declaration.

template <class Object>
class ListItr;     // Incomplete declaration.

template <class Object>
class ListNode
{
	ListNode( const Object & theElement = Object( ), ListNode * n = NULL )
		: element( theElement ), next( n ) { }  // Constructor 

	Object   element;
	ListNode *next;

	friend class List<Object>;
	friend class ListItr<Object>;

};

template <class Object>
class ListItr
{
public:
	ListItr( ) : current( NULL ) { }
	bool isPastEnd( ) const
	{   return current == NULL;   }
	void advance( )
	{   if ( ! isPastEnd( ) )   current = current->next;   }
	const Object & retrieve( ) const
	{   if ( isPastEnd( ) )    throw BadIterator( );
	return current->element;    }

private:
	ListNode<Object> *current;    // Current position

	ListItr( ListNode<Object> *theNode )
		: current( theNode ) { }

	friend class List<Object>;    // Grant access to constructor
};

template <class Object>
class List
{
public:
	List( );
	List( const List & rhs );
	~List( );
	bool isEmpty( ) const;
	void makeEmpty( );
	ListItr<Object> zeroth( ) const;
	ListItr<Object> first( ) const;
	void insert( const Object & x, const ListItr<Object> & p );
	ListItr<Object> find( const Object & x ) const;
	ListItr<Object> findPrevious( const Object & x ) const;
	void remove( const Object & x );

	const List & operator=( const List & rhs );

private:
	ListNode<Object> *header;
};


#endif