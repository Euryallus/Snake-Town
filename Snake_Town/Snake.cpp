#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

#include <conio.h>

#include "Helpers.h"
#include "Snake.h"
#include "RenderedItem.h"
#include "SnakeSegment.h"
#include "Game.h"

//namespace definition
using namespace std;

Snake::Snake () //default constructor
{
	m_character = 'S';

	m_colour1 = Color::purple;
	m_colour2 = Color::yellow;
	m_pointsPerItem = 25;
}

Snake::Snake ( const Vector2 & pos, Color colour1, Color colour2, char character )
{

	m_colour1 = colour1;
	m_colour2 = colour2; //assigns method variables

	m_pointsPerItem = 30; //no. of score points added per item pick-up
	m_length = 1; //length of the snake

	m_character = character;

	direction =Vector2 ( 1, 0 ); //sets default direction to right

	m_segments[ 0 ] =  (SnakeSegment ( pos, m_character, Color::lightYellow )); //adds initial "segment" to array

	addSection ( 3 ); //adds initial
}

Snake::~Snake (){

}

void Snake::checkInput () //Input detection 
{
	switch (m_inputMethod) //switches between 2 input methods (1 - wasd, 2 - ijkl)
	{
	case(0):

		//checks if key is pressed
		//checks if direction is "legal" (e.g. can't go right if already going left)
		//if legal - change direction variables

		if (isKeyPressed ( 'w' ))
		{
			if (direction.Y () != 1){
				direction.Y ( -1 );
				direction.X ( 0 );
			}
		}

		else if (isKeyPressed ( 's' ))
		{
			if (direction.Y () != -1){
				direction.Y ( 1 );
				direction.X ( 0 );
			}
		}

		else if (isKeyPressed ( 'a' ))
		{
			if (direction.X () != 1){
				direction.X ( -1 );
				direction.Y ( 0 );
			}
		}

		else if (isKeyPressed ( 'd' ))
		{
			if (direction.X () != -1){
				direction.X ( 1 );
				direction.Y ( 0 );
			}
		}

		break;

	case(1):

		//checks if key is pressed
		//checks if direction is "legal" (e.g. can't go right if already going left)
		//if legal - change direction variables

		if (isKeyPressed ( 'i' ))
		{
			if (direction.Y () != 1){
				direction.Y ( -1 );
				direction.X ( 0 );
			}
		}

		else if (isKeyPressed ( 'k' ))
		{
			if (direction.Y () != -1){
				direction.Y ( 1 );
				direction.X ( 0 );
			}
		}

		else if (isKeyPressed ( 'j' ))
		{
			if (direction.X () != 1){
				direction.X ( -1 );
				direction.Y ( 0 );
			}
		}

		else if (isKeyPressed ( 'l' ))
		{
			if (direction.X () != -1){
				direction.X ( 1 );
				direction.Y ( 0 );
			}
		}

		break;

	}

}

void Snake::updateSegments ()
{
	m_tickTime = 0;
	//cycles each segment
	m_segments[ m_length - 1 ].erase ();

	for (int i = m_length - 1; i > 0; i--)
	{
		//gives each segment the position of the one before it 
		m_segments[ i ].moveAlong ( m_segments[ i - 1 ] );

		//each segment is an alternating colour, and animates so it looks like the snake is "crawling"
		++m_tickTime;

		if (m_tickTime == 1) {

			if (static_cast<int>(m_currentColour) == static_cast<int>(m_colour1))
			{
				m_currentColour = m_colour2;
			}
			else
			{
				m_currentColour = m_colour1;
			}

			//having a "tick" means that each cycle, the colours alternate

			//resets tick time, animates segment with alternate colour
			m_tickTime = 0;
			m_segments[ i ].animate ( m_currentColour );
		}

	}

	//finally updates the head
	m_segments[ 0 ].setPosition ( m_segments[ 0 ].getPosition () + direction );



	//m_segments[ 0 ].setPos ( m_segments[ 0 ].getX () + direction.X(), m_segments[ 0 ].getY () + direction.Y() );

}

int Snake::returnScore () //returns player score
{
	return m_score;
}

void Snake::drawSnake ()
{
	//cycles each segment and calls draw function
	for (int i = 0; i < m_length; i++)
	{
		m_segments[ i ].draw ();
	}
}

void Snake::addSection ( int sections ) {

	for (int i = 0; i < sections; i++)
	{
		//finds "tail" of snake
		SnakeSegment end = m_segments[ m_length - 1 ];

		//adds new "segment" to end of snake
		m_segments[ m_length ] =  (SnakeSegment ( m_segments[ m_length - 1 ].getPosition () - direction, m_character, m_colour2 ));

		//increases length by 1
		++m_length;
	}


}

void Snake::detectWalls ( vector<RenderedItem> & wall ) {
	//Compares wall position to position of head - if equal, collision has occurred, & playing is false
	SnakeSegment m_head = m_segments[ 0 ];

	for (size_t i = 0; i < wall.size (); i++)
	{
		if (m_head.getPosition() == wall[i].getPosition()) {

			m_playing = false;
			break;
		}

	}

}

int Snake::detectItems ( vector<RenderedItem> & item ) { //items list passed to snake

	SnakeSegment m_head = m_segments[ 0 ]; //head set as reference to segment @ front of snake

	for (size_t i = 0; i < item.size (); i++) //cycles each item in items list, checks if x and y positions match w/ head
	{
		if (m_head.getPosition () == item[i].getPosition()) { //if positions match

			addSection ( 2 ); //add 2 sections, increase score, return position of item in array
			increaseScore ( m_pointsPerItem );
			return static_cast<int>(i);

			break;
		}
	}

	return 300; //if no collision, return 300 (will never be obtained ""naturally"", so stands as the default)
	//NULL was initially used, however NULL is read as 0 so it kept breaking 

}

bool Snake::detectTimedItem (  TimedItem &item )
{
	if (m_segments[ 0 ].getPosition () == item.returnPosition ())
	{
		addSection ( 4 );
		increaseScore ( 50 );
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::detectSelf () {
	//Cycles each segment in self and compares to the head - if equal, collision has occoured
	SnakeSegment m_head = m_segments[ 0 ];

	for (int i = 1; i < m_length; i++) //cycles each segment in snake, compares position to head, sets "m_playing" as false
	{
		SnakeSegment inspect = m_segments[ i ];

		if (m_head.getPosition ().X () == inspect.getPosition ().X () && m_head.getPosition ().Y () == inspect.getPosition ().Y ()) {
			m_playing = false;
		}
	}
}


void Snake::update ()
{

	if (m_playing) //if snake is ""alive"" still, run input detection, update segments accordingly, draw name, detect self, etc.
	{
		checkInput ();
		updateSegments ();
		drawSnake ();
		detectSelf ();
	}

}

bool Snake::returnAlive ()
{
	return m_playing; //returns snake state (true = alive, false = dead)
}

void Snake::increaseScore ( int score )
{
	m_score += score; //increases score by amount defined above
}

void Snake::setScore ( int score )
{
	m_score = score; //sets the score
}

void Snake::setInputMode ( int mode )
{
	m_inputMethod = mode; //sets input mode (1 -wasd or 2 - ijkl)
}

Vector2 Snake::getDirection ()
{
	return direction; //returns the Vector2 direction (mag. 1, e.g. (0, 1)
}

void Snake::setDirection ( const Vector2 & dir )
{
	direction = dir; //sets the direction vector
}


