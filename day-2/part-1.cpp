#include <cstring>
#include <map>
#include <iostream>

#include "../common/fileReader.cpp"

using namespace std;

enum RPSValue
{
    Rock,
    Paper,
    Scissors
};

int score_matrix[3][3] = { 
    { 3, 0, 6 }, 
    { 6, 3, 0 }, 
    { 0, 6, 3 }
};

map<char, RPSValue> rps_value_map = {
    { 'A', Rock },
    { 'B', Paper },
    { 'C', Scissors },
    { 'X', Rock },
    { 'Y', Paper },
    { 'Z', Scissors }
};



int main()
{
    vector<string>* input = readFileToList();

    int totalScore = 0;

    for (string line : *input)
    {
        char opponents_choice = line[0];
        char my_choice = line[2];
        cout << "opponents_choice: " << opponents_choice << endl;
        cout << "my_choice: " << my_choice << endl;

        // get score from match up with opponent
        int my_score = score_matrix[rps_value_map[my_choice]][rps_value_map[opponents_choice]];
        
        cout << "my_score: " << my_score << endl; 
        // get score from my_choice
        my_score += rps_value_map[my_choice] + 1;

        totalScore += my_score;
    }

    cout << "totalScore: " << totalScore << endl;
    delete input;
}