#ifndef SNAKESEGMENT_H
#define SNAKESEGMENT_H

#include "RenderedItem.h"

using namespace std;

class SnakeSegment
	: public RenderedItem //variant of RenderedItem
{
private:

public:
	SnakeSegment (); //default constructor
	SnakeSegment ( Vector2 pos, char character, Color colour ); //constructor, takes pos of segment, character it outputs and it's colour

	//takes previous segment as a param and uses x & y pos of it to move itself along
	void moveAlong ( SnakeSegment previousSegment );

	//colour setter
	void animate ( Color colour );

};

#endif // !SNAKESEGMENT_H