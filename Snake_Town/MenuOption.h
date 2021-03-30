#ifndef MENUOPTION_H
#define MENUOPTION_H

#include "Vector2.h"
#include "RenderedItem.h"
#include <string>


using namespace std;

class MenuOption
{
protected:
	Vector2 m_dimensions;
	Vector2 m_middlePoition;

	string m_text;

	Color m_selectedColour;
	Color m_deselectedColour;
	Color m_combinations[ 5 ][ 2 ];
	Color m_speedColours[ 3 ];
	Color m_currentColour;

	int m_noOfCombos = 5;
	int m_selectedCombo;
	int m_type = 0;
	int m_speed = 1;

	bool m_isSelected = false;

public:

	MenuOption (); //default constructor
	MenuOption ( const Vector2 & dimensions, const Vector2 & position, const string & text, Color onColour, Color offColour ); //constructor, takes position, size, text component & colour data

	virtual void draw (); //uses colour data & draws ""self"" to the screen
	void animate (); //used on the colour select option, alternates between 2 colours even when not selected

	void erase (); //erases ""self"" from screen by drawing over self

	//moves m_selectedCombo pointer up or down 
	void cycleLeft ();
	void cycleRight ();

	//getters & setters
	void setSelected ( bool select );
	void setSelectedColour ( Color colour );

	void increaseSpeed ();
	void decreaseSpeed ();

	int returnSpeed ();

	Color returnColour1 ();
	Color returnColour2 ();



};

#endif // MENUOPTION_H