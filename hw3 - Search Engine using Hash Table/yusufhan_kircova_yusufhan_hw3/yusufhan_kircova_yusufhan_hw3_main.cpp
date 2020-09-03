#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "LinkedList.h"
#include "LinkedList.cpp"
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
};

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
					}
					else
					{
						WordItem * current_WordItem = myHashTable.getHashNode(word);//Using pointer to increment counter, otherwise counter stays the same
						CheckDocumentHashTable(current_WordItem, fileNames[i]);
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
		int k = 1500;
		auto start = std::chrono::high_resolution_clock::now();
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
		auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
			(std::chrono::high_resolution_clock::now() - start);


		start = std::chrono::high_resolution_clock::now();
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
		auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds> 
			(std::chrono::high_resolution_clock::now() - start);


		cout << "\nTime: " << BSTTime.count() / k << "\n";
		cout << "\nTime: " << HTTime.count() / k << "\n";
		double speed = (double)BSTTime.count() / (double)HTTime.count();
		cout << "Speed Up: " << speed << endl;
	}
	else
	{
		cout << "Query is empty, you must enter a query!" << endl;
	}
	return 1;
}