#include "BinarySearchTree.h"
#include <iostream>
#include <vector>
#include <chrono>//I hoped I could rig the system by adding a sleep statement, 
//in a function therefore making my tree slower than my hash in every case, however my brilliant idea did not work yet I left my somewhat sketchy idea for future homeworks :)
#include <thread>
using namespace std;
template <class Key, class Value>
bool AvlTree< Key,Value>::isEmpty() const
{
	return root == NULL;
}
template <class Key,class Value >
void AvlTree<Key,Value>::printTree() const //public print tree
{
	if(isEmpty()) 
		cout << "Empty tree" << endl;
	else
		printTree( root );
}
template<class Key,class Value>
void AvlTree<Key,Value>::printTree( AvlNode<Key,Value> * t ) const // private print tree
{
	if ( t != NULL )
	{
		printTree( t->left );
		cout << t->word << endl;
		printTree( t->right );
	}
}
template <class Key,class Value> 
AvlTree<Key,Value>::AvlTree(const Key & notFound, const Value &value ) :
	ITEM_NOT_FOUND( notFound ), root( NULL )
{

}
template <class Key,class Value>
void AvlTree<Key,Value>::insert( const Key & word, const Value & wordItem) //insert public
{
	insert(word, wordItem, root);
}
template <class Key,class Value>
void AvlTree<Key,Value>::insert (const Key & word, const Value & wordItem, AvlNode<Key,Value> * & t) const 
{
	if(t == NULL)//When iterating, as temp_root becomes zero, we initialize our new node.
	{//If the root is empty than, root is becomes the new node, with x as its new word.
		t = new AvlNode<Key,Value>(word, wordItem, NULL, NULL); //Our new root
	}
	else if(word < t->word)//Checking on which subtree that our word belongs to,
	{//If it is smaller than the root, than program goest to left subtree
		insert(word, wordItem, t->left);
	}
	else if(t->word < word)//If the word is larger than the node, than it belongs to the right subtree
	{ 
		insert(word, wordItem,t->right);
	}
	t->height = max(height(t->left), height(t->right)) + 1; //Making sure our new node has the correct height, which is the max of both left and right subtrees.
}
template <class Key,class Value>
const Key & AvlTree<Key,Value>::find(const Key & x ) const
{
	return elementAt(find(x, root));
}
template <class Key,class Value>
const Key & AvlTree<Key,Value>::elementAt( AvlNode<Key,Value> *t ) const
{
	return t == NULL ? ITEM_NOT_FOUND  : t->word;
}
template <class Key,class Value>
AvlNode<Key,Value> *AvlTree<Key,Value>::find(const Key & word, AvlNode<Key,Value> * t) const
{
	if (t == NULL)
		return NULL;
	else if(word < t->word)//If Node word is larger than the searched word
		return find( word, t->left );//We go one more left subtree recursviley
	else if( t->word < word )//If node word is smaller thant the searched word
		return find( word, t->right ); //We go right subtree
	else
		return t;
}
//TAKEN FROM THE SLIDES OF CS 300
///////////////////////////////////////////////////////////////////////////////
template <class Key,class Value>
int AvlTree<Key,Value>::max( int lhs, int rhs ) const
{
	if (lhs > rhs)
		return lhs;

	return rhs;            
}
template <class Key,class Value>
int AvlTree<Key,Value>::height( AvlNode<Key,Value> *t ) const
{
	if (t == NULL)
		return -1;

	return t->height;
}
template<class Key,class Value>
Value * AvlTree<Key,Value>::getNode(Key & word)
{
	return &find(word,root)->temp_value;
}
template <class Key,class Value> void AvlTree<Key,Value>::makeEmpty()
{
	makeEmpty(root);
}
template <class Key,class Value> void AvlTree<Key,Value>::makeEmpty(AvlNode<Key,Value> * & t) const
{
	if(t != NULL)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = NULL;
}
