#include "AVLTree.h"
#include "AVLTree.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
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

int main()
{
	int numberOfFiles;
	cout << "Enter number of input files: ";
	cin >> numberOfFiles;
	vector<string> fileNames ;//Keeping the filenames on a vector list

	for (int i = 0; i < numberOfFiles; i++)
	{
		string fileName;
		cout << "Enter " << i + 1 << ". file name:";
		cin >> fileName;
		fileNames.push_back(fileName);
	}

	string emptyString = "-9999";//NOT FOUND VALUE is initialzed as -9999
	WordItem ITEM_NOT_FOUND;
	AvlTree<string, WordItem> myTree(emptyString,ITEM_NOT_FOUND);//Creating my tree with not found value

	for (int i = 0; i < fileNames.size(); i++) //This loop is used to scan each file and inserts the words into the tree
	{
		ifstream file;
		file.open(fileNames[i].c_str());
		if(file.fail())//Make sure the file is openable
		{
			cout << "Fail can not be opened."<< endl;
		}
		else
		{
			string word;
			while (file >> word)
			{
				word = ToLower(word);
				if(IsAlphabeticWord(word))
				{
					if(myTree.find(word) == "-9999")//If my word is not found in my tree, program inserts a new node into the necessary place
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
				}
			}
		}
	}
	string line;
	cout << "Enter queried words in one line: ";
	cin.ignore();
	getline(cin, line);

	string word;
	istringstream kiss(line);
	bool IsFoundInTree = true;
	while(kiss >> word)// CHecks If all of the query words are found in the tree
	{
		word = ToLower(word);
		if(myTree.find(word) == "-9999")
		{
			IsFoundInTree = false;
		}
	}

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
						output += ", " + temp_word + " found " + to_string(temp_WordItem->DocumentList[j].count);
					}
				}
				wordCounter ++;
			}
			if(wordCounter == valiCount)//If every word is found on a file
			{
				cout << output << endl;
				PrintedFileCount++;//Then we gave output and increase the printed file count
			}
		}
		if(PrintedFileCount == 0)//Unless there is no file which contains all of the query words we gave this output
		{
			cout << "No document contains the given query" << endl;
		}
	}
	else//If even a word is not a found program prints no document output
	{
		cout << "No document contains the given query" << endl;
	}

	return 1;
}