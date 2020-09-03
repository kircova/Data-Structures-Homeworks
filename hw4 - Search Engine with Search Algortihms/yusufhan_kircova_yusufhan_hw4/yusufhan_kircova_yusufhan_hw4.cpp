#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <istream>
#include <sstream>
#include <algorithm>
#include <ctime>
using namespace std;

struct DocumentItem
{
	string fileName;
	int count;
};

struct WordItem
{
	string word;
	vector<DocumentItem> DocumentList;
	bool operator<(WordItem & rhs)
	{
		if(word < rhs.word)
			return true;
		return false;
	}

	bool operator<=(WordItem & rhs)
	{
		if(word <= rhs.word)
			return true;
		return false;
	}

	bool operator>(WordItem & rhs)
	{
		if(word > rhs.word)
			return true;
		return false;
	} 
	bool operator>=(WordItem & rhs)
	{
		if(word >= rhs.word)
			return true;
		return false;
	} 

	bool operator==(WordItem & rhs)
	{
		if(word == rhs.word)
			return true;
		return false;
	} 
};

template <class Comperable>
int binarySearch(vector<Comperable> & vec, int l, int r, Comperable worditem) 
{ 
	if (r >= l) 
	{ 
		int mid = l + (r - l) / 2; 
		if (vec[mid] == worditem) 
			return mid; 
		if (vec[mid] > worditem) 
			return binarySearch(vec, l, mid - 1, worditem); 
		return binarySearch(vec, mid + 1, r, worditem); 
	} 
	return -1; 
}

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
	int j;
	for (int p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];
		for (j = p; j > 0 && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

inline int leftChild( int i )
{
	return 2*i+1;
}

template <class Comparable>
void heapsort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());
	// sort
	for (int j = a.size() -1; j >0; j--)
	{
		swap(a[0], a[j]); // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}

template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
	int child;
	Comparable tmp;
	for (tmp=a[i] ; leftChild(i) < n; i = child )
	{
		child = leftChild(i);
		if ( child != n-1 && a[ child ] < a[ child+1 ] )
			child++;
		if ( a[child ] > tmp )
			a[i] = a[ child ];
		else
			break;
	}
	a[ i ] = tmp;
}

template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
	vector<Comparable> tmpArray( a.size( ) );
	mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

template <class Comparable>
void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right )
{
	if ( left < right )
	{
		int center = ( left + right ) / 2;
		mergeSort( a, tmpArray, left, center );
		mergeSort( a, tmpArray, center + 1, right );
		merge( a, tmpArray, left, center + 1, right );
	}
}

template <class Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd )
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	// Main loop
	while ( leftPos <= leftEnd && rightPos <= rightEnd )
		if ( a[ leftPos ] <= a[ rightPos ] )
			tmpArray[ tmpPos++ ] = a[ leftPos++ ];
		else
			tmpArray[ tmpPos++ ] = a[ rightPos++ ];
	while ( leftPos <= leftEnd ) // Copy rest of first half
		tmpArray[ tmpPos++ ] = a[ leftPos++ ];
	while ( rightPos <= rightEnd ) // Copy rest of right half
		tmpArray[ tmpPos++ ] = a[ rightPos++ ];
	// Copy tmpArray back
	for ( int i = 0; i < numElements; i++, rightEnd-- )
		a[ rightEnd ] = tmpArray[ rightEnd ];
}

template <class Comparable>
void quicksort( vector<Comparable> & a)
{
	quicksort( a, 0, a.size( ) - 1);
}

template <class Comparable>
const Comparable & median3( vector<Comparable> & a,  int left, int right )
{
	int center = ( left + right ) / 2;
	if ( a[ center ] < a[ left ] )
		swap( a[ left ], a[ center ] );
	if ( a[ right ] < a[ left ] )
		swap( a[ left ], a[ right ] );
	if ( a[ right ] < a[ center ] )
		swap( a[ center ], a[ right ] );
	// Place pivot at position right - 1
	swap( a[ center ], a[ right - 1 ] );
	return a[ right - 1 ];
}

