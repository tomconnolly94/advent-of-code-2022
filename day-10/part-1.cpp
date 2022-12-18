#include <unordered_map>
#include <iostream>
#include <regex>

#include "../common/fileReader.cpp"

using namespace std;

int main()
{
    vector<string>* inputLines = readFileToList();
    unordered_map<int, int> interestingValueMap;


    for(auto inputLine : *inputLines)
    {
        regex rgx("([a-z]{4}) ?(-?\\d*)");
        smatch matches;

        if(regex_search(inputLine, matches, rgx)) {

            string operation = matches[1].str();
            if(matches.size() > 2)
                int value = stoi(matches[2].str());
        }
    }

}