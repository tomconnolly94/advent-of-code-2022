#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../common/fileReader.cpp"

using namespace std;

int main(){

    vector<string>* listEntries = readFileToList();
    int maxTotal = 0;
    int fattestElf = 0;
    int elfIndex = 0;
    int localTotal = 0;

    for(auto entry : *listEntries)
    {
        if(entry.empty())
        {
            if(localTotal > maxTotal)
            {
                maxTotal = localTotal;
                fattestElf = elfIndex;
            }

            cout << "Elf at " << elfIndex << " is carrying " << localTotal << " calories" << endl;

            localTotal = 0;
            ++elfIndex;
        }
        else
            localTotal += stoi(entry);
    }

    cout << "Elf with most calories is at index " << fattestElf << " with " << maxTotal << " calories" << endl;
    delete listEntries;
}