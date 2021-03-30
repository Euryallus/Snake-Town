#include <iostream>
#include <string>
#include <vector>

//console-specific
#include <Windows.h>

//class headers
#include "RenderedItem.h"
#include "Game.h"
#include "Snake.h"
#include "ScoreManager.h"
#include "Helpers.h"
#include "UIManager.h"
#include "Vector2.h"
#include "optionData.h"
#include "introSnake.h"
#include "MenuOption.h"


//namespace definition
using namespace std;

UIManager::UIManager () { };

UIManager::UIManager ( const Vector2 & scorePosition, const Vector2 & gridDimensions, const Vector2 & gridStartPos, const ScoreManager & score )
{

	m_scorePosition = scorePosition; //assigns member variables based on constructor input
	m_gridStartPos = gridStartPos;
	m_displayDimensions = gridDimensions;

	m_middleOfScreen = m_gridStartPos + (m_displayDimensions / 2);
	m_deathScreenDimensions = (m_displayDimensions / 2) + (m_displayDimensions / 4); //calculates dimensions of "death screen" (3/4 size of display dimensions passed in params)

	m_numberOfOptions = 5; //defines number of "options" buttons in options menu
	m_optionsPointer=0; //initialises current position of "options" selection (e.g. 0 = first option button)

	for (int i = 0; i < m_numberOfOptions; i++) //assigns each item in m_menuOptions list as a new MenuOption object, using string from m_options as the text component
	{

		m_menuOptions[ i ] = MenuOption ( Vector2 ( static_cast<int>( m_options[ 0 ].size ()) + 4, 3 ), m_middleOfScreen + Vector2 ( 0, -4 + (i * 3) ), m_options[ i ], Color::red, Color::darkCyan );

		if (i == m_optionsPointer){ //if position in array is the option that's initially selected, tell it it's selected
			m_menuOptions[ i ].setSelected ( true );
		}
	}

	m_menuOptions[ 4 ].setSelectedColour ( Color::yellow ); //set speed element's selected colour to green
}

void UIManager::updateScore ( int newScore ) //takes score passed and re-draws the score display (re-draws UI background and score text)
{
	//draws score UI box
	drawSection ( m_scorePosition - Vector2 ( 0, 1 ), Vector2 ( m_displayDimensions.X () - 2, 3 ), Color::red );
	//specifies score string
	string scoreDisplay = " Current score: " + to_string ( newScore ) + " "; //updates score text output
	//outputs said string to middle of score UI box
	drawString ( scoreDisplay, m_scorePosition, Color::red );

}

void UIManager::updateMultiplayerScore ( int scoreP1, int scoreP2 ) //same as updateScore, however takes 2 scores as input and outputs 2 strings to position calculated
{
	drawSection ( m_scorePosition - Vector2 ( 0, 1 ), Vector2 ( m_displayDimensions.X (), 3 ), Color::red );

	drawString ( "Score: " + to_string ( scoreP1 ), m_scorePosition, Color::red );
	drawString ( "Score: " + to_string ( scoreP2 ), Vector2 ( m_middleOfScreen.X () + 2, m_scorePosition.Y () ), Color::red );
}

void UIManager::drawDeathScreen ( int score)
{
	//draws the pop-up background using dimensions, origin & colour
	drawSection ( m_middleOfScreen - (m_deathScreenDimensions / 2), m_deathScreenDimensions, Color::red );

	//defines messages to output on death screen
	string deathMessage = "GAME OVER";
	string scoreMessage = "Your score was: " + to_string ( score );

	//draws top 3 saved high scores
	drawHighScores ( 3, m_scoreManager.returnScores (), m_scoreManager.returnNames (), Color::red );

	//draws messages
	drawTextCentred ( 0, -3, deathMessage, Color::red );
	drawTextCentred ( 0, 0, scoreMessage, Color::red );


}

