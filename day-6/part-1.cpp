#include <iostream>
#include <unordered_set>

#include "../common/fileReader.cpp"

using namespace std;

int main()
{
    string inputLine = (*readFileToList())[0];

    for(int charIndex = 0; charIndex < inputLine.size() - 3; ++charIndex)
    {
        unordered_set<char> charSet{};
        charSet.insert(inputLine[charIndex]);
        charSet.insert(inputLine[charIndex + 1]);
        charSet.insert(inputLine[charIndex + 2]);
        charSet.insert(inputLine[charIndex + 3]);

        if(charSet.size() == 4)
        {
            cout << "marker found after character: " << charIndex + 4 << endl;
            return 0;
        }
    }
    cout << "No marker found" << endl;
}