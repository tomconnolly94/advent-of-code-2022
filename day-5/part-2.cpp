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
            vector<char> cratesToBeMoved{};

            cout << "move " << crateQuantity << " from " << fromStack << " to " << toStack << endl;

            // pop old crates onto the crane
            for(int index = 0; index < crateQuantity; ++index)
            {
                cratesToBeMoved.push_back(stacks[fromStack].top());
                cout << "pop: " << stacks[fromStack].top() << endl;
                stacks[fromStack].pop();
            }
            
            std::reverse(cratesToBeMoved.begin(), cratesToBeMoved.end());

            // push crates to the new stack
            for(int index = 0; index < cratesToBeMoved.size(); ++index)
            {
                cout << "push: " << cratesToBeMoved[index] << endl;
                stacks[toStack].push(cratesToBeMoved[index]);
            }
        }
    }

    string finalStr = "";

    for(auto crateStack : stacks)
        finalStr += crateStack.top();

    cout << finalStr << endl;
}