void UIManager::drawTwoPlayerDeathScreen ( int scoreP1, int scoreP2 )
{
	//draws pop-up background using dimensions, origin and colour
	drawSection ( m_middleOfScreen - (m_deathScreenDimensions / 2), m_deathScreenDimensions, Color::red );

	//default message
	string winner = "PLAYER 1 WINS!";

	if (scoreP1 < scoreP2){ //if p2 scored higher than p1, change message to "PLAYER 2 WINS!"
		winner = "PLAYER 2 WINS!";
	}

	if (scoreP1 == scoreP2){ //if it was a tie (p1 score = p2 score), change message to "DRAW!"
		winner = "DRAW!";
	}

	drawTextCentred ( 0, -3, winner, Color::red ); //draws winner message in centre screen 

	drawTextCentred ( 0, 0, "~~ SCORES ~~", Color::red ); //draws score title and scores for each player
	drawTextCentred ( 0, 2, "Player 1: " + to_string ( scoreP1 ), Color::red );
	drawTextCentred ( 0, 4, "Player 2: " + to_string ( scoreP2 ), Color::red );
}

void UIManager::drawMirrorDeathScreen ( int score )
{
	//same setup as other score screen methods, takes a single score (combo of snake 1 + snake 2) and draws screen
	drawSection ( m_middleOfScreen - (m_deathScreenDimensions / 2), m_deathScreenDimensions, Color::red );

	drawTextCentred ( 0, -3, "GAME OVER", Color::red );
	drawTextCentred ( 0, 0, "Your score was: " + to_string ( score ), Color::red );

	drawTextCentred ( 0, 5, "TOP TIP:", Color::red );
	drawTextCentred ( 0, 7, "Check both snakes can achieve the maneuver you're trying to pull!", Color::red );
}

void UIManager::drawIntroMenu ()
{
	//draws menu background
	drawSection ( m_gridStartPos, m_displayDimensions - Vector2 ( 3, 0 ), Color::darkCyan );

	//stores title of game
	string title = "SNAKE SNAKE SNAKE TOWN!";


	drawTextCentred ( 0, -10, " _______  __    _  _______  ___   _  _______    _______  _______  _     _  __    _ ", Color::darkCyan );
	drawTextCentred ( 0, -9, "|       ||  |  | ||   _   ||   | | ||       |  |       ||       || | _ | ||  |  | |", Color::darkCyan );
	drawTextCentred ( 0, -8, "|  _____||   |_| ||  |_|  ||   |_| ||    ___|  |_     _||   _   || || || ||   |_| |", Color::darkCyan );
	drawTextCentred ( 0, -7, "| |_____ |       ||       ||      _||   |___     |   |  |  | |  ||       ||       |", Color::darkCyan );
	drawTextCentred ( 0, -6, "|_____  ||  _    ||       ||     |_ |    ___|    |   |  |  |_|  ||       ||  _    |", Color::darkCyan );
	drawTextCentred ( 0, -5, " _____| || | |   ||   _   ||    _  ||   |___     |   |  |       ||   _   || | |   |", Color::darkCyan );
	drawTextCentred ( 0, -4, "|_______||_|  |__||__| |__||___| |_||_______|    |___|  |_______||__| |__||_|  |__|", Color::darkCyan );

	//outputs title & "name: " input area
	//drawTextCentred ( 0, -4, title, Color::darkCyan );
	drawTextCentred ( -2, 0, "Name: ", Color::darkCyan );

	drawTextCentred ( 0, 20, "Developed by Hugo Bailey (2020)", Color::darkCyan );

	//draws high scores below input & title
	drawHighScores ( 3, m_scoreManager.returnScores (), m_scoreManager.returnNames (), Color::darkCyan );
}


void UIManager::drawSection ( const Vector2 & origin, const Vector2 & dimensions, Color screenColour )
{
	//takes origin (top left), size and colour of section to draw
	string filler = string ( dimensions.X (), ' ' ); //creates string of spaces = to x component of dimensions given in params

	for (int i = 0; i < dimensions.Y (); i++)//for each line to print (y size of section)
	{
		drawString ( filler, Vector2 ( origin.X (), origin.Y () + i ), screenColour ); //outputs string in colour selected and at point calculated

	}
}


