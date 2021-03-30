#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

//class headers
#include "RenderedItem.h"
#include "Helpers.h"

//defines namespace
using namespace std;


//constructor (w/ params)
RenderedItem::RenderedItem ( const Vector2 & pos, char character, Color colour )
{

	m_character = character;
	m_position = pos;
	m_colour = colour;

}

//default item (constructor w/ no params)
RenderedItem::RenderedItem ()
{
	//defaults to 0,0 w/ symbol 'N'

	m_position = Vector2 ();
	m_character = 'N';
	m_colour = Color::red;
}

RenderedItem::~RenderedItem ()
{
}

#pragma region  getterssetters

Vector2 RenderedItem::getPosition ()
{
	return m_position;
}

void RenderedItem::setPosition ( const Vector2 & vect )
{
	m_position = vect;
}

#pragma endregion

void RenderedItem::draw ()
{
	drawChar ( m_character, m_position, m_colour );
}

void RenderedItem::erase ()
{
	clearCell ( m_position );
}

void RenderedItem::setColour ( Color colour )
{
	m_colour = colour;
}
