#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include <vector>
#include "ScoreManager.h"
#include "MenuOption.h"
#include "optionData.h"
#include "introSnake.h"


using namespace std;

class UIManager
{
private:

	//Vector2's used for calculations later down the line
	Vector2 m_scorePosition;
	Vector2 m_gridStartPos;
	Vector2 m_middleOfScreen;

	Vector2 m_displayDimensions;

	//array of MenuOptions of size 5
	MenuOption m_menuOptions[ 5 ];

	//Array of text components needed for each menu option
	string m_options[ 5 ] ={ "SINGLE PLAYER", "MULTIPLAYER", "MIRROR MODE", "< COLOUR >", "< SPEED >" };
	int m_optionsPointer=0; //currently selected menu option
	int m_numberOfOptions = 5;
	Vector2 m_deathScreenDimensions; //desired dimensions of game over screen

	int m_colourOptionTick = 0;

	Color m_colour = Color::red;

	ScoreManager m_scoreManager; //score manager object

	introSnake m_introSnake; //snake displayed in options menu

public:
	//constructors

	UIManager ( const Vector2 & scorePosition, const Vector2 & gridDimensions, const Vector2 & gridStartPos, const ScoreManager & score );
	UIManager ();
	void updateScore ( int newScore ); //takes input from Game.cpp and updates score UI elements accordingly

	void updateMultiplayerScore ( int scoreP1, int scoreP2 ); //same as UpdateScore, but 

	void drawDeathScreen ( int score); //draws single player Game Over screen

	void drawTwoPlayerDeathScreen ( int scoreP1, int scoreP2 ); //draws 2 player Game Over screen

	void drawMirrorDeathScreen ( int score ); //draws mirror mode game Over screen

	void drawIntroMenu (); //draws initial title screen

	void drawSection ( const Vector2 & origin, const Vector2 & dimensions, Color screenColour ); //draws a box of size defined from point defined (e.g. draw a 10x10 square at 0,0 of colour red)

	void drawTextCentred ( int xOffset, int yOffset, const std::string & outputString, Color textColour ); //takes text input, calculates x offset from centre text must start at to make it seem centered

	void drawHighScores ( int yOffset, const vector<int> & scores, const vector<string> & names, Color colour ); //outputs highscore data from score manager

	void drawLevelTransition ( int level ); //draws full screen overlay between levels

	void clearScreen (); //outputs blank characters on each line of the screen, essentially "clearing" it
	void drawOptionsMenu (); //draws background & elements for the option menu to work
	void optionsUpdate (); //runs each update while options menu is active

	OptionData returnOptionSelected (); //returns packet of data containing all user selections from options menu

	bool detectMenuInput (); //detects enter key being pressed (returns true)
	bool detectOptionsInput (); //detects enter key being pressed on playable options (e.g. returns yes if entered on "Single Player" option, but false if entered on "colour" option)
	string inputName (); //reads user name from console and outputs it 

};


#endif UIMANAGER_H
