#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Custom ADT
struct Node {
	Node* charPtr[26];
	bool charFlag[26];
};

class Dictionary
{
public:
	Dictionary();
	Dictionary(string file);
	~Dictionary();
	void addWord(string word);
	bool isWord(string word);
	bool isPrefix(string word);
	int wordCount();

private:
	Node* root;
	int numWords;
	// Any private methods you need/want
};