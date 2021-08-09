#include <iostream>
#include "HighScore.h"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

HighScore::HighScore() {

}

void HighScore::AddScore(string name, int value) {
    pair<int, string> newScore;
    newScore.first = value;
    newScore.second = name;
    scoresList.push_back(newScore);
}

void HighScore::ChangeScore(string name, int value) {
    for (auto itr = scoresList.begin(); itr != scoresList.end(); ++itr) {
        if (itr->second == name) {
            itr->first += value;
        }
    }
}

void HighScore::SortScore() {
    sort(scoresList.begin(), scoresList.end(), Compare);
}

pair<int, string> HighScore::GetScore(string name)
{
    pair<int, string> result;
    for (auto itr = scoresList.begin(); itr != scoresList.end(); ++itr) {
        if (itr->second == name) {
            result.first = itr->first;
            result.second = itr->second;
        }
        else
        {
            result.first = 0;
            result.second = "null";
        }
    }
    return result;
}

void HighScore::DebugScoreList() {
    for (auto itr = scoresList.begin(); itr != scoresList.end(); ++itr) {
        cout << itr->first << '\t' << itr->second << '\n';
    }
}