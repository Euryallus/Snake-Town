#include <iostream>
#include <string>
#include <vector>

//file reading
#include <fstream>

//console-specific
#include <Windows.h>
#include <time.h>

//class headers
#include "RenderedItem.h"
#include "Game.h"
#include "Snake.h"
#include "ParticleSystem.h"
#include "ScoreManager.h"
#include "Helpers.h"

#include "Audio.h"


//namespace definition
using namespace std;

Snake snake;
Snake snakes[ 2 ];

//constructor
Game::Game () //constructor 
{


	levelDimensions ( 1 ); //saves initial level dimensions to use for drawing the intro and option menu
	system ( "MODE 130, 54 " ); //sets size of console window
	
	LPCWSTR consoleName = TEXT ( "Snake Town!" );

	SetConsoleTitle (consoleName);

	m_gridY = 0;

	m_updateRate = 75; //sets rate of update for game (sleep(___) between update calls)
	m_level = 1; //sets initial level to 1

	currentMode = GameMode::OnePlayer; //sets default game mode to 1 player


}

void Game::levelDimensions ( int level ) //gets level dimensions from level file (e.g. level1.txt)
{
	string levelName = "level" + to_string ( level ) + ".txt"; //creates name of file from level input

	if (currentMode == GameMode::TwoPlayer) //if in 2 player mode, set level to default name "Multiplayer.txt"
	{
		levelName = "Multiplayer.txt";
	}

	ifstream levelFile; //opens file in read mode, goes through each line and increases "lines" count
	string line;
	int lines = 0;
	levelFile.open ( levelName, ios::out );

	while (getline ( levelFile, line )){
		++lines;
	}
	levelFile.close ();

	m_gridY = lines; //saves Y dimension of file
}

//extracts data from .txt file and stores it in arrays defined above
void Game::load ( int level )
{
	levelDimensions ( level ); //gets level dimensions

	walls ={};
	string fileToOpen = "level" + to_string ( level ) + ".txt";

	if (currentMode == GameMode::TwoPlayer || currentMode == GameMode::MirrorMode) //sets name of file to "Multiplayer.txt" if in 2 player or mirror mode
	{
		fileToOpen = "Multiplayer.txt";
	}
	//creates file name from level to open


	//defines level file
	ifstream levelFile;

	string line;

	//opens level file in read
	levelFile.open ( fileToOpen, ios::out );
	int gridX = 0;

	//cycles each line of the open file
	if (levelFile.is_open ())
	{

		for (int i = 0; i < m_gridY; i++)
		{
			//saves line data in 'line'
			getline ( levelFile, line );
			//cycles each character in the line
			for (size_t j = 0; j < line.size (); j++)
			{

				//if char is an = sign, it's a wall - creates new renderedItem obj with co-ords corresponding to position in level
				if (line.at ( j ) == '=') {
					walls.push_back ( RenderedItem ( Vector2 ( static_cast<int>(j), i ), ' ', Color::cyan ) );
				}

			}

		}
	}
	//closes file once operations are finished
	levelFile.close ();

	//set the position of the 1st wall piece (top left) & last wall piece (bottom right)
	startPosition = Vector2 ( walls[ 0 ].getPosition () );
	endPosition = Vector2 ( walls[ walls.size () - 1 ].getPosition () );

	//sets size of grid

	gridDimensions = Vector2 ( endPosition - startPosition );
}