void UIManager::drawTextCentred ( int xOffset, int yOffset, const std::string & outputString, Color textColour )
{
	//extension of drawText
	//calculates where cursor should be to centre text by taking the middle of the screen and taking away 1/2 the length of string to print
	drawString ( outputString, Vector2 ( m_middleOfScreen.X () - static_cast<int>((outputString.size ()) / 2) + xOffset, m_middleOfScreen.Y () + yOffset ), textColour );
}

bool UIManager::detectMenuInput () //returns true if enter key is pressed
{
	return(isKeyPressed ( VK_RETURN ));
}

bool UIManager::detectOptionsInput () //returns true if enter key is pressed AND m_optionPointer is on a mode setting (e.g. Mirror Mode can be played, Colour selection cannot)
{
	return (m_optionsPointer < 3 && isKeyPressed ( VK_RETURN ));
}

string UIManager::inputName ()
{
	string nameIn;
	string nameOut;
	//saves name input as nameIn

	getline ( std::cin, nameIn );

	//cin >> nameIn;
	//Modifies name to be first 3 letters of name 
	nameOut = nameIn.substr ( 0, 3 ); //string manipulation - gets first 3 letters of string

	return nameOut; //returns new formatted name
}

void UIManager::drawHighScores ( int yOffset, const vector<int> & scores, const vector<string> & names, Color colour )
{
	//outputs high score title message
	string highScoreMessage = "~~ SINGLE PLAYER HIGH SCORES ~~";
	drawTextCentred ( 0, yOffset, highScoreMessage, colour );

	for (int i = 0; i < 3; i++) //for the top 3 scores;
	{
		//add padding to front of score (all to 4 places, e.g. 0003, 0032, 0320, 3200)
		string filler = string ( 4 - (to_string ( scores[ i ] )).size (), '0' );
		//saves formatted score (e.g.3 to 0003)
		string score = filler + to_string ( scores[ i ] );

		//saves overall display string as score ranking, name and new modified score string
		string toDisplay = to_string ( i + 1 ) + " - " + names[ i ] + ": " + score;

		//calls drawTextCentred to draw text
		drawTextCentred ( 0, (i * 2) + yOffset + 2, toDisplay, colour );
	}
}

void UIManager::drawLevelTransition ( int level ) //draws scree-size pop-up and outputs string "Loading level " + level name (e.g. Loading level 2...")
{
	drawSection ( Vector2 ( m_gridStartPos.X (), m_gridStartPos.Y () - 3 ), Vector2 ( m_displayDimensions.X (), m_displayDimensions.Y () + 5 ), Color::darkCyan );

	drawTextCentred ( 0, 0, "Loading level " + to_string ( level ) + "...", Color::darkCyan );
}

void UIManager::clearScreen () //system("clr") was causing screen flickering, this more or less removes it
{

	drawSection ( Vector2 ( 0, 0 ), Vector2 ( 130, 54 ), Color::black );

}

void UIManager::drawOptionsMenu ()
{
	//draws menu background

	m_introSnake = introSnake (m_middleOfScreen, 15);
	m_introSnake.draw ();

	drawSection ( m_gridStartPos, m_displayDimensions - Vector2 ( 3, 0 ), Color::darkCyan );

	//stores title of game
	string title = "~~ OPTIONS ~~";

	//outputs title & "name: " input area
	drawTextCentred ( 0, -8, title, Color::darkCyan );

	for (int i = 0; i < m_numberOfOptions; i++)
	{
		m_menuOptions[ i ].draw ();
	}
}

