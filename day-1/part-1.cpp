#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string>* readFileToList()
{
    vector<string>* entries = new vector<string>{};

    string line;
    ifstream myfile;
    myfile.open("input.txt");

    if(!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    while(getline(myfile, line)) {
        entries->push_back(line);
    }
    return entries;
}

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