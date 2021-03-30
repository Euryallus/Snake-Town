#include <iostream>
#include <string>
#include <vector>

//file reading
#include <fstream>

//console-specific
#include <Windows.h>
#include <Wincon.h>
#include <conio.h>

//class headers
#include "RenderedItem.h"
#include "Game.h"
#include "Snake.h"

#include "UIManager.h"
#include "ScoreManager.h"

//namespace definition
using namespace std;

vector<int> m_scores;
vector<string> m_names;

ScoreManager::ScoreManager ()
{
	//saves name of score document
	m_scoreDocName = "Score.txt";
}

void ScoreManager::extractHighScores ()
{

	//opens score doc in read mode (ifstream)
	m_scoreFileRead.open ( m_scoreDocName );

	if (m_scoreFileRead.is_open ()){ //checks file was opened correctly


		for (int i = 0; i < 3; i++) //for the first 3 lines in the file;
		{
			string line;
			getline ( m_scoreFileRead, line ); //output line and store as "line"

			string score = "";
			string name = "";

			for (size_t j = 0; j < line.size (); j++) //for each character in the line
			{
				if (isdigit ( line.at ( j ) )) //if it's a digit
				{
					score = score + line.at ( j ); //add it to the score string (e.g. "1" + "2" = "12")
				}

				else if (!isdigit ( line.at ( j ) ) && line.at ( j ) != '&')
				{
					name = name + line.at ( j ); //if the character isn't a digit and isn't an "&" sign, add to "name"
				}
			}
			m_scores.push_back ( std::stoi ( score ) ); //adds the integer conversion of "score" (e.g. "123" becomes 123) onto scores array
			m_names.push_back ( name ); //adds the name extracted to the back of name array
		}
	}

	m_scoreFileRead.close (); //closes the file once operation is complete
}

void ScoreManager::compareScore ( int currentScore, const string & name ) //takes the score achieved and the name stored for the player as params
{
	int pos = 4; //sets pos as a high default value that's unachievable in the for loop below
	for (int i = 0; i < 3; i++) //for each element in scores
	{
		if (currentScore >= m_scores[ i ]) //going from highest to lowest score, if the score being passed is bigger than the score saved there, it's a new top 3 score
		{
			pos = i; //saves the position found as Pos
			i = 4; //sets i to 4 so it doesn't repeat the for loop
		}
	}

	if (pos != 4) //if pos has changed, a new top 3 high score has been found
	{
		insertScore ( currentScore, pos, name ); //insert currentScore into the scores array at pos

	}
}

void ScoreManager::insertScore ( int score, int position, const string & name )
{
	//stores params as new local variables to keep everything clean
	string nameToAdd = name;
	int scoreToAdd = score;
	int positionToAdd = position;

	m_names.insert ( m_names.begin () + positionToAdd, nameToAdd ); //inserts name of player into the names array at the position of new high score
	m_scores.insert ( m_scores.begin () + positionToAdd, scoreToAdd ); //inserts score at position of new high score

	m_names.pop_back (); //removes last elements of the arrays to keep it to top 3 scores
	m_scores.pop_back ();

	m_scoreFileWrite.open ( m_scoreDocName, std::ofstream::out ); //type ofstream
	m_scoreFileWrite.clear (); //clears file


	if (m_scoreFileWrite.is_open ())
	{
		for (int i = 0; i < 3; i++) //cycles each item in high score list
		{
			string filler = string ( 4 - to_string ( m_scores[ i ] ).size (), '0' ); //formats so 8 characters in total (4 numbers (0001), '&' and name)
			string scoreWrite =  filler + to_string ( m_scores[ i ] ); //creates score string from filler & score
			string output = scoreWrite + '&' + m_names[ i ] + "\n"; //creates full line

			m_scoreFileWrite << output; //outputs to file
		}
		m_scoreFileWrite.seekp ( 0 ); //resets pointer to start of file (character 0)

	}

	m_scoreFileWrite.close (); //closes file

}

vector<int> ScoreManager::returnScores () //outputs array of scores
{
	return m_scores;
}

vector<string> ScoreManager::returnNames () //outputs array of names
{
	return m_names;
}

int ScoreManager::returnSavedScore ()
{
	return m_savedScore;
}

void ScoreManager::setSavedScore ( int score )
{
	m_savedScore = score;
}
