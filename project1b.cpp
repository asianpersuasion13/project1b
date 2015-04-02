// header files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>


using namespace std;


//GLOBAL CONSTANTS
const int ARRAY_SIZE = 15;
const int ROW = 10;
const int COLUMN = 3;
const int SYMBOLS_ROW = 6;
const int SYMBOLS_COLUMN = 2;



// function prototypes
void openOriginalFile( char array[][ARRAY_SIZE][ARRAY_SIZE] );

void randomize( char originalArray[][ARRAY_SIZE][ARRAY_SIZE], char randomizedArray[][ARRAY_SIZE][ARRAY_SIZE] );

void strcpy( char source[], char destination[] );

bool strcmp( char str1[], char str2[] );

void openFile( char array[][ARRAY_SIZE][ARRAY_SIZE] );

void printToScreen( char array[][ARRAY_SIZE][ARRAY_SIZE] );

void writeToFile( char array[][ARRAY_SIZE][ARRAY_SIZE], char checkForOriginalFileName[] );

void bonusValue( char array[][ARRAY_SIZE][ARRAY_SIZE], char originalArray[][ARRAY_SIZE][ARRAY_SIZE] );



// main program
int main()
{
	// initialize variables
	char arrayToHoldSymbols[ARRAY_SIZE][ARRAY_SIZE][ARRAY_SIZE];
	char arrayToHoldRandomizedSymbols[ARRAY_SIZE][ARRAY_SIZE][ARRAY_SIZE];
	char outputFile[ARRAY_SIZE];
	char symbolsFile[ARRAY_SIZE] = "symbols";
	int selection;



	// randomize the original file to have a default machine configuration
		// prevents program from loading/printing garbage if selection 1 or 2 are not chosen first
	openOriginalFile( arrayToHoldSymbols );
	randomize( arrayToHoldSymbols, arrayToHoldRandomizedSymbols );



	// menu selection
	do
		{
			cout << endl << endl << "	Welcome to Slots and Slots of Fun!" << endl;
			cout << "	==================================" << endl;
			cout << "	1.  Spin the reel!" << endl;
			cout << "	2.  Read in an existing machine configuration from a file" << endl;
			cout << "	3.  Print the machine configuration to the screen" << endl;
			cout << "	4.  Print the machine configuration to a file" << endl;
			cout << "	5.  Pick a reel and slot number from a file to find out the symbol and its value!" << endl;
			cout << "	6.  Exit the program" << endl;
			cout << "	Enter your selection: ";

			// get user selection
			cin >> selection;
			cout << endl << endl << endl;

			switch ( selection )
			{
				// randomly generate a new slot machine (just storing into an array)
				case 1:
					randomize( arrayToHoldSymbols, arrayToHoldRandomizedSymbols );
					cout << "You randomized the slot machine! Try printing something to the screen or a file." << endl << endl;
					break;		
				// read in an existing file and stores it into an array	
				case 2:
					openFile( arrayToHoldRandomizedSymbols );
					break;	
				// prints whatever is stored in an already loaded array
				case 3:
					printToScreen( arrayToHoldRandomizedSymbols );
					break;
				// print the randomly generated array to a file
				case 4:
					writeToFile( arrayToHoldRandomizedSymbols, symbolsFile );
					break;
				// allow the user to pick a file to load
				// allow the user to pick a reel and column
					// print the symbol and the bonus number to the screen
				case 5:
					openFile( arrayToHoldRandomizedSymbols );
					bonusValue( arrayToHoldRandomizedSymbols, arrayToHoldSymbols );
					break;
				// Exit the program				
				case 6:
					cout << "Thanks for playing!" << endl << endl;
					break;
			}
		}
	while (selection != 6 );



	// end the program
	return 0;
}





// function implementations
void openOriginalFile( char array[][ARRAY_SIZE][ARRAY_SIZE] )
{
	// initialize variables
	ifstream fin;

	// clear the file stream and open "symbols"
	fin.clear();
	fin.open( "symbols" );

	for( int i = 0; i < SYMBOLS_ROW ; i++ )
	{
		for( int j = 0; j < SYMBOLS_COLUMN; j++ )
		{
			fin >> array[i][j];
		}
	}
	fin.close();
}



