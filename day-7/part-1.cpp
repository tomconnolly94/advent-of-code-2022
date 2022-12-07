#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>

#include "../common/fileReader.cpp"

using namespace std;

class Directory
{
    public:
        string name;
        int size;
        Directory* parent;
        vector<Directory*> children;

        Directory(string input_name, Directory* input_parent) : children{}
        {
            name = input_name;
            parent = input_parent;
            size = 0;
        }

        void increase_size(int increase)
        {
            size += increase;
            if(parent != nullptr) parent->increase_size(increase);
        }
};

int main()
{
    vector<string>* inputLines = readFileToList();
    Directory* root_directory = new Directory("/", nullptr);
    Directory* active_directory = root_directory;
    vector<Directory*> all_directories{};

    for(string inputLine : *inputLines)
    {
        // split string into parts
        std::stringstream ss(inputLine);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<std::string> tokens(begin, end);
        bool line_is_command = false;

        if(tokens[0] == "$") line_is_command = true;

        if(line_is_command)
        {
            string command = tokens[1];
            string optional_command_location = "";
            if(command == "cd")
            {
                if(tokens[2] == "..") active_directory = active_directory->parent;

                for(auto child : active_directory->children)
                {
                    if(child->name == tokens[2]) 
                        active_directory = child;
                }
            }
        }
        else
        {
            if(tokens[0] == "dir")
            {
                auto new_directory = new Directory(tokens[1], active_directory);
                all_directories.push_back(new_directory);
                active_directory->children.push_back(new_directory);
            }
            else
                active_directory->increase_size(stoi(tokens[0]));
        }
    }

    int total_directory_size = 0;

    for(auto directory : all_directories)
    {
        if(directory->size < 100000)
            total_directory_size += directory->size;
        delete directory;
    }

    cout << "total dir size of directories under 100000: " << total_directory_size << endl;


    delete inputLines;
}