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

int choice_matrix[3][3] = { 
    { 2, 0, 1 }, 
    { 0, 1, 2 }, 
    { 1, 2, 0 }
};

map<char, RPSValue> rps_value_map = {
    { 'A', Rock },
    { 'B', Paper },
    { 'C', Scissors }
};

map<char, int> required_result_score_map = {
    { 'X', 0 },
    { 'Y', 3 },
    { 'Z', 6 }
};

map<char, int> required_result_index_map = {
    { 'X', 0 }, // i lose
    { 'Y', 1 }, // i draw
    { 'Z', 2 }  // i win
};

int main()
{
    vector<string>* input = readFileToList();

    int totalScore = 0;

    for (string line : *input)
    {
        char opponents_choice = line[0];
        char required_result = line[2];
        cout << "opponents_choice: " << opponents_choice << endl;
        cout << "required_result: " << required_result << endl;

        // get score from match up with opponent
        int my_choice = choice_matrix[rps_value_map[opponents_choice]][required_result_index_map[required_result]];
        
        RPSValue my_choice_enum = static_cast<RPSValue>(my_choice);
        cout << "my_choice: " << my_choice << " " << my_choice_enum << endl; 
        // get score from my_choice
        int my_score = required_result_score_map[required_result] + my_choice + 1;
        
        totalScore += my_score;
    }

    cout << "totalScore: " << totalScore << endl;
}