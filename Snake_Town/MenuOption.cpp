#include "MenuOption.h"
#include <string.h>
#include "Helpers.h"
#include "optionData.h"

MenuOption::MenuOption () //default constructor, sets position to 0,0 and dimensions to 1,1
{
	m_dimensions =			Vector2 ( 1, 1 );
	m_middlePoition =		Vector2 ( 0, 0 );
	m_text =				"DEFAULT";

	m_selectedColour =		Color::red;
	m_deselectedColour =	Color::darkCyan;

	m_isSelected = false;
}

MenuOption::MenuOption ( const Vector2 & dimensions, const Vector2 & position, const string & text, Color onColour, Color offColour ) //constructor
{
	m_dimensions =dimensions;  //assigns member variables values passed as parameters
	m_middlePoition = position;
	m_text = text;

	m_selectedColour = onColour;
	m_deselectedColour = offColour;

	m_isSelected = false;

	//populates colour combo array w/ colour pairs (e.g. snake alternating blue and purple)
	m_combinations[ 0 ][ 0 ] = Color::blue;
	m_combinations[ 0 ][ 1 ] = Color::cyan;

	m_combinations[ 1 ][ 0 ] =Color::red;
	m_combinations[ 1 ][ 1 ] = Color::yellow;

	m_combinations[ 2 ][ 0 ] = Color::blue;
	m_combinations[ 2 ][ 1 ] = Color::purple;

	m_combinations[ 3 ][ 0 ] = Color::cyan;
	m_combinations[ 3 ][ 1 ] = Color::yellow;

	m_combinations[ 4 ][ 0 ] = Color::cyan;
	m_combinations[ 4 ][ 1 ] = Color::white;

	m_selectedCombo = 3; //sets default combo as Cyan and Yellow
	m_speed = 2; //sets default speed to 2 (medium)

	m_speedColours[ 0 ] = Color::green; //populates speed colour list w/ colours (red being fastest, green being slowest)
	m_speedColours[ 1 ] = Color::yellow;
	m_speedColours[ 2 ] = Color::red;
}

void MenuOption::draw ()
{
	//creates box to draw as "selected" highlight (e.g. changes from cyan to red when selected)
	string output = string ( m_dimensions.X (), ' ' );
	for (int i = 0; i < m_dimensions.Y (); i++) //outputs said selection box
	{
		drawString ( output, Vector2 ( m_middlePoition.X () - (m_dimensions.X () / 2), m_middlePoition.Y () + (i - 1) ), m_isSelected?m_selectedColour:m_deselectedColour );
	}
	//draws text component to centre of box
	drawString ( m_text, m_middlePoition - Vector2 ( static_cast<int>(m_text.size ()) / 2, 0 ), m_isSelected?m_selectedColour:m_deselectedColour );
}

void MenuOption::animate ()
{
	//checks current selected colour and alternates between the 2 "selected combo" colours each call
	if (static_cast<int>(m_selectedColour) == static_cast<int>(m_combinations[ m_selectedCombo ][ 0 ]))
	{
		m_selectedColour = m_combinations[ m_selectedCombo ][ 1 ];
		m_deselectedColour = m_combinations[ m_selectedCombo ][ 0 ];
	}
	else
	{
		m_selectedColour = m_combinations[ m_selectedCombo ][ 0 ];
		m_deselectedColour = m_combinations[ m_selectedCombo ][ 1 ];
	}

	draw (); //re-draws button w/ new colour
}


void MenuOption::erase () //erases self
{
	clearSection ( m_middlePoition, m_dimensions );
}

void MenuOption::setSelected ( bool select ) //toggles whether or not button is "selected" 
{
	m_isSelected = select;
}

void MenuOption::setSelectedColour ( Color colour ) //sets colour displayed when button is "selected" 
{
	m_selectedColour = colour;
}

void MenuOption::cycleLeft () //increments selected combo pointer, re-assigns selected & deselected colours according to new combo selection, and circles around array if end is reached
{
	++m_selectedCombo;

	if (m_selectedCombo == m_noOfCombos)
	{
		m_selectedCombo = 0;
	}

	m_selectedColour = m_combinations[ m_selectedCombo ][ 0 ];
	m_deselectedColour = m_combinations[ m_selectedCombo ][ 1 ];
}

void MenuOption::cycleRight ()//decrements selected combo pointer, re-assigns selected & deselected colours according to new combo selection, and circles around array if beginning is overshot (e.g. if at -1, go back round to 4)
{
	--m_selectedCombo;

	if (m_selectedCombo == -1)
	{
		m_selectedCombo = m_noOfCombos - 1;
	}

	m_selectedColour = m_combinations[ m_selectedCombo ][ 0 ];
	m_deselectedColour = m_combinations[ m_selectedCombo ][ 1 ];
}

void MenuOption::increaseSpeed () //increments speed indicator, if it over-shoots max speed (in this case 3) cycle back round to slowest
{
	++m_speed;
	if (m_speed == 4)
	{
		m_speed = 1;
	}

	m_selectedColour = m_speedColours[ m_speed - 1 ];
	draw ();
}

void MenuOption::decreaseSpeed ()//decrements speed indicator, if it reaches below minimum (in this case 0), cycle back round to highest value
{
	--m_speed;
	if (m_speed == 0)
	{
		m_speed = 3;
	}

	m_selectedColour = m_speedColours[ m_speed - 1 ];
	draw ();
}

Color MenuOption::returnColour1 () //returns colour 1 from selected colour combo
{
	return m_combinations[ m_selectedCombo ][ 0 ];
}

Color MenuOption::returnColour2 ()//returns colour 2 from selected colour combo
{
	return m_combinations[ m_selectedCombo ][ 1 ];
}

int MenuOption::returnSpeed () //returns speed pointer
{
	return m_speed;
}




