#include <iostream>
#include <regex>
#include <unordered_set>
#include <unordered_map>

#include "../common/fileReader.cpp"
using namespace std;

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
    Position (&positions)[10])
{

    cout << "new movement applied: " << direction << movementMagnitude << endl;
    
    for(int movementIndex = 0; movementIndex < movementMagnitude; ++movementIndex)
    {
        Position positionModifier = positionModiiers[direction];
        positions[0].x += positionModifier.x;
        positions[0].y += positionModifier.y;

        for(int ropePositionIndex = 1; ropePositionIndex < 10; ++ropePositionIndex)
        {        
            Position leadPosition = positions[ropePositionIndex - 1];
            Position followPosition = positions[ropePositionIndex];

            cout << "Current lead pos, index: " << ropePositionIndex - 1 << " (x: " << leadPosition.x << ", y: " << leadPosition.y << ") " << endl;

            // head and tail are close enough that no repositioning is necessary
            if(abs(leadPosition.x - followPosition.x) > 1 || abs(leadPosition.y - followPosition.y) > 1)
            {
            
                if(leadPosition.x == followPosition.x) // positions are stacked vertically
                    followPosition.y += positionModifier.y;

                else if(leadPosition.y == followPosition.y) // positions are lined up horizontally
                    followPosition.x += positionModifier.x;
                else
                {
                    // diagonal
                    if(positionModifier.x == 0)
                    {
                        positionModifier.x = leadPosition.x - followPosition.x;
                        followPosition.x = leadPosition.x;
                    }
                    else
                        followPosition.x += positionModifier.x;
                    
                    if(positionModifier.y == 0)
                    {
                        positionModifier.y = leadPosition.y - followPosition.y;
                        followPosition.y = leadPosition.y;
                    }
                    else
                        followPosition.y += positionModifier.y;
                }
            }

            cout << "Current follow pos (x: " << followPosition.x << ", y: " << followPosition.y << endl << endl;

            if(ropePositionIndex == 9)
                tailVisitedPositionSet.insert(followPosition.posToString());

            positions[ropePositionIndex] = followPosition;
        }
    }
}


int main()
{
    vector<string>* inputLines = readFileToList();
    Position positions[10] = { 
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0},
        Position{0,0}
    };
    tailVisitedPositionSet.insert(positions[9].posToString());
    

    for(auto inputLine : *inputLines)
    {
        regex rgx("([A-Z]) (\\d*)");
        smatch matches;

        if(regex_search(inputLine, matches, rgx)) {

            string direction = matches[1].str();
            int magnitude = stoi(matches[2].str());

            applyMovement(direction, magnitude, positions);
        }
    }
    cout << "positions: " << tailVisitedPositionSet.size() << endl;
}