void Game::checkCollisions ()
{
	//checks collisions by sending arrays of walls & items to snake

	switch (currentMode)
	{
	case Game::GameMode::OnePlayer: //if one player, use variable "snake"

		snake.detectWalls ( walls );

		break;

	case  GameMode::MirrorMode: //if in mirror or 2 player mode, use the array of snakes
	case Game::GameMode::TwoPlayer:

		for (int j = 0; j < 2; j++)
		{
			snakes[ j ].detectWalls ( walls );
		}
		break;

	default:
		break;
	}



	if (items.size () != 0)  //if items exist: check collisions
	{
		//pos is set as a default to 300 - it will
		int pos = 300;

		switch (currentMode)
		{
		case Game::GameMode::OnePlayer:
			pos = snake.detectItems ( items );

			if (pos != 300)
			{
				//when pick-up is collected, remove it from list, create a new one
				particles.push_back ( ParticleSystem ( items[ pos ].getPosition (), Color::whiteBlank ) );

				items[ pos ].~RenderedItem ();
				items.erase ( items.begin () + pos );

				Audio::playSoundClip (Audio::Sounds::pickUp, false );
				createPickUp ( 0 );
			}

			if (snake.detectTimedItem ( m_timedPickUp ))
			{
				m_timedPickUp.despawn ();
				particles.push_back ( ParticleSystem ( m_timedPickUp.returnPosition (), Color::red ) );
				Audio::playSoundClip ( Audio::Sounds::timedPickUp, false );
			}

			break;
		case GameMode::MirrorMode:
		case Game::GameMode::TwoPlayer:

			for (int j = 0; j < 2; j++)
			{
				pos = snakes[ j ].detectItems ( items );

				if (pos != 300)
				{
					//when pick-up is collected, remove it from list, create a new one
					particles.push_back ( ParticleSystem ( items[ pos ].getPosition (), Color::white ) );
					createPickUp ( items[ pos ].getPosition ().X () );
					Audio::playSoundClip ( Audio::Sounds::pickUp, false );
					items[ pos ].~RenderedItem ();
					items.erase ( items.begin () + pos );

				}

				if (snakes[ j ].detectTimedItem ( m_timedPickUp ))
				{
					m_timedPickUp.despawn ();
					particles.push_back ( ParticleSystem ( m_timedPickUp.returnPosition (), Color::red ) );
					Audio::playSoundClip ( Audio::Sounds::timedPickUp, false );
				}
			}

			break;

		default:
			break;
		}


	}

	switch (currentMode) //checks death state from snake / snakes
	{
	case Game::GameMode::OnePlayer:
		if (snake.returnAlive () == false)
		{
			currentState = state::Dead; //if 1 player, just check single snake var
		}

		break;

	case GameMode::MirrorMode:
	case Game::GameMode::TwoPlayer: //if in game mode w/ 2 snakes, use array of snakes

		for (int j = 0; j < 2; j++)
		{
			if (snakes[ j ].returnAlive () == false)
			{
				currentState = state::Dead;
			}
		}

		break;

	default:
		break;
	}


}


//main loop
void Game::run ()
{
	//initialises wall renders
	initialise ();

	//continuously clears and re-renders walls & items
	while (true) {

		switch (currentState) //runs different Update methods based on game mode
		{
		case(state::MainScreen): //main menu update 
		{
			if (!m_mainMenuDisplayed){ //runs on first call of main menu (draws menu)
				Audio::playSoundClip ( Audio::Sounds::menuMusic, true );
				m_UIManager.drawIntroMenu ();
				m_mainMenuDisplayed = true;

			}


			goTo ( (gridDimensions / 2) + startPosition + Vector2 ( 2, 0 ) );
			m_playerName = m_UIManager.inputName (); //takes name input

			if (m_UIManager.detectMenuInput ()){ //if enter key is pressed, change state to Options & reset menu displayed bool

				currentState = state::Options;
				m_mainMenuDisplayed = false;
			}

			break;
		}

		case(state::Options): //options menu update
			m_updateRate = 50; //sets update rate to 50

			if (!m_mainMenuDisplayed) //runs on initial call of option state (draws options menu)
			{
				m_UIManager.drawOptionsMenu ();


				Sleep ( 300 );

			}


			m_mainMenuDisplayed = true; //sets display bool to true (stops menu from being drawn multiple times)

			m_UIManager.optionsUpdate (); //allows options navigation to run

			if (m_UIManager.detectOptionsInput ()) //if enter key is detected on play-mode option, continue to play mode
			{
				const OptionData data = m_UIManager.returnOptionSelected (); // takes options selected from UI manager

				m_snakeCol1 = data.snakeColour1;
				m_snakeCol2 = data.snakeColour2;
				m_updateRate = (100 / data.speed); //assigns variables selected to be used later in program

				currentMode = (GameMode)data.optionPointer; //assigns game mode to game mode selected

				currentState = state::Playing; //sets game mode to Playing
				m_mainMenuDisplayed = false;
			}
			break;


		case(state::Playing): //"playing" update methods called
		{
			if (!m_gameStarted) //runs on first call of "playing" state
			{
				Audio::stopAudio ();
				m_gameStarted = true;
				if (m_level == 1){ //if initial level is being loaded, run initial method (defines snake, creates first item etc)
					startPlay ();
					
				}

			}

			if (!m_timedPickUp.returnSpawnStatus () && (rand () % 1000) == 1) //0.1% chance each update that it attempts to spawn a timed item
			{
				Audio::playSoundClip ( Audio::Sounds::timedSpawn, false ); //plays spawn sound effect
				m_timedPickUp.spawn ( walls ); //sets location (walls passed to allow it to check it doesn't spawn inside one)
			}

			snakeUpdate (); //updates snake according to play state

			renderItems (); //renders all ""items"" within scene
			renderWalls ();
			RenderParticles ();

			checkCollisions (); //passes item & wall data to snake

			m_timedPickUp.update ();


			if (currentMode == GameMode::OnePlayer){ //checks score against saved high-scores 
				checkScore ();
			}

			break;
		}

		case(state::Dead): //dead update methods
		{
			if (!m_deathScreenDisplayed) //runs on initial call of "Dead" mode update
			{
				deathScreen (); //draws death screen (depends on play mode)

				m_deathScreenDisplayed = true; //outputs sound
				m_gameStarted = false;
				Audio::playSoundClip ( Audio::Sounds::death, false );
			}

			if (m_UIManager.detectMenuInput ()) //if enter input is detected
			{
				switch (currentMode)
				{
				case Game::GameMode::OnePlayer: //if single player, destruct snake
					snake.~Snake ();
					break;

				case Game::GameMode::TwoPlayer:
				case Game::GameMode::MirrorMode: //if more than 1 snake exists, destruct items in snakes array
					for (int i = 0; i < 2; i++)
					{
						snakes[ i ].~Snake ();
					}

					break;

				}

				m_deathScreenDisplayed = false;
				currentState = state::Options; //set state to "Options"
				Audio::playSoundClip ( Audio::Sounds::menuMusic, true );
				m_level = 1; //reset level in
				startPlay ();
			}
		}
		}

		Sleep ( m_updateRate ); //sleeps for rate pre-determined
	}
}

