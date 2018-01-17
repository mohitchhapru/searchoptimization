#include "Dictionary.h"

/* This is a constructor
Precondition: The object is declared
Postcondition: Space is allocated to the object */
Dictionary::Dictionary()
{
	root = new Node;
	for (int counter = 0; counter < 26; counter++) {
		root->charPtr[counter] = NULL;
		root->charFlag[counter] = false;
	}
}

/* This is a destructor 
Precondition: The object is declared
Postcondition: The memory is been released */
Dictionary::~Dictionary() {
	delete root;
}

/* This constructor builds a dictionary from the given text file link
Precondition: The object is been initialized
Postcondition: All the words from file are noted in object */
Dictionary::Dictionary(string file) {
	root = new Node;
	for (int counter = 0; counter < 26; counter++) {
		root->charPtr[counter] = NULL;
		root->charFlag[counter] = false;
	}

	ifstream inputFile(file);
	string line;
	while (getline(inputFile, line)) {
		addWord(line);
	}
	cout << wordCount() << " Words loaded.";
}

/* This function is used to add word into the dictionary
Precondition: The object is been initialized
Postcondition: The string given in argumented is been added*/
void Dictionary::addWord(string word) {
	Node *currNode = root;
	int charPosition = 0;
	for (int counter = 0; counter < word.length(); counter++) {
		word[counter] = tolower(word[counter]);
		charPosition = (int)word[counter] - (int)'a';
		if (currNode->charPtr[charPosition] == NULL) {
			Node* newNode;
			newNode = new Node;
			for (int counter1 = 0; counter1 < 26; counter1++) {
				newNode->charPtr[counter1] = NULL;
				newNode->charFlag[counter1] = false;
			}
			currNode->charPtr[charPosition] = newNode;	//Pointing to new node
		}
		currNode = currNode->charPtr[charPosition];		
	}
	currNode->charFlag[charPosition] = true;
	numWords++;
}

/* This function check if the given argument string is a prefix of any word in dictionary & The function is capable to handly lower and upper case.
Precondition: The object is been initialized
Postcondition: The function returns true if it finds argument as prefix of any word or else it returns false */
bool Dictionary::isPrefix(string word) {
	Node* currNode;
	currNode = new Node; 
	currNode = root;
	//bool isPrefix = true;
	for (int counter = 0; counter < word.length(); counter++) {
		word[counter] = tolower(word[counter]);

		if (currNode->charPtr[word[counter] - (int)'a'] == nullptr || word[counter] - 'a' < 0) {
			return false;
		}
		currNode = currNode->charPtr[word[counter] - 'a'];
	}
	return true;
}

/* This function check if the given argument string is a word in dictionary & The function is capable to handly lower and upper case.
Precondition: The object is been initialized
Postcondition: The function returns true if it finds word in dictionary or else it returns false */
bool Dictionary::isWord(string word) {
	Node* currNode;
	currNode = new Node;
	currNode = root;
	int charPosition;
	for (int counter = 0; counter < word.length(); counter++) {
		charPosition = word[counter] - 'a';
		word[counter] = tolower(word[counter]);
		if (currNode->charPtr[charPosition] == nullptr || charPosition < 0) {
			return false;
		}
		currNode = currNode->charPtr[charPosition];
	}
	return currNode->charFlag[charPosition];
}

/* This function used to find number of words in dictionary
Precondition: The object is been initialized
Postcondition: The funciton returns number of words present in dictionary */
int Dictionary::wordCount() {
	return numWords;
}