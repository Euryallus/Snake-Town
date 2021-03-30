#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <string>
#include <fstream>
using namespace std;
class ScoreManager
{
private:

	int m_savedScore = 0;

	string m_scoreDocName;

	ifstream m_scoreFileRead; //in / out files for retrieving score data from Score.txt
	ofstream m_scoreFileWrite;

	void insertScore ( int score, int position, const string & name ); //internal call only, inserts the new high score into the stored vector & re-writes the Scores.txt file accordingly

public:
	ScoreManager ();

	void extractHighScores (); //gets score data from Score.txt file
	void compareScore ( int currentScore, const string & name ); //compares score input to data taken from score file, & adapts it should a new high score be present

	//getters & setters
	vector<int> returnScores ();
	vector<string> returnNames ();

	int returnSavedScore ();
	void setSavedScore ( int score );
};

#endif // !SCOREMANAGER_H