void randomize( char originalArray[][ARRAY_SIZE][ARRAY_SIZE], char randomizedArray[][ARRAY_SIZE][ARRAY_SIZE] )
{
	// initialize variables
	int randomTime;



	// prime the time
	srand( time(NULL) );

	for( int i = 0; i < ROW; i++ )
	{
		for( int j = 0; j < COLUMN; j++ )
		{
			// store random number in variable
			randomTime = rand() % 5 + 1;
			// copy the original array (source) at random number and first column to a new array
			strcpy( originalArray[randomTime][0], randomizedArray[i][j] );
		}
	}
}



void strcpy( char source[], char destination[] )
{
	// initialize variables
	int i = 0;
	


	while( source[i] != '\0' )
	{
		destination[i] = source[i];
		i++;
	}

	// add the null terminator
	destination[i] = '\0';

}



bool strcmp( char str1[], char str2[] )
{
	//initialize variables
	int i = 0;



	// while the character is not null and the strings are the same length
	while( str1[i] != '\0' && str1[i] == str2[i] )
	{
		i++;
	}

	// will return either true or false
	return str1[i] == str2[i];
}



void openFile( char array[][ARRAY_SIZE][ARRAY_SIZE] )
{
	// initialize variables
	ifstream fin;
	char file[ARRAY_SIZE];



	// prompt the user for the desired file to be loaded
	cout << "Enter the name of the file that you want to read in from: ";
	cin >> file;



	// clear the file stream
	// open the file
	fin.clear();
	fin.open( file );



	// If file cannot be opened write error message to the screen
	if( !fin.good() )
	{
		cout << endl << "Could not open the file." << endl;
		cout << "Please enter a valid file name." << endl;
	}	



	else
	{
		// prints a message telling the user that the file was successfully read
		cout << endl << endl << "Successfully read in the file " << '"' << file << '"' << "!" << endl << endl;

		// read in the data (nested loop) and store it in array
		for( int i = 0; i < ROW ; i++ )
			{
				for( int j = 0; j < COLUMN; j++ )
				{
					fin >> array[i][j];
				}
			}	
	}

	cout << endl;



	// close the file
	fin.close();
}



void printToScreen( char array[][ARRAY_SIZE][ARRAY_SIZE] )
{
	cout << endl << endl;

	for( int i = 0; i < ROW; i++ )
	{
		for( int j = 0; j < COLUMN; j++ )
		{
			cout << array[i][j] << "	";
		}
		cout << endl;
	}

	cout << endl << endl << endl;
}



void writeToFile( char array[][ARRAY_SIZE][ARRAY_SIZE], char checkForOriginalFileName[] )
{
	// initialize variables
	ofstream fout;
	char file[ARRAY_SIZE];



	// prompt the user for filename
	cout << "Enter the name of the file you want the symbols to be stored in: ";
	cin >> file;

	// does not let you override original "symbols" file name
	if( strcmp( file, checkForOriginalFileName ) == true )
	{
		cout << endl << "Error: Cannot overwrite original file" << endl << endl << endl;
	}

	else
	{
		// Store the symbols in the file named by the user
		fout.open( file );
	
		// read out the data (nested loop)
		for( int i = 0; i < ROW; i++ )
		{
			for( int j = 0; j < COLUMN; j++ )
			{
				fout << array[i][j] << "	";
			}
			fout << endl;
		}
	}

	fout.close();
}



void bonusValue( char array[][ARRAY_SIZE][ARRAY_SIZE], char originalArray[][ARRAY_SIZE][ARRAY_SIZE] ) 
{
	// initialize variables
	int reel;
	int column;



	// prompt the user for a reel and column number to output symbol and bonus value
	cout << "Pick a reel number and column number that you want to know the symbol and bonus value of." << endl << endl;
	cout << "REEL: ";
	cin >> reel;
	cout << endl << "COLUMN: ";
	cin >> column;


	// makes sure that the reel and column by the user are valid
	if( ( reel < ROW && reel >= 0 ) && ( column < COLUMN && column >= 0 ) )
	{
	
		for( int i = 0; i < SYMBOLS_ROW; i++ )
		{
			for( int j = 0; j < SYMBOLS_COLUMN; j++ )
			{
				if ( strcmp( array[reel][column], originalArray[i][j] ) == true )
				{
								// symbol		// number
					cout << endl << endl << array[reel][column] << "	" << originalArray[i][1] << endl << endl;
				}
			}
		}
	}
	
	else
	{
		cout << endl << "Oops! Looks like your value is out of bounds. Please pick a valid number for the reel and column." << endl << endl;
	}
}
