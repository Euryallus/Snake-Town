//libraries required to output data to console
#include <iostream>
#include <Windows.h>
#include <string>


//imports self-created objects
#include "RenderedItem.h"
#include "Helpers.h"

//defines namespace used
using namespace std;

void goTo ( const Vector2 & vect ) //moves cursor to position given in params (e.g. goTo(Vector2(1, 1)) would move cursor to (1, 1) on screen (top left)
{
	HANDLE hStdout = GetStdHandle ( STD_OUTPUT_HANDLE );
	COORD position ={ (SHORT)vect.X (), (SHORT)vect.Y () };

	SetConsoleCursorPosition ( hStdout, position );
}

void drawString ( const std::string & stringToOutput, const Vector2 & pos, Color colourInputS ) //goes to start position given and outputs string passed in colour passed
{
	goTo ( pos );

	string outputString = "\033[1;" + to_string ( static_cast<int>(colourInputS )) + "m" + stringToOutput + "\033[ 0m\n";

	cout << outputString;
}


void drawChar ( char & charToInput, const Vector2 & vect, Color colourInputC ) //goes to "cell" specified and outputs character given in colour defined
{
	goTo ( vect );

	string outputString = "\033[1;" + to_string ( static_cast<int>(colourInputC )) + "m" + charToInput + "\033[ 0m\n";

	cout << outputString;
}

void clearCell ( const Vector2 & vect ) //goes to "cell" specified (vector pos on screen) and outputs a blank space (effectively clearing it)
{
	goTo ( vect );
	cout << "\033[1;" + to_string ( 0 ) + "m" + " " + "\033[ 0m\n";;
}

void clearSection ( const Vector2 & mid, const Vector2 & dimensions ) //middle of section and size of section passed as params using Vector2
{
	string output = string ( dimensions.X (), ' ' ); //creates string of spaces the same length as X component of dimensions vector

	for (int i = 0; i < dimensions.Y (); i++) //for loop from 0 to Y component of dimensions vector, calculates start position of section based off length of string and size desired
	{
		drawString ( output, Vector2 ( mid.X () - (dimensions.X () / 2), mid.Y () + (i - 1) ), Color::black ); //outputs string at position calculated in background colour (black, in this case)
	}
}

void clearSection ( const Vector2 & mid, const Vector2 & dimensions, Color colour )
{
	string output = string ( dimensions.X (), ' ' ); //creates string of spaces the same length as X component of dimensions vector

	for (int i = 0; i < dimensions.Y (); i++) //for loop from 0 to Y component of dimensions vector, calculates start position of section based off length of string and size desired
	{
		drawString ( output, Vector2 ( mid.X () - (dimensions.X () / 2), mid.Y () + (i - 1) ), colour ); //outputs string at position calculated in background colour 
	}
}

bool isKeyPressed ( int virtualKey )
{
	virtualKey = toupper ( virtualKey );

	// Call GetAsyncKeyState and mask out all bits except BIT 15 because of how the function works
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate

	//taught in lectures, used instead of _getch() as it has a certain "lag" to it which was impeeding gameplay 

	return (bool)(GetAsyncKeyState ( virtualKey ) & 0x8000);
}





