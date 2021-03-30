#include <string>

//file reading
#include <fstream>

//class headers
#include "RenderedItem.h"
#include "Snake.h"
#include "SnakeSegment.h"

//namespace definition
using namespace std;



SnakeSegment::SnakeSegment ( Vector2 pos, char character, Color colour ) //passes values to parent class (RenderedItem) 
	: RenderedItem ( pos, character, colour )
{ //no class-specific values or functions
}

SnakeSegment::SnakeSegment () //default constructor
{
}

void SnakeSegment::moveAlong ( SnakeSegment previousSegment ) //takes previous segment in snake as param, extracts its position and moves itself to said position
{
	setPosition ( previousSegment.getPosition () );
}

void SnakeSegment::animate ( Color colour ) //changes colour to colour passed as parameter 
{
	m_colour = colour;
}
