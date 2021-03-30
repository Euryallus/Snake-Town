#include "introSnake.h"
#include "RenderedItem.h"
#include <string.h>

#include "Helpers.h"

using namespace std;

introSnake::introSnake () //default constructor
{
	m_colour1 = Color::red;
	m_colour2 = Color::lightYellow;

	pos = 0;
}

introSnake::introSnake ( const Vector2 & centreOfScreen, int yOffset ) //normal constructor
{
	m_colour1 = Color::cyan;
	m_colour2 = Color::white;

	m_centreOfScreen = centreOfScreen; //assigns member variables values from params passed
	pos = 0;

	m_startOfSnake = Vector2 ( m_centreOfScreen.X () - ((m_segmentCount * m_squareSize) / 2), m_centreOfScreen.Y () - yOffset ); //calculates start point (top left) of snake based on size & location of centre screen

	int xPos; //local variables used to calc. x & y pos of each ""cell"" (renderedItem) in the snake
	int yPos;

	Color colour = Color::purple;
	int counter = 0;

	for (int i = 0; i < m_segmentCount; i++) //cycles each ""segment"" in the snake (each 3x3 section)
	{
		if (i % 2 == 0) //checks if colour should be colour1 or colour2 (%2 allows for alternating colours along back)
		{
			colour = m_colour1;
		}
		else
		{
			colour = m_colour2;
		}

		if (i == m_segmentCount - 1) //makes the head of the snake black
		{
			colour = Color::black;
		}

		counter = 0;

		for (int y = 0; y < m_squareSize; y++) //goes through each cell in the 3x3 section and assigns it an X & Y (2 for loops allows for it to cycle through each RenderedItem, e.g. (0,0), (0, 1), (0, 2) etc)
		{
			for (int x = 0; x < m_squareSize; x++)
			{
				xPos = m_startOfSnake.X () + (i * m_squareSize) + x;
				yPos = m_startOfSnake.Y () + y;

				m_snakeSegments[ i ][ counter ] = RenderedItem ( Vector2 ( xPos, yPos ), ' ', colour ); //creates RenderedItem in m_snakeSegments w/ the correct pos, colour and character
				++counter; //acts as a "counter" for which element in the section 
			}
		}

	}
}

void introSnake::draw ()
{
	clearSection ( Vector2 ( m_centreOfScreen.X (), m_startOfSnake.Y () - m_squareSize ), Vector2 ( m_segmentCount * m_squareSize, m_squareSize * 3 ), Color::darkCyan ); //clears previously rendered cells by drawing over them
	Color colour = Color::purple; //sets default colour to purple

	for (int i = 0; i < m_segmentCount; i++)
	{
		if (i % 2 == 0) //same process as when defined, sets each alternating "segment" to an alternating colour
		{
			colour = m_colour1;
		}
		else
		{
			colour = m_colour2; //colours are redefined as they get changed between draw calls
		}
		if (i == m_segmentCount - 1)
		{
			colour = Color::black;
		}

		for (int j = 0; j < m_squareSize * m_squareSize; j++)//goes through each cell in the section,assigns it the correct colour, & calls its draw function
		{
			m_snakeSegments[ i ][ j ].setColour ( colour );
			m_snakeSegments[ i ][ j ].draw ();
		}
	}
}

void introSnake::animate ()
{
	++pos; //increases tick timer by 1 each call

	if (pos > 10) //every 10 calls it momves alternating segments up
	{

		for (int i = 0; i < m_segmentCount; i++)
		{
			for (int j = 0; j < m_squareSize * m_squareSize; j++)
			{
				if (i % 2 == static_cast<int>(alt)) //alt is a bool, changed each call to make the alternating segments bit work
				{
					m_snakeSegments[ i ][ j ].setPosition ( m_snakeSegments[ i ][ j ].getPosition () + Vector2 ( 0, 0 ) );
				}
				else
				{
					m_snakeSegments[ i ][ j ].setPosition ( m_snakeSegments[ i ][ j ].getPosition () + Vector2 ( 0, -1 ) );
				}
			}
		}

		pos = 0; //tick timer reset
		alt = !alt; //alternates value of alt


		draw (); //calls draw func
	}



	if (pos == 5)
	{
		int xPos; //local vars used to calc. position of cell
		int yPos;



		for (int i = 0; i < m_segmentCount; i++)
		{
			int counter = 0;
			for (int y = 0; y < m_squareSize; y++)
			{
				for (int x = 0; x < m_squareSize; x++) //recalculates default position of segment, middle frame of the animation
				{
					xPos = m_startOfSnake.X () + (i * m_squareSize) + x;
					yPos = m_startOfSnake.Y () + y;
					Vector2 position = Vector2 ( xPos, yPos );
					m_snakeSegments[ i ][ counter ].setPosition ( position );

					++counter;
				}
			}
		}
		draw (); //calls draw func
	}

}

void introSnake::setColour1 ( Color colour1 )
{
	m_colour1 = colour1; //sets colour1 member variable to param passed
}

void introSnake::setColour2 ( Color colour2 )
{
	m_colour2 = colour2;//sets colour2 member variable to param passed
}
