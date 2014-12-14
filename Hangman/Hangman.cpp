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
void usedAlpha(const char[], bool[]);
void storeAlpha(char, const char[], bool[]);
bool usedLetter(const char[], const bool[], char);



int main()
{
	//Initializations

	//play again bool flag
	bool keepPlaying = true;

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
		char guess;

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

		//arrays to check for used letters
		const char alphabet[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		bool alphaCheck[] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

		//internal game loop, start of game
		do
		{
			//clears the screen
			clearScreen();

			//prints hangman
			printGallows(wrongGuesses);

			//prints used letters
			usedAlpha(alphabet, alphaCheck);

			//Check win/lose conditions
			if (wrongGuesses >= 8)
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
				cout << endl;
				for (int i = 0; i < wordLength; i++)
				{
					if (guessedLetters[i])
						cout << gameWord[i];
					else
						cout << "-";
				}
			}
			cout << endl << endl;
			
			//prevents asking for more input if the endgame flag has already been set
			//also added in duplicate check
			bool badLetter;
			
			do
			{
				badLetter = false;
				if (!endgame)
				{
					guess = getInput();
					badLetter = usedLetter(alphabet, alphaCheck, guess);
				}
				if (badLetter)
					cout << "Duplicate Letter"<<endl;

			} while (badLetter);

			//test guess char against wordArray and set guessedLetter flags
			bool isLetterinWord = false;

			for (int i = 0; i < wordLength; i++)
			{
				if (!guessedLetters[i] && (gameWord[i] == guess))
				{
					guessedLetters[i] = true;
					isLetterinWord = true;
				}
			}

			//if letter isn't found then add to wrong guess variable
			if (!isLetterinWord)
			{
				wrongGuesses++;
				
			}
			
			storeAlpha(guess, alphabet, alphaCheck);
			//check if word has been solved
			//set game condition to true, and then check if it should be changed to false
			guessedWord = true;
			for (int i = 0; i < wordLength; i++)
			{
				if (!guessedLetters[i])
					guessedWord = false;
			}


		} while (!endgame);
		
		
		delete[] guessedLetters;
		
		keepPlaying = playAgain();

	} while (keepPlaying);

	delete[] wordArray;


	return 0;
}

/******************************************************************
The storeAlpha() function takes in a character, and two arrays used
to compare to the alphabet. AlphaCheck is used as a parallel array
to the constant alphabet array. The function loops through the
alphabet and when it finds the location for the character passed in
it marks the location by setting a flag on the same location in
alphacheck. This keeps track of (wrong) guesses that are made.
(correct) guesses are displayed on the screen already so I kept them
from being tracked here.
*******************************************************************/
void storeAlpha(char used, const char alphabet[], bool alphaCheck[])
{
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i] == used)
		{
			alphaCheck[i] = true;
		}
	}
}

/*******************************************************************
usedAlpha() simply loops through the alphabet array and the bool
array that tracks what letters have been used. When it finds a
letter that has been used it sends it out to the console so that
the user can see what letters they have already guessed wrong.
*******************************************************************/
void usedAlpha(const char alphabet[], bool alphaCheck[])
{
	cout << "Used letters: ";
	for (int i = 0; i < 26; i++)
	{
		if (alphaCheck[i])
		{
			cout << alphabet[i];
		}
	}
	cout << endl;
}
/********************************************************************
Returns true or false on whether the letter being used has been used
previously. If it has been used already it will send back true and
the calling function will get a new letter.
********************************************************************/
bool usedLetter(const char alphabet[], const bool alphaCheck[], char check)
{
	bool hasThisLetterBeenUsed = false;
	for (int i = 0; i < 26; i++)
	{
		if (alphabet[i] == check)
			if (alphaCheck[i] == true)
				hasThisLetterBeenUsed = true;
	}
	return hasThisLetterBeenUsed;
}

/*********************************************************************
playAgain() simple asks the user for input, uses the getInput function
to receive and sanatize the input, and will either loop the game again
if the user says Y or y, otherwise it will end the game.
*********************************************************************/
bool playAgain()
{
	cout << "Do you wish to play again? (y/n)" << endl;
	char play = getInput();
	if (play == 'n')
	{
		return false;
	}
	if (play == 'y')
		return true;
	else
		return false;
}

/************************************************************************
the getInput() function asks the user for input, which it will then clear
extraneous white spaces from, check to make sure only one character has
been entered, checks to make sure the char is an alpha, and if it fails
any of those tests it loops asking for correct input. When it has finished
and validated input it converts it to a char and returns it to the calling
function.
*************************************************************************/
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
			int length = input.length();
			changed = false;
			for (int i = 0; i < length-1; i++)
			{
				if (input.at(i) == ' ' && input.at(i + 1) == ' ')
				{
					input.erase(i, 1);
					changed = true;
				}
			}
		} while (changed);

		//check for single spaces
		for (int i = 0; i < input.length(); i++)
		{
			if (input.at(i) == ' ')
				input.erase(i, 1);
		}

		//check if more than one letter
		if (input.length() > 1)
		{
			cout << "You can only input one letter." << endl;
		}

		if (input.length() == 1)
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

/**************************************************************
fillWordArray() opens up a specified file and fills the array
that has been passed into it with words from the file. This
function works closely with the countWords array so I did not
add in extra functionality / error checking here.
**************************************************************/
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

/****************************************************************
countWords() takes in a filename, opens the file if it can find it
then goes through the file taking up a count of its contents. Once
the file has been counted it returns the number of items in the file
****************************************************************/
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

/*******************************************************************
clearScreen() is a simple for loop that makes the console print out
25 nextline characters, essentially wiping the screen for the basic
console window. Fairly simple, and can be customized to do more or
less easily.
*******************************************************************/
void clearScreen()
{
	for (int i = 0; i < 25; i++)
		cout << endl;
}


/*******************************************************************
printGallows() takes in an int number of wrong guesses which it puts
into a switch statement to determine which level of hangman to print
to the console. 
*******************************************************************/
void printGallows(int x)
{
	const int zero = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8;

	switch (x)
	{
	case zero:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;
	
	case one:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;		
		cout << "#########" << endl;
		cout << endl;
		break;

	case two:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;

	case three:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;

	case four:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;

	case five:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|    /" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;

	case six:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|    / \\" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;

	case seven:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|   _/ \\" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;

	case eight:

		cout << " __   __ _______ __    _ _______ __   __ _______ __    _ " << endl;
		cout << "|  | |  |   _   |  |  | |       |  |_|  |   _   |  |  | |" << endl;
		cout << "|  |_|  |  |_|  |   |_| |    ___|       |  |_|  |   |_| |" << endl;
		cout << "|       |       |       |   | __|       |       |       |" << endl;
		cout << "|   _   |   _   |  _    |   ||  |       |   _   |  _    |" << endl;
		cout << "|  | |  |  | |  | | |   |   |_| | ||_|| |  | |  | | |   |" << endl;
		cout << "|__| |__|__| |__|_|  |__|_______|_|   |_|__| |__|_|  |__|" << endl;
		cout << endl;
		cout << "_______" << endl;
		cout << "|     |" << endl;
		cout << "|     O" << endl;
		cout << "|    /X\\" << endl;
		cout << "|   _/ \\_" << endl;
		cout << "|" << endl;
		cout << "|" << endl;
		cout << "#########" << endl;
		cout << endl;
		break;
	}
}