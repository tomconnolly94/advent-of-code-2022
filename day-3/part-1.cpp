#include <tuple>
#include <unordered_map>
#include <iostream>

#include "../common/fileReader.cpp"
#include "../common/intersection.cpp"

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

tuple<string, string> split_string_in_half(string input_string)
{
    int halfway = input_string.size() / 2;
    string first_half{};
    string second_half{};

    for(int char_index = 0; char_index < input_string.size(); ++char_index)
    {
        if(char_index < halfway)
            first_half += input_string[char_index];
        else
            second_half += input_string[char_index];
    }
    return tuple<string, string>(first_half, second_half);
};

int main()
{
    vector<string>* input_lines = readFileToList();
    int totalPriority = 0;

    for(auto input : *input_lines)
    {
        tuple<string, string> split_string = split_string_in_half(input);
        string first_half = get<0>(split_string);
        string second_half = get<1>(split_string);

        char common_element = intersection(first_half, second_half)[0];

        int index = ALPHABET.find(common_element);

        cout << "character: " << common_element << " has priority " << index + 1 << endl;

        if (index != std::string::npos)
            totalPriority += index + 1;
        else
            cout << "ERROR: " << common_element << " does not seem to be in the alphabet!" << std::endl;
        cout << "total priority: " << totalPriority << endl;    
    }
    cout << "Total priority count: " << totalPriority;
}