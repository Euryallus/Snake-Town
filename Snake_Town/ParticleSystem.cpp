#include <iostream>
#include <string>

//file reading
#include <fstream>

//console-specific

#include "RenderedItem.h"
#include "ParticleSystem.h"
#include "Vector2.h"

using namespace std;

ParticleSystem::ParticleSystem ( const Vector2 & pos, Color colour )
	: RenderedItem ( pos, '|', colour )
{
	string m_characters = "|~~|"; //creates string of characters to display (makes star shape around item)


	for (int i = 0; i < 4; i++) //for each char in the string
	{
		Vector2 position = pos; //sets central position to pos passed in params (usually position of last item eaten)

		switch (i) //creates 4 RenderedItems at top, bottom, left & right of object w/ char value of i position in m_characters string
		{
		case(0):
		{
			position = Vector2 ( pos.X () + 0, pos.Y () + 1 );
			break;
		}

		case(1):
		{
			position = Vector2 ( pos.X () + 1, pos.Y () + 0 );
			break;
		}

		case(2):
		{
			position = Vector2 ( pos.X () - 1, pos.Y () + 0 );
			break;
		}

		case(3):
		{
			position = Vector2 ( pos.X () + 0, pos.Y () - 1 );
			break;
		}
		}

		m_particlePieces[ i ] = RenderedItem ( position, m_characters.at ( i ), colour ); //creates each RenderedItem & adds it to m_particlePieces array
	}
}

ParticleSystem::~ParticleSystem () //destructor for particle system
{
}

void ParticleSystem::draw () //draws each character defined in a cross position around specified location (emulates particle)
{
	for (int i = 0; i < 4; i++)
	{
		m_particlePieces[ i ].draw ();
	}

}

void ParticleSystem::erase () //does the same as draw() but outputs " " instead of a character
{
	for (int i = 0; i < 4; i++)
	{
		m_particlePieces[ i ].erase ();
	}
}
