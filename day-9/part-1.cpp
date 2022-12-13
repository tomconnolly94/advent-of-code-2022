#include <iostream>
#include <regex>
#include <unordered_set>
#include <unordered_map>

#include "../common/fileReader.cpp"

struct Position{
    int x;
    int y;

    string posToString(){
        return to_string(x) + to_string(y);
    }
};

Position movementModifierL = { -1, 0 };
Position movementModifierR = { 1, 0 };
Position movementModifierU = { 0, 1 };
Position movementModifierD = { 0, -1 };

map<string, Position> positionModiiers = {
    {"L", movementModifierL },
    {"R", movementModifierR },
    {"U", movementModifierU },
    {"D", movementModifierD },
};

unordered_set<string> tailVisitedPositionSet{};

void applyMovement(
    string direction,
    int movementMagnitude,
    Position& currentHeadPosition, 
    Position& currentTailPosition)
{

    cout << "new movement applied: " << direction << movementMagnitude << endl;
    
    for(int movementIndex = 0; movementIndex < movementMagnitude; ++movementIndex)
    {
        Position positionModifier = positionModiiers[direction];
        currentHeadPosition.x += positionModifier.x;
        currentHeadPosition.y += positionModifier.y;

        cout << "Current Head pos (x: " << currentHeadPosition.x << ", y: " << currentHeadPosition.y << endl;

        // head and tail are close enough that no repositioning is necessary
        if(abs(currentHeadPosition.x - currentTailPosition.x) > 1 || abs(currentHeadPosition.y - currentTailPosition.y) > 1)
        {
        
            if(currentHeadPosition.x == currentTailPosition.x) // positions are stacked vertically
                currentTailPosition.y += positionModifier.y;

            else if(currentHeadPosition.y == currentTailPosition.y) // positions are lined up horizontally
                currentTailPosition.x += positionModifier.x;
            else
            {
                // diagonal
                currentTailPosition.x = positionModifier.x == 0 ? currentHeadPosition.x : currentTailPosition.x += positionModifier.x;
                currentTailPosition.y = positionModifier.y == 0 ? currentHeadPosition.y : currentTailPosition.y += positionModifier.y;
            }
        }

        cout << "Current Tail pos (x: " << currentTailPosition.x << ", y: " << currentTailPosition.y << endl << endl;

        tailVisitedPositionSet.insert(currentTailPosition.posToString());
    }
}


int main()
{
    vector<string>* inputLines = readFileToList();
    Position headPos = { 0, 0 };
    Position tailPos = { 0, 0 };
    tailVisitedPositionSet.insert(tailPos.posToString());
    

    for(auto inputLine : *inputLines)
    {
        regex rgx("([A-Z]) (\\d*)");
        smatch matches;

        if(regex_search(inputLine, matches, rgx)) {

            string direction = matches[1].str();
            int magnitude = stoi(matches[2].str());

            applyMovement(direction, magnitude, headPos, tailPos);
        }
    }
    cout << "positions: " << tailVisitedPositionSet.size() << endl;
}