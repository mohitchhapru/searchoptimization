#pragma once

// ADT
struct MyBoard {
	int iPosition, jPosition;
	char character;
	MyBoard *next;
};

class BoggleSolver
{
public:
	BoggleSolver();	
	void Push(char character, int i, int j);
	void Pop();
	bool isInQueue(int i, int j);
	string getString();
	void getCurrentNodelocation(int* i, int* j);
	void displayNodePositions(char inputMatrix[4][4]);
private:
	MyBoard* root;
	int count;
};