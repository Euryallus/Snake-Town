#include <iostream>
#include "Vector2.h"

using namespace std;

Vector2::Vector2 ( int x, int y ) //constructor, assigns position based on input
{
	m_x = x;
	m_y = y;
}

Vector2::Vector2 () //default constructor (assigns pos of 0,0 to item)
{
	m_x = 0;
	m_y = 0;
}

Vector2 Vector2::operator+( const Vector2 &vect ) //custom addition operator, returns a Vector2 which adds own position & Vector2 given as params
{
	return Vector2 ( m_x + vect.X(), m_y + vect.Y());
}

Vector2 Vector2::operator-( const Vector2 &vect ) //custom subtraction operator, returns Vector2 of own position - Vector2 position passed as param
{
	return Vector2 ( m_x - vect.X (), m_y - vect.Y () );
}

Vector2 Vector2::operator/( int val ) //custom division operator
{
	return Vector2 ( m_x / val, m_y / val ); //returns Vector2 with values of each co-ord divided by int passed
}

bool Vector2::operator==( Vector2 vect )
{
	if (m_x == vect.X () && m_y == vect.Y ())
	{
		return true;
	}
	else
	{
		return false;
	}
}


