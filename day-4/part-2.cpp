#include <iostream>
#include <regex>

#include "../common/fileReader.cpp"

using namespace std;

bool range_1_overlaps_with_range_2(int range_1_lower, int range_1_upper, int range_2_lower, int range_2_upper)
{
    if(range_1_lower <= range_2_lower &&
        range_1_upper >= range_2_lower
    )
        return true;
    return false;
}

int main()
{
    vector<string>* inputLines = readFileToList();
    int range_contained_count = 0;

    for(auto inputLine : *inputLines)
    {
        regex rgx("(\\d*)-(\\d*),(\\d*)-(\\d*)");
        smatch matches;

        if(regex_search(inputLine, matches, rgx)) {

            int elf1Start = stoi(matches[1].str());
            int elf1End = stoi(matches[2].str());
            int elf2Start = stoi(matches[3].str());
            int elf2End = stoi(matches[4].str());

            //cout << elf1Start << " " << elf1End << " " << elf2Start << " " << elf2End << endl;

            if(range_1_overlaps_with_range_2(elf1Start, elf1End, elf2Start, elf2End) || 
                range_1_overlaps_with_range_2(elf2Start, elf2End, elf1Start, elf1End))
                ++range_contained_count;
            
            // cout << "Total: " << range_contained_count << endl;
        }
    }
    cout << "Total: " << range_contained_count << endl;
}