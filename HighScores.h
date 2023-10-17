#ifndef HIGHSCORES_H
#define HIGHSCORES_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class HighScores{
    public:
        vector<tuple<string, string, int> > readHighScoresFromFile(const string& filename);
};
#endif