#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_
#include <vector>

template <class Key, class HashedObj>
class HashTable
{
public:
	explicit HashTable(const Key & word, const HashedObj & notFound, int size = 101);
	HashTable( const HashTable & rhs )
		: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
		array( rhs.array ), currentSize( rhs.currentSize ) { }

	int getSize();
	double getLoadFactor();//I use these functions to print size and loadfactor in main

	const HashedObj & find( const Key & word ) const;
	void makeEmpty();
	void insert(const Key & word, const HashedObj & x );
	void remove(const HashedObj & x );

	HashedObj * getHashNode(Key & element);//I use this function to update the count value on main

	const HashTable & operator=( const HashTable & rhs );
	enum EntryType { ACTIVE, EMPTY, DELETED};
private:
	struct HashEntry
	{
		Key word;
		HashedObj element;
		EntryType info;
		HashEntry(const Key & k = "-99999", const HashedObj & e = HashedObj(), EntryType i = EMPTY): word(k), element(e), info(i) { }
	};
	vector<HashEntry> array;
	int currentSize;
	const HashedObj ITEM_NOT_FOUND;

	bool isActive(int currentPos) const;
	int findPos(const Key & x) const;
	void rehash();
	int hash(const Key & word, int tableSize) const;
};

template<class Key,class HashedObj>
HashedObj * HashTable<Key,HashedObj>::getHashNode(Key & element)//Function is used to update values directly on hashtable via main
{
	int arrayIndex = findPos(element);
	return & array[arrayIndex].element;
}

bool isPrime(int n)
{
	if (n == 2 || n == 3)
		return true;
	if (n == 1 || n % 2 == 0)
		return false;
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

int nextPrime(int n)
{
	if(n % 2 == 0)
		n++;
	for( ; !isPrime(n); n += 2);
	return n;
}

template <class Key, class HashedObj>
int HashTable<Key, HashedObj>::getSize()
{
	return currentSize;
}

template <class Key, class HashedObj>
double HashTable<Key, HashedObj>::getLoadFactor()//Got this part from rehash function, returning load factor to be printed in main
{
	for (int i = 0; i < array.size(); i++ )
		if (array[i].info == ACTIVE)//If the element is active
			insert(array[i].word, array[i].element); //Inserting it as a hash table product
	double loadRatio = (double)currentSize/(double)array.size();//Calculating the loadratio
	return loadRatio;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////// /BELOW FUNCTIONS HAVE BEEN TAKEN FROM CS300 SLIDES/WITH MINOR EDITS ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Key, class HashedObj>
int HashTable<Key, HashedObj>::hash (const Key & word, int tableSize) const
{
	int sum = 0;
	for (int i = 0; i < word.length(); i++)
	{
		sum = sum + word[i];
	}
	return (sum % tableSize);
}

template <class Key, class HashedObj>
void HashTable<Key, HashedObj>::makeEmpty()
{
	for(int i = 0; i < array.size(); i++ )
		array[i].info = EMPTY;
	currentSize = 0;
}

template <class Key,class HashedObj>
HashTable<Key,HashedObj>::HashTable(const Key & word,const HashedObj & notFound, int size)
	: ITEM_NOT_FOUND(notFound), array(nextPrime(size))
{
	makeEmpty();
}

template <class Key,class HashedObj>
int HashTable<Key,HashedObj>::findPos( const Key & x ) const
{
	int collisionNum = 0;
	int currentPos = hash( x, array.size( ) );

	while ( array[ currentPos ].info != EMPTY && array[ currentPos ].word != x )
	{
		currentPos += 2 * ++collisionNum - 1;
		if ( currentPos >= array.size())
		{
			currentPos -= array.size();
		}
	}
	return currentPos;
}

template <class Key,class HashedObj>
bool HashTable<Key,HashedObj>::isActive( int currentPos ) const
{
	return array[ currentPos ].info == ACTIVE;
}

template <class Key,class HashedObj>
void HashTable<Key,HashedObj>::remove( const HashedObj & x )
{
	int currentPos = findPos( x );
	if ( isActive( currentPos ) )
		array[ currentPos ].info = DELETED;
}

template <class Key,class HashedObj>
const HashedObj & HashTable<Key,HashedObj>::find( const Key & word ) const
{
	int currentPos = findPos( word );
	if (isActive( currentPos )) 
		return array[currentPos].element; 

	return ITEM_NOT_FOUND;
}

template <class Key,class HashedObj>
void HashTable<Key,HashedObj>::insert(const Key & word, const HashedObj & x )
{
	int currentPos = findPos(word);
	if (isActive(currentPos))
		return;
	array[currentPos] = HashEntry(word,x,ACTIVE);

	if (++currentSize >= array.size() / 1.3)
		rehash();
}

template <class Key,class HashedObj>
void HashTable<Key, HashedObj>::rehash()
{
	cout << "rehashed..." << endl;
	cout << "previous table size: " << array.size();
	vector<HashEntry> oldArray = array;
	array.resize( nextPrime( 2 * oldArray.size( ) ) );
	for ( int j = 0; j < array.size( ); j++ )
	{
		array[j].word = "-99999";
		array[j].info = EMPTY;//Just changed this part since my worditem list can be empty and might be item not found.
		array[j].element = ITEM_NOT_FOUND;
	}
	currentSize = 0;
	for (int i = 0; i < oldArray.size( ); i++)
		if (oldArray[i].info == ACTIVE )
			insert( oldArray[ i ].word, oldArray[ i ].element );
	double loadRatio = (double)currentSize/(double)array.size();

	cout << ", new table size: " << array.size() << ", current unique word count " //Printing out values, used in rehash since it must be called every time rehash occurs
		<< currentSize << ", current load factor: "<< loadRatio <<endl ;
}
#endif