void UIManager::optionsUpdate () //takes input for the options menu (e.g. up & down to navigate buttons, left & right to change colour / speed if on said buttons)
{
	m_colourOptionTick += 1;

	if (m_colourOptionTick > 5){ //every 5 runs of the function animate the colour select option (e.g. every 5 runs alternate between colour 2 and colour 1)
		m_menuOptions[ 3 ].animate ();
		m_colourOptionTick = 0; //resets timer
	}

	m_introSnake.setColour1 ( m_menuOptions[ 3 ].returnColour1 () );
	m_introSnake.setColour2 ( m_menuOptions[ 3 ].returnColour2 () );

	m_introSnake.animate ();

	if (isKeyPressed ( 'w' ) || isKeyPressed ( 'i' || isKeyPressed ( VK_UP ) )) //if user wants to cycle UP the list via any input method (letter keys or arrow keys)
	{


		m_menuOptions[ m_optionsPointer ].setSelected ( false ); //sets previous item to deselected mode, re-draws it as not selected
		m_menuOptions[ m_optionsPointer ].draw ();

		--m_optionsPointer; //decrements the pointer (moves one up)
		if (m_optionsPointer == -1){ //checks if pointer's at -1, essentially a circular array pointer)
			m_optionsPointer = m_numberOfOptions - 1;
		}

		m_menuOptions[ m_optionsPointer ].setSelected ( true ); //tells newly selected item that it's selected& re-draws it
		m_menuOptions[ m_optionsPointer ].draw ();
		Beep ( 1200, 100 );

	}

	if (isKeyPressed ( 's' ) || isKeyPressed ( 'k' ) || isKeyPressed ( VK_DOWN )) //same as previous but cycles DOWN the array
	{

		m_menuOptions[ m_optionsPointer ].setSelected ( false ); //deselects and re-draws prev. button
		m_menuOptions[ m_optionsPointer ].draw ();


		++m_optionsPointer; //increments option pointer
		if (m_optionsPointer == m_numberOfOptions){ //checks it's not "out of bounds"
			m_optionsPointer = 0;
		}
		Beep ( 1200, 100 );
		m_menuOptions[ m_optionsPointer ].setSelected ( true ); //draws current button as "selected"
		m_menuOptions[ m_optionsPointer ].draw ();

	}

	if ((isKeyPressed ( 'a' ) || isKeyPressed ( 'j' ) || isKeyPressed ( VK_LEFT )))
	{
		if (m_optionsPointer == 3){ //if left is pressed & user is "on" colour button, cycle left through the colour combos
			Beep ( 1200, 100 );
			m_menuOptions[ 3 ].cycleLeft ();
		}
		else if (m_optionsPointer == 4) //if left is pressed & user is "on" speed button, cycle left through speed options
		{
			Beep ( 1200, 100 );
			m_menuOptions[ 4 ].decreaseSpeed ();
		}

	}

	if ((isKeyPressed ( 'd' ) || isKeyPressed ( 'l' ) || isKeyPressed ( VK_RIGHT )))
	{
		if (m_optionsPointer == 3)//if right is pressed & user is "on" colour button, cycle right through the colour combos
		{
			Beep ( 1200, 100 );
			m_menuOptions[ 3 ].cycleRight ();
		}
		else if (m_optionsPointer == 4)//if right is pressed & user is "on" speed button, cycle right through speed options
		{
			Beep ( 1200, 100 );
			// 
			m_menuOptions[ 4 ].increaseSpeed ();
		}
	}
}

OptionData UIManager::returnOptionSelected () //creates a ""packet"" of data of type OptionData to be passed to Game
{
	OptionData optionMenuData; //Allows more than 1 piece of data to be returned from the function
	optionMenuData.snakeColour1 = m_menuOptions[ 3 ].returnColour1 ();
	optionMenuData.snakeColour2 = m_menuOptions[ 3 ].returnColour2 ();
	optionMenuData.speed = m_menuOptions[ 4 ].returnSpeed ();
	optionMenuData.optionPointer = m_optionsPointer;

	return optionMenuData;
}


