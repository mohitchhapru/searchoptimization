#include "Dictionary.h"
#include "BoggleSolver.h"
#include <time.h>

/* This funciton pushes paramaters into a queue
Precondition: The Object is been initialized
Postcondition: The paramaters are pushed into the queue in form of node(ADT) */
void BoggleSolver::Push(char character, int i, int j) {
	MyBoard* newNode = root;

	if (count > 0) {
		for (int counter = 0; counter < count - 1; counter++, newNode = newNode->next);
		newNode->next = new MyBoard;
		newNode = newNode->next;
	}
	newNode->character = character;
	newNode->iPosition = i;
	newNode->jPosition = j;
	count++;
}

/* This funciton pops out paramaters into a queue
Precondition: The Object is been initialized
Postcondition: last node is been deleted from queue */
void BoggleSolver::Pop() {
	MyBoard* newNode = root;

	if (count == 1) {
		root->character = NULL;
		root->iPosition = root->jPosition = NULL;
		root->next = NULL;
	}
	else {
		for (int counter = 0; counter < count - 2; counter++, newNode = newNode->next);
		MyBoard* tempNode = newNode->next;
		delete tempNode; // Delete Last node
		newNode->next = NULL;
	}
	count--;
}

/* This is a constructor
Precondition: The object is declared
Postcondition: Space is allocated to the object */
BoggleSolver::BoggleSolver() {
	root = new MyBoard;
	root->character = root->iPosition = root->jPosition = count = NULL;
}

/* The function is used to check if the position passed as argument is present in queue
Precondition: The Object is been initialized
Postcondition: If the posistion(passed as argument) is present in queue then it returns true or else false   */
bool BoggleSolver::isInQueue(int i, int j) {
	MyBoard* counterNode = root;
	for (int counter = 0; counter < count; counter++, counterNode = counterNode->next) {
		if (counterNode->iPosition == i && counterNode->jPosition == j) {
			return true;
		}
	}
	return false;
}

/* The function check weather the given location is valid in terms of 4x4 matrix 
Precondition: The Object is been initialized
Postcondition: the function returns true if the location is valid or else returns false */
bool isValidLocation(int i, int j) {
	if ((i > -1 && i < 4) && (j > -1 && j < 4))
		return true;
	return false;
}

/* This funcion returns string value from queue*/
string BoggleSolver::getString() {
	string word = "";
	MyBoard* counterBoard = root;
	for (int counter = 0; counter < count; counter++,counterBoard=counterBoard->next) {
		word += counterBoard->character;
	}
	return word;
}

/* This function returns last node's location
Precondition: The Object is been initialized
Postcondition: The function navigates to the end of queue and returns the i & j value */
void BoggleSolver::getCurrentNodelocation(int* i, int* j) {
	MyBoard* counterBoard = root;
	for (int counter = 0; counter < count - 1; counter++, counterBoard = counterBoard->next);
	*i = counterBoard->iPosition;
	*j = counterBoard->jPosition;
}

