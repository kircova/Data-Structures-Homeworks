#ifndef AVLTREE_H_
#define AVLTREE_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class Key, class Value>
class AvlTree;
//Key word(string), value * worditem
template <class Key, class Value>
class AvlNode
{
	Key word;
	Value temp_value;
	AvlNode * left;
	AvlNode * right;
	int height;

	AvlNode(const Key & key, const Value & wordItem, AvlNode *lt, AvlNode *rt, int h = 0)
		: word(key),temp_value(wordItem), left(lt), right(rt), height(h) { }

	friend AvlTree<Key,Value>;
};

template <class Key, class Value>
class AvlTree
{
public:
	explicit AvlTree(const Key & notFound, const Value & value); 
	//~AvlTree( );

	const Key & find( const Key & x ) const;

	void makeEmpty();


	void insert(const Key & x, const Value & el);
	Value * getNode(Key & element); 

private:
	AvlNode<Key,Value> *root;
	const Key ITEM_NOT_FOUND;

	const Key & elementAt(AvlNode<Key,Value> *t) const;

	void insert(const Key & x, const Value &theval ,AvlNode<Key,Value> * & t) const;
	AvlNode<Key,Value> * find(const Key & x, AvlNode<Key,Value> *t ) const;

	void makeEmpty(AvlNode<Key,Value> * & t) const;

	int height(AvlNode<Key,Value> *t ) const;
	int max(int lhs, int rhs) const;

	void rotateWithLeftChild( AvlNode<Key,Value> * & k2 ) const;
	void rotateWithRightChild( AvlNode<Key,Value> * & k1 ) const;
	void doubleWithLeftChild( AvlNode<Key,Value> * & k3 ) const;
	void doubleWithRightChild( AvlNode<Key,Value> * & k1 ) const;
};


#endif