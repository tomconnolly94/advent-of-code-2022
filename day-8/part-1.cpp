#include <iostream>
#include <string>
#include <map>

#include "../common/fileReader.cpp"

using namespace std;

enum ScanMode {
    HorizontalLtoR,
    HorizontalRtoL,
    VerticalLtoR,
    VerticalRtoL
};


bool visibleTreePositionCount[99][99]{false};

int traverse_int_arr_for_visibility_count(int input[99], bool scanningRow, int parentIndex, bool reverse)
{
    cout << "traverse_int_arr_for_visibility_count called" << endl;
    int visibleCount = 0;
    int inputLength = 99;
    int highestValue = -1;

    for (int i = 0; i < inputLength && i >= 0; ++i)
    {
        int rowIndex = scanningRow ? parentIndex : i;
        int colIndex = scanningRow ? i : parentIndex;
        rowIndex = !scanningRow && reverse ? inputLength - rowIndex - 1 : rowIndex;
        colIndex = scanningRow && reverse ? inputLength - colIndex - 1 : colIndex;

        if(input[i] > highestValue || i == 0)
        {
            highestValue = input[i];
            if(!visibleTreePositionCount[rowIndex][colIndex])
            {
                ++visibleCount;
                visibleTreePositionCount[rowIndex][colIndex] = true;
                cout << "Found new highest value: " << highestValue << " - rowIndex: " << rowIndex << ", colIndex: " << colIndex << endl;
            }
        }
    }
    return visibleCount;
}

int main()
{
    vector<string>* inputLines = readFileToList();
    //vector<string>* inputLines = readFileToList("input2.txt");
    int matrixDimension = 99;
    int treeHeightRowMatrix[matrixDimension][matrixDimension];
    int treeHeightRowMatrixReverse[matrixDimension][matrixDimension];
    int treeHeightColumnMatrix[matrixDimension][matrixDimension];
    int treeHeightColumnMatrixReverse[matrixDimension][matrixDimension];
    int visibleCount = 0;

    for(int xIndex = 0; xIndex < matrixDimension; ++xIndex)
    {
        for(int yIndex = 0; yIndex < matrixDimension; ++yIndex)
        {
            string line = (*inputLines)[xIndex];
            string s1 = line.substr(yIndex, 1);
            int val = stoi((s1));

            treeHeightRowMatrix[xIndex][yIndex] = val;
            treeHeightRowMatrixReverse[xIndex][matrixDimension - 1 - yIndex] = val;
            treeHeightColumnMatrix[yIndex][xIndex] = val;
            treeHeightColumnMatrixReverse[yIndex][matrixDimension - 1 - xIndex] = val;
        }
    }

    // iterate rows
    for(int index = 0; index < matrixDimension; ++index)
    {
        visibleCount += traverse_int_arr_for_visibility_count(treeHeightRowMatrix[index], true, index, false);
        visibleCount += traverse_int_arr_for_visibility_count(treeHeightRowMatrixReverse[index], true, index, true);
        visibleCount += traverse_int_arr_for_visibility_count(treeHeightColumnMatrix[index], false, index, false);
        visibleCount += traverse_int_arr_for_visibility_count(treeHeightColumnMatrixReverse[index], false, index, true);
        cout << "pass: " << index << " visible trees: " << visibleCount << endl;
    }

    cout << "Number of trees that are visible: " << visibleCount << endl; 
}