#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "RenderedItem.h"
#include "Snake.h"
#include "ParticleSystem.h"
#include "UIManager.h"
#include "ScoreManager.h"
#include "TimedItem.h"


class Game
{
private:

	//basic Variables needed to run game
	int m_gridY;

	int m_particleTickTime	= 0;
	int m_level				= 1;
	const int m_numberOfLevels	= 3;

	int m_updateRate = 100;

	bool m_deathScreenDisplayed = false;
	bool m_mainMenuDisplayed	= false;
	bool m_gameStarted			= false;

	string m_playerName			= "";

	//							  //
	// internal-call-only methods //
	//							  //

	void checkCollisions (); //passes object data to snake & checks for true / false response

	void renderItems (); //cycles item list and renders each item within

	void RenderParticles (); //cycles particle list & renders each one as necessary

	void renderWalls (); //cycles wall list and renders each one

	void createPickUp ( int x ); //Generates a new item based on X co-ord passed as param & game mode

	void checkScore (); //gets score from snakes & compares with score value needed to progress to next level

	void nextLevel (); //loads next level & tells the user it's being loaded

	void snakeUpdate (); //updates the snake object (either single snake or snakes in array, depending on game mode)

	void deathScreen (); //displays the "GAME OVER" screen, calls different functions from UIManager based on game mode

	void initialise (); //calls initial set-up procedures, e.g. calculates size of screen & creates manager objects

	void startPlay (); //calls methods needed to begin playing, whether it be at the start or at the beginning of a new level

	void levelDimensions ( int level ); //cycles input levels .txt file and calculates the dimensions

	void load ( int level ); //creates wall data based off input levels .txt file

	//object lists
	vector<RenderedItem> items;
	vector<RenderedItem> walls;
	vector<ParticleSystem> particles;

	//Vector2's used for calculations
	Vector2 startPosition;
	Vector2 endPosition;
	Vector2 gridDimensions;

	//Manager objects
	UIManager m_UIManager;
	ScoreManager m_scoreManager;

	//user-selected colour data
	Color m_snakeCol1;
	Color m_snakeCol2;

	TimedItem m_timedPickUp;

public:

	//public called methods
	Game ();
	void run ();

	enum class state //stores 4 possible states for the game 
	{
		MainScreen,
		Options,
		Playing,
		Dead
	};

	enum class GameMode //stores 3 possible game modes available to play 
	{
		OnePlayer,
		TwoPlayer,
		MirrorMode

	};

	state currentState = state::MainScreen; //stores current active game state

	GameMode currentMode = GameMode::OnePlayer; //stores current game mode selection

};

#endif // !GAME_H