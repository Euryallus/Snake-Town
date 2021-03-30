#ifndef PARTICLE_H
#define PARTICLE_H

#include "RenderedItem.h"
#include "Vector2.h"
class ParticleSystem :
	public RenderedItem //variant of RenderedItem
{
private:
	RenderedItem m_particlePieces[ 4 ]; //stores array of 4 renderedItems (4 ""particles"")

public:
	ParticleSystem ( const Vector2 & pos, Color colour ); //takes position of centre & colour
	~ParticleSystem ();

	void draw (); //variant functions from the base draw() & erase()
	void erase ();

};

#endif //PARTICLE_H