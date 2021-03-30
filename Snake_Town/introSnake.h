#ifndef INTROSNAKE_H
#define INTROSNAKE_H

#include "RenderedItem.h"
#include "Vector2.h"

#pragma once
class introSnake
{
private:

	//data about snake needed to draw & animate
	Vector2 m_startOfSnake; //stores position of start of snake
	Vector2 m_centreOfScreen; //stores position of centre screen

	bool alt = false; //stores alternating true/false values

	RenderedItem m_snakeSegments[ 12 ][ 9 ]; //creates array of 12 9x9 segments

	int m_segmentCount = 12;
	int m_squareSize = 3;
	int pos = 0;



	Color m_colour1; //colour data 
	Color m_colour2;

public:

	introSnake (); //default constructor
	introSnake ( const Vector2 & centreOfScreen, int yOffset ); //constructor, takes screen centre position & y offset at which to draw snake (e.g. 8 would print snake 8 cells above centre point of screen)

	void draw ();
	void animate ();

	void setColour1 ( Color colour1 );
	void setColour2 ( Color colour2 );

};

#endif // !INTROSNAKE_H