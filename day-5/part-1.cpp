#include <iostream>
#include <regex>
#include <stack>

#include "../common/fileReader.cpp"

using namespace std;

int main()
{
    vector<stack<char>> stacks{};
    vector<string>* inputLinesStackStart = readFileToList("stack-start.txt");

    for(auto inputLine : *inputLinesStackStart)
    {
        stack<char> charStack{};
        for(auto character : inputLine)
        {
            charStack.push(character);
            cout << character << " ";
        }
        stacks.push_back(charStack);
        cout << endl;
    }

    vector<string>* inputLinesMoveOps = readFileToList();

    for(auto inputLine : *inputLinesMoveOps)
    {
        regex rgx("move (\\d*) from (\\d*) to (\\d*)");
        smatch matches;

        if(regex_search(inputLine, matches, rgx)) {

            int crateQuantity = stoi(matches[1].str());
            int fromStack = stoi(matches[2].str()) - 1;
            int toStack = stoi(matches[3].str()) - 1;

            cout << "move " << crateQuantity << " from " << fromStack << " to " << toStack << endl;

            for(int index = 0; index < crateQuantity; ++index)
            {
                char moveChar = stacks[fromStack].top();
                cout << "moveChar: " << moveChar << endl;
                stacks[fromStack].pop();
                stacks[toStack].push(moveChar);
            }
        }
    }

    string finalStr = "";

    for(auto crateStack : stacks)
        finalStr += crateStack.top();

    cout << finalStr << endl;
}