/* This function displays matrix and highlits the char which form word with its position 
Precondition: The Object is been initialized
Postcondition: Display character and position matrix  */
void BoggleSolver::displayNodePositions(char inputMatrix[4][4]) {
	int wordCounter = 1;
	int positionMatrix[4][4] = { 0 };

	// Creating position matrix
	MyBoard* counterBoard = root;
	for (int counter = 0; counter < count ; counter++, counterBoard = counterBoard->next) {
		positionMatrix[counterBoard->iPosition][counterBoard->jPosition] = counter + 1;
	}

	// Displaying matrix
	for (int iCounter = 0; iCounter < 4; iCounter++) {
		for (int jCounter = 0; jCounter < 4; jCounter++) { // Loop to display Words in matrix
			if (isInQueue(iCounter, jCounter))
				cout << "'" << inputMatrix[iCounter][jCounter] << "'\t";
			else
				cout << inputMatrix[iCounter][jCounter] << "\t";
		}
		cout << "\t";
		
		for (int jCounter = 0; jCounter < 4; jCounter++) { /// Loop to display Positions in matrix
				cout << positionMatrix[iCounter][jCounter] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

/* This is a recursuive function whcih check posible words in the given boggle
Precondition: The Object is been initialized
Postcondition: This function detects and diplays the words found in boggle present in dictionary */
void SearchWord(Dictionary& Dict, Dictionary& newDict, BoggleSolver boardQueue, char inputMatrix[4][4], bool displayBoard) {
	
	string word = boardQueue.getString();
	if (Dict.isWord(word)) {	// check is the boardQueue is a valid word
		if (!newDict.isWord(word)) {	// check if the word in present in new Dictionary
			newDict.addWord(word);	// Add into new Dictionary
						
			if (displayBoard) { // Display the board according to user preference
				cout << "Word:" << word << endl << "Number of words:" << newDict.wordCount() << endl;
				boardQueue.displayNodePositions(inputMatrix);
			}
			else
			{
				cout << newDict.wordCount() << "\t" << word << endl;
			}
		}		
	}

	int i, j;
	boardQueue.getCurrentNodelocation(&i, &j);

	// Check North
	if (isValidLocation(i - 1, j)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i - 1, j)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i - 1][j])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i - 1][j], i - 1, j);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}		
	}
	// Check North East
	if (isValidLocation(i - 1, j + 1)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i - 1, j + 1)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i - 1][j + 1])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i - 1][j + 1], i - 1, j + 1);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
	// Check East
	if (isValidLocation(i, j + 1)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i, j + 1)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i][j + 1])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i][j + 1], i, j + 1);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
	// Check South East
	if (isValidLocation(i + 1, j + 1)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i + 1, j + 1)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i + 1][j + 1])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i + 1][j + 1], i + 1, j + 1);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
	// Check South
	if (isValidLocation(i + 1, j)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i + 1, j)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i + 1][j])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i + 1][j], i + 1, j);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
	// Check South West 
	if (isValidLocation(i + 1, j - 1)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i + 1, j - 1)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i + 1][j - 1])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i + 1][j - 1], i + 1, j - 1);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
	// Check West
	if (isValidLocation(i, j - 1)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i, j - 1)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i][j - 1])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i][j - 1], i, j - 1);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
	// Check North West
	if (isValidLocation(i - 1, j - 1)) { // Check if the given location is valid
		if (!boardQueue.isInQueue(i - 1, j - 1)) {	// check if the location is not used in the current Queue.
			if (Dict.isPrefix(word + (char)inputMatrix[i - 1][j - 1])) {   // Check if the contactination of letter is a valid prefix
				boardQueue.Push((char)inputMatrix[i - 1][j - 1], i - 1, j - 1);
				SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
				boardQueue.Pop();
			}
		}
	}
}

