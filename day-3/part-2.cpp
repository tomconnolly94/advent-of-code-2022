#include <tuple>
#include <unordered_map>
#include <iostream>

#include "../common/fileReader.cpp"
#include "../common/intersection.cpp"

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main()
{
    vector<string>* input_lines = readFileToList();
    int totalPriority = 0;
    vector<string> elfGroup;

    for(auto input : *input_lines)
    {
        cout << input << endl;
        elfGroup.push_back(input);
        if(elfGroup.size() == 3)
        {
            char common_element = vector_intersection(elfGroup);

            int index = ALPHABET.find(common_element);

            cout << "character: " << common_element << " has priority " << index + 1 << endl;

            if (index != std::string::npos)
                totalPriority += index + 1;
            else
                cout << "ERROR: " << common_element << " does not seem to be in the alphabet!" << std::endl;
            cout << "total priority: " << totalPriority << endl;
            elfGroup.clear();
        }
    }

    cout << "entries: " << (*input_lines).size() << endl;

    cout << "Total priority count: " << totalPriority;
}