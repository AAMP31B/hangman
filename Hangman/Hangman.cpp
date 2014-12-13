/*******************************************************************
Michael Hodges
C++ Final - Hangman
This program will simulate a game of hangman.
Input: File Input for wordlist / userinput for guesses
Output: Hangman Visuals, Guessed letters, Used Letters, Tries
*******************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

void clearScreen();
void printGallows(int);
void displayUsedLetters(char[]);
bool playAgain();
void getWordArray();
void getWord();
char checkInput(string);
int countWords(string);
void fillWordArray(string*, string);


int main()
{
	//play again bool flag
	bool keepPlaying = false;

	//store filename in a string for passing 
	string fileName = "wordList.txt";
	
	//get count of words in file
	//create array based off of number
	int wordCount = countWords(fileName);
	string* wordArray = new string[wordCount];
	
	//populate string array with words
	fillWordArray(wordArray, fileName);
	
	//seed random number generator
	srand(time(NULL));
	
	
	//Game Loop
	do
	{
		//gets random number
		int RNG = rand() % wordCount;

		//gets word and length of word
		string gameWord = wordArray[RNG];
		int wordLength = gameWord.length();


	} while (keepPlaying);
	return 0;
}

void fillWordArray(string* Array, string fileName)
{
	string temp = "";
	int count = 0;
	ifstream wordFile;
	wordFile.open(fileName);

	if (wordFile)
	{
		while (wordFile >> temp)
		{
			if (!temp.empty())
			{
				Array[count] = temp;
				count++;
			}
		}
	}
	wordFile.close();

}

int countWords(string fileName)
{
	int count = 0;
	string temp = "";
	ifstream wordFile;
	wordFile.open(fileName);

	if (wordFile)
	{
		while (wordFile >> temp)
		{
			count++;
		}
	}

	wordFile.close();
	
	return count;
}

void clearScreen()
{
	for (int i = 0; i < 25; i++)
		cout << endl;
}

void printGallows(int x)
{
	const int zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6;

	switch (x)
	{
	case zero:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		break;
	
	case one:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;		
		cout << "#########" << endl;
		break;

	case two:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		break;

	case three:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		break;

	case four:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		break;

	case five:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|    /" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		break;

	case six:
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|    / \\" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		break;
	}
}