/* Main function drives all operation according to user inputs */
void main() {
	Dictionary Dict("Dictionary.txt"), newDict;
	char inputMatrix[4][4];
	int iCounter = 0, jCounter = 0, inputMethod;
	string userInput;

	cout << "\n___________________________________";
	cout << "\n\nEnter 0 (zero) for manual input";
	cout << "\nEnter 1 (one) for rolling 16 Dice";
	cout << "\nEnter your Preference : ";
	inputMethod = getchar() - 48;
	cout << "\n___________________________________";
	cin.ignore();
	
	if(inputMethod == 1){
		char dice[16][6];

		cout << "\n\nContent of 16 dice : \n_______________________\n";
		srand(time(NULL));
		for (iCounter = 0; iCounter < 16; iCounter++) {
			cout << "\nDice " << iCounter + 1 << ":  ";
			for (jCounter = 0; jCounter < 6; jCounter++){
				dice[iCounter][jCounter] = 'a' + rand() % 26;
				cout << dice[iCounter][jCounter] << " ";
			}
		}

		cout << "\n\nSelecting randon variable from above dice";
		int tempCounter=0;
		for (iCounter = 0; iCounter < 4; iCounter++) {
			cout << "\nRow " << iCounter << " :";
			for (jCounter = 0; jCounter < 4; jCounter++) {
				inputMatrix[iCounter][jCounter] = dice[tempCounter++][rand() % 6];
				cout << inputMatrix[iCounter][jCounter] << " ";
			}
		}
	}
	else {
		cout << "\n\nEnter Board \n________________\n";
		for (iCounter = 0; iCounter < 4; iCounter++) {
			cout << "Row " << iCounter << " :";
			getline(cin, userInput);
			jCounter = 0;
			for (int i = 0; i < userInput.length(); i++) {
				if (userInput[i] == ' ')
					continue;
				inputMatrix[iCounter][jCounter++] = userInput[i];
			}
		}
	}

	char gameChoice;
	int userWordCounter = 0;
	cout << "\n__________________________________";
	cout << "\n              GAME                ";
	cout << "\n__________________________________";
	cout << "\n____________________________________________________________________________________\n";
	cout << "\n Please Note : This Game is between user and computer. ";
	cout << "\n1. User should enter all possible words visiable in given above matrix seprated by space.";
	cout << "\n2. User should hit 'Enter Button' to submit,";
	cout << "\n3. This Program will compare the speed of user and computer also matches number of total correct answers submitted.";
	cout << "\n____________________________________________________________________________________\n";
	cout << "\nDo you want to play game ? (y/n) : ";
	gameChoice = getchar();	
	clock_t begin_time, userInputTime;	

	system("cls");
	Dictionary tempDict;
	// Building dictinary for reference 
	for (iCounter = 0; iCounter < 4; iCounter++) {
		for (jCounter = 0; jCounter < 4; jCounter++) {
			BoggleSolver boardQueue;
			boardQueue.Push(inputMatrix[iCounter][jCounter], iCounter, jCounter);
			SearchWord(Dict, tempDict, boardQueue, inputMatrix, false);
		}
	}
	system("cls");
	
	if (tolower(gameChoice) == 'y') {	// GAME		

		system("cls");		
		cout << "\n__________________________________";
		cout << "\n              GAME                ";
		cout << "\n__________________________________";
		for (iCounter = 0; iCounter < 4; iCounter++) {
			cout << "\n Row " << iCounter << ": ";
			for (jCounter = 0; jCounter < 4; jCounter++) {
				cout << inputMatrix[iCounter][jCounter] << " ";
			}
		}
		
		cout << "\nUser Input (Words seprated by ' '(space) : ";
		string inputString;		
		cin.ignore();
		begin_time = clock();
		getline(cin, inputString);
		userInputTime = clock() - begin_time;
		// Find number of corrent words entered by user ... userWordCounter

		string delimiter = " ";
		size_t pos = 0;
		while ((pos = inputString.find(delimiter)) != string::npos) {
			if (tempDict.isWord(inputString.substr(0, pos))){
				userWordCounter++;
			}
			inputString.erase(0, pos + delimiter.length());
		}
		if (tempDict.isWord(inputString.substr(0, pos))) {
			userWordCounter++;
		}
	}

	bool displayBoard;
	char userInputBoard;
	cout << "\nShow Board (y/n): ";
	cin >> userInputBoard;
	if (userInputBoard == 'y' || userInputBoard == 'Y')
		displayBoard = true;
	else
		displayBoard = false;
	begin_time = clock();	
	for (iCounter = 0; iCounter < 4; iCounter++) {
		for (jCounter = 0; jCounter < 4; jCounter++) {
			BoggleSolver boardQueue;
			boardQueue.Push(inputMatrix[iCounter][jCounter],iCounter,jCounter);
			SearchWord(Dict, newDict, boardQueue, inputMatrix, displayBoard);
		}
	}
	clock_t computerTime = (clock() - begin_time);
	cout << "\n Computer took " << (float) ((float)computerTime / CLOCKS_PER_SEC) << " seconds to find " << newDict.wordCount() << " words";

	if (tolower(gameChoice) == 'y') {
		cout << "\n User took " << (float) ((float)userInputTime / CLOCKS_PER_SEC) << " seconds to find " << userWordCounter << " words\n";
	}
}
