#include <iostream>
#include <string>
#include <map>

#include "../common/fileReader.cpp"

using namespace std;


const int matrixDimension = 99;
int treeHeightMatrix[matrixDimension][matrixDimension];

bool positionIsValid(int position)
{
    if(position >= 0 and position < 99)
        return true;
    return false;
}

int getDirectionScoreForPosition(int rowIndex, int colIndex, int rowJumpSize, int colJumpSize)
{
    int originalScorePosition = treeHeightMatrix[rowIndex][colIndex];
    int rowPosition = rowIndex + rowJumpSize;
    int colPosition = colIndex + colJumpSize;
    bool moving = true;
    int visibleTrees = 1;

    while(moving)
    {
        int newPositionValue = treeHeightMatrix[rowPosition][colPosition];

        rowPosition += rowJumpSize;
        colPosition += colJumpSize;

        if(newPositionValue >= originalScorePosition || !positionIsValid(rowPosition) || !positionIsValid(colPosition))
            return visibleTrees;
        ++visibleTrees;
    }
    return visibleTrees;
}

int main()
{
    vector<string>* inputLines = readFileToList();
    //vector<string>* inputLines = readFileToList("input2.txt");
    int visibleCount = 0;

    for(int rowIndex = 0; rowIndex < matrixDimension; ++rowIndex)
    {
        for(int colIndex = 0; colIndex < matrixDimension; ++colIndex)
        {
            string line = (*inputLines)[rowIndex];
            string s1 = line.substr(colIndex, 1);
            int val = stoi((s1));

            treeHeightMatrix[rowIndex][colIndex] = val;
        }
    }

    int highestScore = 0;

    for(int rowIndex = 0; rowIndex < matrixDimension; ++rowIndex)
    {
        for(int colIndex = 0; colIndex < matrixDimension; ++colIndex)
        {
            int leftScore = getDirectionScoreForPosition(rowIndex, colIndex, 0, -1);
            int rightScore = getDirectionScoreForPosition(rowIndex, colIndex, 0, 1);
            int upScore = getDirectionScoreForPosition(rowIndex, colIndex, -1, 0);
            int downScore = getDirectionScoreForPosition(rowIndex, colIndex, 1, 0);

            int score = leftScore * rightScore * upScore * downScore;

            if(score > highestScore)
            {
                highestScore = score;

                cout << "new highest score: " << highestScore << ", leftScore: " << leftScore << 
                    ", rightScore: " << rightScore <<", upScore: " << upScore <<", downScore: " << downScore << endl; 
            }
        }
    }


    cout << "highest score: " << highestScore << endl; 
}