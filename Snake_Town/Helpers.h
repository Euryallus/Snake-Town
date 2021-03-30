#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include "RenderedItem.h"
#include "Vector2.h"
#include "Color.h"



void drawString ( const std::string & stringToOutput, const Vector2 & pos, Color colourInputS ); //takes string, position and colour & outputs it to console

void drawChar ( char & charToInput, const Vector2 & vect, Color colourInputC ); //takes char, position and colour & outputs character to console

void goTo ( const Vector2 & vect ); //moves cursor to position specified

void clearCell ( const Vector2 & vect ); //""clears"" cell at point passed by printing ' ' in black

void clearSection ( const Vector2 & mid, const Vector2 & dimensions ); //clears section of screen defined in params (default = black)

void clearSection ( const Vector2 & mid, const Vector2 & dimensions, Color colour );//clears section of screen defined in params, this time in colour defined


bool isKeyPressed ( int virtualKey ); //returns whether or not key input is pressed (e.g. isKeyPressed('w') returns true or false)


#endif // HELPERS_H
