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
        int num_distinct_chars = 14;

        for(int distinct_char_index = 0; distinct_char_index < num_distinct_chars; ++distinct_char_index)
            charSet.insert(inputLine[charIndex + distinct_char_index]);

        if(charSet.size() == num_distinct_chars)
        {
            cout << "marker found after character: " << charIndex + num_distinct_chars << endl;
            return 0;
        }
    }
    cout << "No marker found" << endl;
}