void Game::initialise () //loads initial level, initialises scoreManager & UIManager items
{
	load ( 1 ); //loads level 1 for real this time


	m_scoreManager = ScoreManager ();
	m_scoreManager.extractHighScores ();

	

	m_UIManager = UIManager ( startPosition + Vector2 ( 0, -2 ), gridDimensions + Vector2 ( 3, 0 ), startPosition, m_scoreManager );

}

void Game::startPlay ()
{
	srand ( static_cast<int>(time ( NULL ) )); //""randomises"" random numbers

	m_UIManager.clearScreen (); //clears screen

	items ={ }; //resets items & particles vectors back to 0 length
	particles ={};

	load ( m_level ); //loads level defined



	switch (currentMode) //initialises snake to position 
	{
	case Game::GameMode::OnePlayer:

		snake = Snake ( startPosition + Vector2 ( 10, 10 ), m_snakeCol1, m_snakeCol2, ' ' ); //initialises snake
		createPickUp ( 0 ); //creates initial pick-up
		break;

	case Game::GameMode::TwoPlayer: //initialises snake & creates pick-up for 
		snakes[ 0 ] =Snake ( startPosition + Vector2 ( 9, 10 ), m_snakeCol1, m_snakeCol2, ' ' );

		createPickUp ( startPosition.X () + 10 ); //creates item & passes x position as param

		snakes[ 1 ] = Snake ( startPosition + Vector2 ( gridDimensions.X () / 2 + 10, 10 ), m_snakeCol2, m_snakeCol1, ' ' ); //creates 2nd snake
		createPickUp ( startPosition.X () + 10 + (gridDimensions.X () / 2) ); //creates item & passes x pos as param
		snakes[ 1 ].setInputMode ( 1 ); //sets input method for 2nd snake at 

		break;

	case GameMode::MirrorMode: //same snake position as 2 player but only 1 item initialised
		snakes[ 0 ] =Snake ( startPosition + Vector2 ( 10, 10 ), m_snakeCol1, m_snakeCol2, ' ' );

		createPickUp ( 0 );

		snakes[ 1 ] = Snake ( startPosition + Vector2 ( gridDimensions.X () / 2 + 10, 10 ), m_snakeCol2, m_snakeCol1, ' ' );

		snakes[ 1 ].setInputMode ( 2 );
		break;
	}
	m_timedPickUp.~TimedItem ();
	m_timedPickUp = TimedItem ( gridDimensions, startPosition, Color::red, Color::purple );

}

//cycles each item and calls its draw function
void Game::renderItems () {
	for (size_t i = 0; i < items.size (); i++)
	{
		items[ i ].draw ();
	}


}

void Game::RenderParticles () //renders particles
{
	if (particles.size () != 0){ //checks if particles exist
		++m_particleTickTime; //increases no. of updates particles have been "alive"

		if (m_particleTickTime > 3){ //if around for more than 3 ""ticks"", delete & erase all particles
			for (size_t i = 0; i < particles.size (); i++)
			{
				particles[ i ].erase ();
				particles[ i ].~ParticleSystem ();
				particles.pop_back ();
			}

			m_particleTickTime = 0;
		}

		for (size_t i = 0; i < particles.size (); i++) //if not over 3 ticks old, draw particles
		{
			particles[ i ].draw ();
		}
	}
}