template <class Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
	for ( int p = left + 1; p <= right; p++ )
	{
		Comparable tmp = a[ p ];
		int j;
		for ( j = p; j > left && tmp < a[ j - 1 ]; j-- )
			a[ j ] = a[ j - 1 ];
		a[ j ] = tmp;
	}
}
template <class Comparable>
void quicksort(vector<Comparable>& a, int left, int right, int pivot)//For pivot version
{
	if (left + 10 <= right)
	{
		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i].word < a[pivot].word) {}

			while (a[pivot].word < a[--j].word) {}

			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}
		swap(a[i], a[right - 1]);   // Restore pivot
		quicksort(a, left, i - 1);       // Sort small elements
		quicksort(a, i + 1, right);    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}

template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right)
{
	if ( left + 10 <= right )
	{
		Comparable pivot = median3( a, left, right );
		int i = left, j = right - 1;
		for ( ; ; )
		{
			while ( a[ ++i ] < pivot ) { }

			while ( pivot < a[ --j ] ) { }

			if ( i < j )
				swap( a[ i ], a[ j ] );
			else
				break;

		}
		swap( a[ i ], a[ right - 1 ]); // Restore pivot
		quicksort( a, left, i - 1); // Sort small elements
		quicksort( a, i + 1, right); // Sort large elements
	}
	else // Do an insertion sort on the subarray

		insertionSort( a, left, right);
}

bool IsAlphabetic(char x)//Checks if the char is a lower case letter
{
	if(97 <= x && x <= 122)
	{
		return true;
	}
	return false;
}

bool IsAlphabeticWord(string word)//Checks if string is a lowercase word
{
	bool IsAlhabe = true;
	for (int i = 0; i < word.length(); i++)
	{
		if(!IsAlphabetic(word[i]))
		{
			return false;
		}
	}
	return IsAlhabe;
}

string ToLower(string word)//Converts a word into a lowercase word
{
	string newWord = "";
	for (int i = 0; i < word.length(); i++)
	{
		if(65 <= word[i] && word[i] <= 90)
			newWord += (word[i] + 32);
		else
			newWord += word[i];
	}
	return newWord;
}

int GetVectorElementIndex(vector<WordItem> xd, string word)
{
	int index = -1;//If not found
	for (int i = 0; i < xd.size(); i++)
	{
		if(xd[i].word == word)
		{
			index = i;
			return index;
		}
	}
	return index;
}
void CheckDocumentList(WordItem * x, string fileName)
{
	bool FileExists = false;
	for (int i = 0; i < x->DocumentList.size(); i++)
	{
		if(x->DocumentList[i].fileName == fileName)//Increases the count of Documentlist if the found filename matches with filename
		{
			x->DocumentList[i].count ++;
			FileExists = true;
		}
	}
	if(FileExists == false) //If file does not exist than program intializes count to 1
	{
		DocumentItem temp_Doc;
		temp_Doc.count = 1;
		temp_Doc.fileName = fileName;
		x->DocumentList.push_back(temp_Doc);
	}
}

void CheckDocumentHashTable(WordItem * x, string fileName)
{
	bool FileExists = false;
	for (int i = 0; i < x->DocumentList.size(); i++)
	{
		if(x->DocumentList[i].fileName == fileName)//Increases the count of Documentlist if the found filename matches with filename
		{
			x->DocumentList[i].count ++;
			FileExists = true;
		}
	}
	if(FileExists == false) //If file does not exist than program intializes count to 1
	{
		DocumentItem temp_Doc;
		temp_Doc.count = 1;
		temp_Doc.fileName = fileName;
		x->DocumentList.push_back(temp_Doc);
	}
}

