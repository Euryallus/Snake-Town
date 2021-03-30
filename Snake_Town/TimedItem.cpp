#include "TimedItem.h"
#include <vector>
#include <windows.h>
#include "Helpers.h"

using namespace std;

TimedItem::TimedItem () //default cnstructor
{
	m_colour1 = Color::purple;
	m_colour2 = Color::cyan;

	m_character =' ';

	m_currentColour = m_colour1;

	m_position = Vector2(0,0);
	m_screenDimensions = Vector2 ( 0, 0 );
	m_wallsStartPoint = Vector2 ( 0, 0 );
	m_lifespan = 0;
	m_maxLifespan = 1000;

	m_isSpawned = false;
}

TimedItem::~TimedItem () //destructor
{
}

TimedItem::TimedItem ( const Vector2 & screenDimensions, const Vector2 & startPoint, Color colour1, Color colour2 ) //constructor, takes screen dimensions, start position of play field, colour 1 and colour 2
{
	//assigns member vars to parameters passed
	m_colour1 = colour1;
	m_colour2 = colour2;

	m_currentColour = m_colour1;

	m_character =' ';

	m_position = Vector2 ( 0, 0 );
	m_screenDimensions = screenDimensions;

	m_lifespan = 0;
	m_maxLifespan = 100;

	m_isSpawned = false;
}

void TimedItem::draw () //draws the object to the screen @ position stored using drawChar (from Helpers.h)
{
	if (m_isSpawned)
	{
		drawChar ( m_character, m_position, m_currentColour);
	}
}

void TimedItem::update ()
{
	if (m_lifespan % 10 == 0) //alternates colours every 10 calls
	{
		m_currentColour = static_cast<int> (m_currentColour) == static_cast<int> (m_colour1) ? m_colour2 : m_colour1;
		if (m_isSpawned)
		{
			Beep ( 1000, 20 );
		}
	}

	if (m_lifespan > m_maxLifespan && m_isSpawned) //checks if item has been around for longer than "maximum life" - if it has, despawn 
	{
		despawn ();
	}
	

	if(m_isSpawned) //if its's still active, increase lifespan & draw to screen
	{
		m_lifespan++;
		draw ();
	}

}

void TimedItem::spawn ( vector<RenderedItem> & wall ) 
{

	m_isSpawned = true;
	m_lifespan = 0;

	Vector2 origin = m_wallsStartPoint + Vector2 ( 2, 2 );
	Vector2 range = m_screenDimensions - Vector2 ( 2, 2 );

	m_position = origin + Vector2 ( rand () % range.X (), rand () % range.Y () ); //creates point to spawn item

	for (size_t i = 0; i < wall.size(); i++)
	{
		if (wall[ i ].getPosition () == m_position)
		{
			spawn (wall);
			break;
		}
	}

	draw ();
}

void TimedItem::despawn ()
{
	clearCell ( m_position );

	m_position = Vector2 ( 0, 0 );
	m_isSpawned = false;

}

bool TimedItem::returnSpawnStatus ()
{
	return m_isSpawned;
}

Vector2 TimedItem::returnPosition ()
{
	return m_position;
}
