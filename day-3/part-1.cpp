#include <tuple>
#include <unordered_map>
#include <iostream>

#include "../common/fileReader.cpp"

using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

tuple <char*, char*> split_string_in_half(string input_string)
{
    int halfway = input_string.size() / 2;
    char first_half[halfway];
    char second_half[halfway];

    for(int char_index = 0; char_index < input_string.size(); ++char_index)
    {
        if(char_index < halfway)
            first_half[char_index] = input_string[char_index];
        else
            second_half[char_index % halfway] = input_string[char_index];
    }
    return tuple <char*, char*>(first_half, second_half);
};

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

int main()
{
    vector<string>* input_lines = readFileToList();
    int totalPriority = 0;

    for(auto input : *input_lines)
    {
        tuple <char*, char*> split_string = split_string_in_half(input);

        string first_half = get<0>(split_string);
        string second_half = get<1>(split_string);

        char common_element = intersection(first_half, second_half)[0];

        int index = ALPHABET.find(common_element);

        if (index != std::string::npos)
            totalPriority += index;
        else
            cout << "ERROR: " << common_element << " does not seem to be in the alphabet!" << std::endl;
    }

    cout << "Total priority count: " << totalPriority;
}