void Game::renderWalls () { //cycles each wall and calls draw function

	for (size_t i = 0; i < walls.size (); i++)
	{
		walls[ i ].draw ();
	}
}


void Game::createPickUp ( int x )
{
	//x indicates which side of the board the collected pick-up was on

	 //prompts "new" random values to be generated

	Vector2 origin = startPosition + Vector2 ( 2, 2 );
	Vector2 range = gridDimensions - Vector2 ( 2, 2 );

	//int rangeX = m_xsize - 2;
	//int rangeY = m_ysize - 2;

	if (currentMode == GameMode::TwoPlayer) //creates new item depending on game mode (2 player -> create new item on side of screen passed via param)
	{
		range.X ( (gridDimensions.X () - 2) / 2 );

		if (x > startPosition.X () + range.X ()) //sets range & start pos depending on "side" of screen that needs item created
		{
			origin.X ( origin.X () + (gridDimensions.X () / 2) );
		}
	}

	Vector2 pos = origin + Vector2 ( rand () % range.X (), rand () % range.Y () ); //creates point to spawn item


	for (size_t i = 0; i < walls.size (); i++) //checks item won't be spawned inside walls
	{
		if (walls[ i ].getPosition ().X () == pos.X () && walls[ i ].getPosition ().Y () == pos.Y ()){
			createPickUp ( x );
			break;
		}
	}

	items.push_back ( RenderedItem ( pos, ' ', Color::white ) ); //pushes back new item in position created

}

void Game::checkScore ()
{
	if (snake.returnScore () > 200 * (m_level * 2) && m_level < m_numberOfLevels) //checks if score is over 200 * (level * 2) (400 for lvl 1-2, 800 for lvl 2-3 etc) & there is another level to go to
	{
		nextLevel ();
	}
}

void Game::nextLevel ()
{
	walls ={}; //resets walls array
	m_scoreManager.setSavedScore ( snake.returnScore () ); //gives score to score manager to hold onto while snake is destroyed & re-initialized
	m_gameStarted = false;
	++m_level; //increases level
	//load ( m_level );

	m_UIManager.drawLevelTransition ( m_level ); // draws level transition
	Sleep ( 3000 ); //waits for 3 seconds

	startPlay (); //begins play

	snake.setScore ( m_scoreManager.returnSavedScore () ); //passes score back to snake (stored locally)
}

void Game::snakeUpdate ()
{

	switch (currentMode)
	{
	case(GameMode::OnePlayer): //in 1 player mode, update score display & run snake's update func.
		m_UIManager.updateScore ( snake.returnScore () );
		snake.update ();

		break;

	case(GameMode::TwoPlayer): //in 2 person mode, update 2 player score & run each snake's update accordingly

		for (int i = 0; i < 2; i++)
		{
			snakes[ i ].update ();

		}
		m_UIManager.updateMultiplayerScore ( snakes[ 0 ].returnScore (), snakes[ 1 ].returnScore () );
		break;

	case(GameMode::MirrorMode): //updates 1st snake, takes input and gives to 2nd snake (to copy movement exactly)

		snakes[ 0 ].update ();
		snakes[ 1 ].setDirection ( snakes[ 0 ].getDirection () );
		snakes[ 1 ].update ();

		m_UIManager.updateScore ( snakes[ 0 ].returnScore () + snakes[ 1 ].returnScore () ); //updates score
		break;
	}
}


void Game::deathScreen ()
{
	switch (currentMode)
	{
	case Game::GameMode::OnePlayer: //displays single player death screen & updates scoreManager (handles high score, position in leaderboard etc.)

		m_scoreManager.compareScore ( snake.returnScore (), m_playerName );
		m_UIManager.drawDeathScreen ( snake.returnScore () );

		break;

	case Game::GameMode::TwoPlayer: //draws 2 player death screen specifically
		m_UIManager.drawTwoPlayerDeathScreen ( snakes[ 0 ].returnScore (), snakes[ 1 ].returnScore () );
		break;

	case Game::GameMode::MirrorMode: //draws mirror mode death screen
		m_UIManager.drawMirrorDeathScreen ( snakes[ 0 ].returnScore () + snakes[ 1 ].returnScore () );
		break;

	default:
		break;
	}

}


