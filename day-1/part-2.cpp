#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <queue>

#include "../common/fileReader.cpp"

using namespace std;


int main(){

    vector<string>* listEntries = readFileToList();
    int fattestElf = 0;
    int elfIndex = 0;
    int localTotal = 0;
    std::priority_queue<int> orderedCalories;


    for(auto entry : *listEntries)
    {
        if(entry.empty())
        {
            orderedCalories.push(localTotal);
            localTotal = 0;
            ++elfIndex;
        }
        else
            localTotal += stoi(entry);
    }

    int topThreeTotal = 0;

    for(int calorieIndex = 0; calorieIndex < 3; ++calorieIndex)
    {
        topThreeTotal += orderedCalories.top();
        cout << topThreeTotal << endl;
        orderedCalories.pop();
    }

    cout << "The elves carrying the most calories are carrying a combined total of " << topThreeTotal << " calories" << endl;

    delete listEntries;
}