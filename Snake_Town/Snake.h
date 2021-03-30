#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>
#include <vector>
#include "RenderedItem.h"
#include "SnakeSegment.h"
#include "Game.h"
#include "Vector2.h"
#include "TimedItem.h"

class Snake
{
private:

	int m_inputMethod = 0;
	int m_length = 1;
	int m_tickTime = 0;
	int m_score = 0;
	int m_pointsPerItem;

	bool m_playing = true;

	char m_character;

	Color m_colour1;
	Color m_colour2;
	Color m_currentColour = Color::red;

	void checkInput ();
	void updateSegments ();
	void drawSnake ();
	void detectSelf ();

	Vector2 direction;

	SnakeSegment m_segments[ 5400 ]; //based on average level dimensions (~ 45 x 120 grid) 5400 is the max. number of segments the snake can have before dying

public:

	Snake (); //default constructor
	~Snake (); //destructor

	Snake ( const Vector2 & pos, Color colour1, Color colour2, char character ); //constructor, takes starting position, colour combos & character used for each segment as params
	void update (); //updates each segment in snake & re-draws them

	
	void addSection ( int sections ); //adds additional X no. of sections onto end of snake
	void detectWalls ( vector<RenderedItem> & wall ); //checks pos of snake head vs pos of each wall segment in wall vector passed
	int detectItems ( vector<RenderedItem> & item ); //checks pos of snake head vs pos of each item in wall vector passed

	bool detectTimedItem ( TimedItem & item );

	//getters & setters
	bool returnAlive ();
	void increaseScore ( int score );
	void setScore ( int score );
	void setInputMode ( int mode );
	Vector2 getDirection ();
	void setDirection ( const Vector2 & dir );
	int returnScore ();

};

#endif //SNAKE_H

