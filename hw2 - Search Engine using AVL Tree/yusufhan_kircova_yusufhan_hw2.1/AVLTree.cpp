#include "AVLTree.h"
#include <iostream>
#include <vector>
using namespace std;

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
		if(height(t->left) - height(t->right) == 2) //If there is a 2 difference between subtrees, than we rebalance the tree
		{
			if (word < t->left->word)//Incase the newly added word is on left-left subtree
			{
				rotateWithLeftChild(t);
			}
			else//Incase the newly added word is on right-left subtree
			{
				doubleWithLeftChild(t);
			}
		}
	}
	else if(t->word < word)//If the word is larger than the node, than it belongs to the right subtree
	{ 
		insert(word, wordItem,t->right);
		if (height(t->right) - height(t->left) == 2)//We check for inbalances,
		{
			if (t->right->word < word)//Making the necessary balance operations.
			{
				rotateWithRightChild(t);
			}
			else
			{
				doubleWithRightChild(t);
			}
		}
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

template <class Key,class Value>
void AvlTree<Key,Value>::doubleWithRightChild
	( AvlNode<Key,Value> * & k1 ) const
{
	rotateWithLeftChild( k1->right );
	rotateWithRightChild( k1 );
}


template <class Key,class Value>
void AvlTree<Key,Value>::doubleWithLeftChild
	( AvlNode<Key,Value> * & k3 ) const
{
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}

template <class Key,class Value>
void AvlTree<Key,Value>::rotateWithRightChild
	( AvlNode<Key,Value> * & k1 ) const
{
	AvlNode<Key,Value> *k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	k1->height = max(height(k1->left), height(k1->right)) + 1;
	k2->height = max(height(k2->right), k1->height) + 1;
	k1 = k2;
}

template <class Key,class Value>
void AvlTree<Key,Value>::rotateWithLeftChild(AvlNode<Key,Value> * & k2) const
{
	AvlNode<Key,Value> *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left), k2->height) + 1;
	k2 = k1;
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
