#include "HighScores.h"
vector<tuple<string, string, int> > HighScores::readHighScoresFromFile(const string& filename)
{
    vector<tuple<string, string, int> > highScores;

    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string date, name;
            int score;
            if (iss >> date >> name >> score)
            {
                highScores.emplace_back(date,name,score);
            }
        }
        file.close();
    }

    return highScores;
}