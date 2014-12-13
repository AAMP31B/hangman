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
bool playAgain();
char getInput();
int countWords(string);
void fillWordArray(string*, string);


int main()
{
	//Initializations

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
	
	
	//Outer game loop, when looped will reset variables
	do
	{
		//keep track of wrong guesses
		int wrongGuesses = 0; 
		bool guessedWord = false;
		bool endgame = false;

		//gets random number
		int RNG = rand() % wordCount;

		//gets word and length of word
		string& gameWord = wordArray[RNG];
		int wordLength = gameWord.length();

		//bool array to track guessed letters
		bool* guessedLetters = new bool[wordLength];
		//populate array
		for (int i = 0; i < wordLength; i++)
			guessedLetters[i] = false;

		//internal game loop, start of game
		do
		{
			//clears the screen
			clearScreen();

			//prints hangman
			printGallows(wrongGuesses);

			//Check win/lose conditions
			if (wrongGuesses >= 6)
			{
				cout << "You are dead!" << endl;
				cout << "The word was: " << gameWord << endl;
				endgame = true;
			}
			else if (guessedWord)
			{
				cout << "You won!" << endl;
				cout << "You guessed the word: " << gameWord << endl;
				endgame = true;
			}
			else //Prints hidden word + guessed letters
			{
				for (int i = 0; i < wordLength; i++)
				{
					if (guessedLetters[i])
						cout << gameWord[i];
					else
						cout << "_";
				}
			}
			cout << endl;


		} while (endgame);
	} while (keepPlaying);



	return 0;
}

char getInput()
{
	string input = "";
	char cleanedInput;
	bool changed;
	bool goodInput = false;

	while (!goodInput)
	{


		//get input
		cout << "Please enter a letter: ";
		getline(cin, input);
		cout << endl;

		do //whitespace cleanup
		{
			changed = false;
			for (int i = 0; i < input.length() - 1; i++)
			{
				if (input.at(i) == ' ' && input.at(i + 1) == ' ')
				{
					input.erase(i, 1);
					changed = true;
				}
			}
		} while (changed);

		//check if more than one letter
		if (input.length > 1)
		{
			cout << "You can only input one letter." << endl;
		}

		if (input.length == 1)
		{
			char temp = input[0];
			if (isalpha(temp))
			{
				tolower(temp);
				cleanedInput = temp;
				goodInput = true;
			}
			else if (!isalpha(temp))
			{
				cout << "You must enter a letter." << endl;
			}
		}
	}
	return cleanedInput;
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