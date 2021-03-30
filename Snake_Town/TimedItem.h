#ifndef TIMEDITEM_H
#define TIMEDITEM_H

#include "RenderedItem.h"
#include <vector>


class TimedItem 
{
private:

	Color m_colour1;
	Color m_colour2;

	Color m_currentColour;

	char m_character;

	Vector2 m_position;

	int m_lifespan;
	int m_maxLifespan;

	bool m_isSpawned = false;

	Vector2 m_screenDimensions;

	Vector2 m_wallsStartPoint;

public:

	TimedItem ();
	~TimedItem ();
	TimedItem ( const Vector2 & screenDimensions, const Vector2 & startPoint, Color colour1, Color colour2 );

	void draw ();
	void update ();
	void spawn ( std::vector<RenderedItem> & walls );

	void despawn ();

	bool returnSpawnStatus ();

	Vector2 returnPosition();


};

#endif // TIMEDITEM_H