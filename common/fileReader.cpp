#include <vector>
#include <string>
#include <fstream>

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