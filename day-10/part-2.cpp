#include <unordered_map>
#include <iostream>
#include <regex>

#include "../common/fileReader.cpp"

using namespace std;


int cycleCount = 0;
int registerTotal = 0;
int registerValue = 1;
int interestingCycleCounts[] = { 20, 60, 100, 140, 180, 220 };
string crtOutput = "";

void checkAndIncreaseCycleCount(int registerValueIncrease = 0)
{
    int adjustedCycleCount = cycleCount % 40;
    if(adjustedCycleCount == 0 && cycleCount != 0)
        crtOutput += "\n";

    crtOutput += adjustedCycleCount >= registerValue - 1 && adjustedCycleCount <= registerValue + 1 ? "#" : ".";

    cout << endl << crtOutput << endl;
    
    ++cycleCount;

    cout << "cycleCount bumped to: " << cycleCount << endl;

    int itemCount = sizeof(interestingCycleCounts) / sizeof(*interestingCycleCounts);
    if(std::find(interestingCycleCounts, interestingCycleCounts + itemCount, cycleCount) != interestingCycleCounts + itemCount) 
    {
        registerTotal += cycleCount * registerValue;
        cout << endl << "total: " << registerTotal << " after adding: " << registerValue << endl << endl;
    }

    registerValue += registerValueIncrease;
    if(registerValueIncrease != 0)
        cout << "registerValue: " << registerValue << " after adding: " << registerValueIncrease << endl;

}

int main()
{
    vector<string>* inputLines = readFileToList();
    unordered_map<int, int> interestingValueMap;

    for(auto inputLine : *inputLines)
    {
        regex rgx("([a-z]{4}) ?(-?\\d*)");
        smatch matches;

        if(!regex_search(inputLine, matches, rgx)) exit(2); // valid operation not found on this line

        string operation = matches[1].str();
        int value = 0;
        if(matches[2].str() != "")
            value = stoi(matches[2].str());
            
        checkAndIncreaseCycleCount();

        if(operation == "noop")
            continue;
        else if(operation == "addx")
        {
            checkAndIncreaseCycleCount(value);
        }
    }
    cout << "total: " << registerTotal << endl;
}