int main()
{
	int numberOfFiles;
	cout << "Enter number of input files: ";
	cin >> numberOfFiles;
	vector<string> fileNames;

	for (int i = 0; i < numberOfFiles; i++)
	{
		string fileName;
		cout << "Enter " << i + 1 << ". file name:";
		cin >> fileName;
		fileNames.push_back(fileName);
	}

	string tempString = "-99999";
	WordItem ITEM_NOT_FOUND; ITEM_NOT_FOUND.word = "-99999";

	AvlTree<string,WordItem>myTree(tempString, ITEM_NOT_FOUND);
	HashTable<string,WordItem>myHashTable(tempString,ITEM_NOT_FOUND);
	vector<WordItem> myVector;

	for (int i = 0; i < numberOfFiles; i++)
	{
		ifstream file;
		file.open(fileNames[i].c_str());
		if(file.fail())
		{
			cout << "Fail can not be opened."<< endl;
		}
		else
		{
			string line;
			while (getline(file,line))
			{
				line = ToLower(line);
				for (int j = 0; j < line.length(); j++)
				{
					if(!IsAlphabetic(line[j]))
					{
						replace(line.begin(), line.end(), line[j],' ');
					}
				}
				string word;
				istringstream iss(line);
				while(iss >> word)
				{

					if(myTree.find(word) == "-99999")//If my word is not found in my tree, program inserts a new node into the necessary place
					{
						WordItem temp_WordItem; 
						temp_WordItem.word = word;
						DocumentItem temp_DocumentItem;
						temp_DocumentItem.count = 1; temp_DocumentItem.fileName = fileNames[i];
						temp_WordItem.DocumentList.push_back(temp_DocumentItem);
						myTree.insert(word, temp_WordItem);
					}
					else//Else we just increase count of document item or set a new document item using the CheckDocument Function
					{
						WordItem * current_WordItem = myTree.getNode(word);
						CheckDocumentList(current_WordItem, fileNames[i]);
					}

					if(myHashTable.find(word).word == "-99999")
					{
						WordItem temp_WordItem; 
						temp_WordItem.word = word;
						DocumentItem temp_DocumentItem;
						temp_DocumentItem.count = 1; temp_DocumentItem.fileName = fileNames[i];
						temp_WordItem.DocumentList.push_back(temp_DocumentItem);
						myHashTable.insert(word, temp_WordItem);
						myVector.push_back(temp_WordItem);
					}
					else
					{
						WordItem * current_WordItem = myHashTable.getHashNode(word);//Using pointer to increment counter, otherwise counter stays the same
						CheckDocumentHashTable(current_WordItem, fileNames[i]);

						bool FileExists = false;
						int index = GetVectorElementIndex(myVector,word);
						for (int x = 0; x < myVector[index].DocumentList.size(); x++)
						{
							if(myVector[index].DocumentList[x].fileName == fileNames[i])//Increases the count of Documentlist if the found filename matches with filename
							{
								myVector[index].DocumentList[x].count ++;
								FileExists = true;
								break;
							}
						}
						if(FileExists == false)
						{
							DocumentItem temp_Doc;
							temp_Doc.count = 1;
							temp_Doc.fileName = fileNames[i];
							myVector[index].DocumentList.push_back(temp_Doc);
						}
					}
				}
			}
		}
	}

	cout << endl;
	cout << "After preprocessing, the unique word count is " << myHashTable.getSize() 
		<< ". Current load ratio is " << myHashTable.getLoadFactor() << endl; 

	string line;
	cout << "Enter queried words in one line: ";
	cin.ignore();
	cin.seekg(0);

	getline(cin, line);
	line = ToLower(line);
	for (int i = 0; i < line.length(); i++)//Clears out the line
	{
		if(!IsAlphabetic(line[i]))
		{
			replace(line.begin(), line.end(), line[i],' ');
		}
	}

	bool IsLineEmpty = true;
	for (int i = 0; i < line.length(); i++)//Checks if the query is empty
	{
		if(line[i] != ' ')
		{
			IsLineEmpty = false;
		}
	}

	string word;
	bool IsFoundInTree = true;
	istringstream iss(line);
	while(iss >> word)// CHecks If all of the query words are found in the tree
	{
		word = ToLower(word);
		if(myTree.find(word) == "-99999")
		{
			IsFoundInTree = false;
		}
	}

	if(!IsLineEmpty)
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int k = 10;
		clock_t begin_time = clock();

		for (int t = 0; t < k; t++)
		{
			string temp_word;
			int PrintedFileCount = 0;
			if(IsFoundInTree)//If all query words are found, if is executed
			{
				for (int i = 0; i < numberOfFiles; i++)
				{
					istringstream iss(line);
					string output = "in Document " + fileNames[i];
					int wordCounter = 0; int valiCount = 0; //Every query word must be found on a file, so i will use these ints to check if every is found
					while(iss >> temp_word)
					{
						temp_word = ToLower(temp_word);
						WordItem * temp_WordItem = myTree.getNode(temp_word);
						for (int j = 0; j < temp_WordItem->DocumentList.size(); j++)
						{
							if(temp_WordItem->DocumentList[j].fileName == fileNames[i])
							{
								valiCount ++;
								if(t == 0)
								{
									output += ", " + temp_word + " found " + to_string(temp_WordItem->DocumentList[j].count) + " times, ";
								}
							}
						}
						wordCounter ++;
					}
					if(wordCounter == valiCount)//If every word is found on a file
					{
						if(t == 0)
						{
							cout << output << endl;
							PrintedFileCount++;//Then we gave output and increase the printed file count;
						}
					}
				}
				if(PrintedFileCount == 0)//Unless there is no file which contains all of the query words we gave this output
				{
					if(t == 0)
					{
						cout << "No document contains the given query" << endl;
					}
				}
			}
			else//If even a word is not a found program prints no document output
			{
				if(t == 0)
				{
					cout << "No document contains the given query" << endl;
				}
			}
		}
		double endBST = float(clock() - begin_time) / k;

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		begin_time = clock();
		for (int t = 0; t < k; t++)
		{
			string temp_word;
			int PrintedFileCount = 0;
			if(IsFoundInTree)//If all query words are found, if is executed
			{
				for (int i = 0; i < numberOfFiles; i++)
				{
					istringstream iss(line);
					string output = "in Document " + fileNames[i];
					int wordCounter = 0; int valiCount = 0; //Every query word must be found on a file, so i will use these ints to check if every is found
					while(iss >> temp_word)
					{
						temp_word = ToLower(temp_word);
						WordItem * temp_WordItem = myHashTable.getHashNode(temp_word);
						for (int j = 0; j < temp_WordItem->DocumentList.size(); j++)
						{
							if(temp_WordItem->DocumentList[j].fileName == fileNames[i])
							{
								valiCount ++;
								if(t == 0)
								{
									output += ", " + temp_word + " found " + to_string(temp_WordItem->DocumentList[j].count) + " times, ";
								}
							}
						}
						wordCounter ++;
					}
					if(wordCounter == valiCount)//If every word is found on a file
					{
						if(t == 0)
						{
							cout << output << endl;
							PrintedFileCount++;//Then we gave output and increase the printed file count;
						}
					}
				}
				if(PrintedFileCount == 0)//Unless there is no file which contains all of the query words we gave this output
				{
					if(t == 0)
					{
						cout << "No document contains the given query" << endl;
					}
				}
			}
			else//If even a word is not a found program prints no document output
			{
				if(t == 0)
				{
					cout << "No document contains the given query" << endl;
				}
			}
		}
		double endHT = float(clock() - begin_time) / k;
		///////////////////////////////////////////////////////////////////////////////////////////////////
		vector<WordItem>tempVector = myVector;
		quicksort(tempVector);
		//////////////////////////////////////////////////////////////////////////////////////////////////
		begin_time = clock();
		for (int t = 0; t < k; t++)
		{
			string temp_word;
			int PrintedFileCount = 0;
			if(IsFoundInTree)//If all query words are found, if is executed
			{
				for (int i = 0; i < numberOfFiles; i++)
				{
					istringstream iss(line);
					string output = "in Document " + fileNames[i];
					int wordCounter = 0; int valiCount = 0; //Every query word must be found on a file, so i will use these ints to check if every is found
					while(iss >> temp_word)
					{
						temp_word = ToLower(temp_word);
						WordItem temp_WordItem; temp_WordItem.word = temp_word;
						int index = binarySearch<WordItem>(tempVector,0,tempVector.size()-1, temp_WordItem);

						for (int j = 0; j < tempVector[index].DocumentList.size(); j++)
						{
							if(tempVector[index].DocumentList[j].fileName == fileNames[i])
							{
								valiCount ++;
								if(t == 0)
								{
									output += ", " + temp_word + " found " + to_string(tempVector[index].DocumentList[j].count) + " times, ";
								}
							}
						}
						wordCounter ++;
					}
					if(wordCounter == valiCount)//If every word is found on a file
					{
						if(t == 0)
						{
							cout << output << endl;
							PrintedFileCount++;//Then we gave output and increase the printed file count;
						}
					}
				}
				if(PrintedFileCount == 0)//Unless there is no file which contains all of the query words we gave this output
				{
					if(t == 0)
					{
						cout << "No document contains the given query" << endl;
					}
				}
			}
			else//If even a word is not a found program prints no document output
			{
				if(t == 0)
				{
					cout << "No document contains the given query" << endl;
				}
			}
		}
		double endBS = float(clock() - begin_time) / k;

		///////////////////////////////////////////MEDIAN ////////////////////////////////////////////////
		begin_time = clock();
		for (int i = 0; i < k; i++)
		{
			vector<WordItem>QuickSortedVector = myVector;
			quicksort(QuickSortedVector);
		}
		double endQMSV = float(clock() - begin_time) / k;
		/////////////////////////////////////// RANDOM  ////////////////
		begin_time = clock();
		for (int i = 0; i < k; i++)
		{
			vector<WordItem>QuickSortedVector = myVector;
			int random = rand() % QuickSortedVector.size();
			quicksort(QuickSortedVector, 0, QuickSortedVector.size()- 1, random);
		}
		double endQRSV = float(clock() - begin_time) / k;
		//////////////////////////////////////////////FIRST PIVOT//////////////////////
		begin_time = clock();
		for (int i = 0; i < k; i++)
		{
			vector<WordItem>QuickSortedVector = myVector;
			quicksort(QuickSortedVector, 0, QuickSortedVector.size() - 1, 0);
		}
		double endQFSV = float(clock() - begin_time) / k;
		///////////////////////////////////////////////////////
		begin_time = clock();
		for (int i = 0; i < k; i++)
		{
			vector<WordItem>mergeSortVector = myVector;
			mergeSort(mergeSortVector);
		}
		double endMS = float(clock() - begin_time) / k;
		///////////////////////////////////////////////////////
		begin_time = clock();
		for (int i = 0; i < k; i++)
		{
			vector<WordItem>heapSortVector = myVector;
			heapsort(heapSortVector);
		}
		double endHS = float(clock() - begin_time) / k;
		/////////////////////////////////////////////////////////
		begin_time = clock();
		for (int i = 0; i < k; i++)
		{
			vector<WordItem>insertionSortVector = myVector;
			insertionSort(insertionSortVector);
		}
		double endIS = float(clock() - begin_time);;

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		cout << "\nBinary Search Tree Time: " << endBST;
		cout << "\nHash Table Time: " << endHT;
		cout << "\nBinary Search Time: " << endBS<< "\n";
		////////////////////////////////////////////////////////////////////
		cout << "\nQuick Sort(median) Time: " << endQMSV;
		cout << "\nQuick Sort(random) Time: " << endQRSV;
		cout << "\nQuick Sort(first) Time: " << endQFSV;
		cout << "\nMerge Sort Time: " << endMS;
		cout << "\nHeap Sort Time: " << endHS;
		cout << "\nInsertion Sort Time: " << endIS << endl << endl;
		///////////////////////////////////////////////////////////
		cout << "Speed Up BST/HST: " << (endBST / endHT )<< endl;
		cout << "Speed Up Merge Sort/Quick Sort(Median): " << (endMS / endQMSV) << "\n";
		cout << "Speed Up Heap Sort/Quick Sort(Median): " << (endHS / endQMSV) <<  "\n";
		cout << "Speed Up Insertion Sort/Quick Sort(Median): " << (endIS / endQMSV) << "\n";
		cout << "Speed Up Binary Search Tree Time / Binary Search Time: " <<  (endBST / endBS) <<  "\n";
		cout << "Speed Up Binary Search / Hash Table Time: " <<  (endBS /  endHS) <<  "\n";
	}
	else
	{
		cout << "Query is empty, you must enter a query!" << endl;
	}
	return 1;
}