#ifndef RENDEREDITEM_H
#define RENDEREDITEM_H

#include "Vector2.h"
#include "Color.h"

class RenderedItem
{
protected:

	Vector2 m_position;
	char m_character;
	Color m_colour;

public:
	RenderedItem (); //default constructor
	RenderedItem ( const Vector2 & pos, char character, Color colour ); //constructor, takes position, colour & character

	~RenderedItem (); //destructor

	virtual void draw (); //draws character to screen in position stored & in colour stored
	virtual void erase (); //clears the cell the character is at by printing a blank ' '

	//getters & setters
	void setColour ( Color colour );
	Vector2 getPosition ();
	void setPosition ( const Vector2 & vect );
};


#endif // !RENDEREDITEM_H

