#ifndef HIGHSCORE_HEADER
#define HIGHSCORE_HEADER

#include <iostream>
#include <map>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class HighScore {
private:
	int scoreLength = 10;
	vector<pair<int, string>> scoresList;
public:
	string currentPlayer;
	HighScore();
	void AddScore(string name, int value);
	void ChangeScore(string name, int value);
	void SortScore();
	pair<int, string> GetScore(string name);
	void DebugScoreList();
};

#endif