#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// finds all chars that are common between the two provided strings
vector<char> intersection(string str1, string str2)
{
    unordered_map<char, int> mp1, mp2;
    vector<char> res;
    for (auto x : str1)
        mp1[x]++;
    for (auto x : str2)
        mp2[x]++;
    for (auto x : mp1) {
        int cnt = 0;
        cnt = min(x.second, mp2[x.first]);
        if (cnt > 0)
            res.push_back(x.first);
    }
    return res;
};

// finds all chars that are common between each item in the vector of strings
char vector_intersection(vector<string> inputEntries)
{
    vector<char> res;
    string firstInputEntry = inputEntries[0];

    for(char character : firstInputEntry)
    {
        bool character_found_in_all_strings = true;
        for (int inputEntryIndex = 1; inputEntryIndex < inputEntries.size(); ++inputEntryIndex)
        {
            string inputEntry = inputEntries[inputEntryIndex];

            int index = inputEntry.find(character);

            if (index != std::string::npos)
                continue;
            else
            {
                character_found_in_all_strings = false;
                break;
            }
        }
        if(character_found_in_all_strings) return character;
    }

    cout << "ERROR: there does not seem to be common characters in the elfGroup" << std::endl;

    return '#';
};