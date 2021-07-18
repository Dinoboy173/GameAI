#include <iostream>
#include <vector>
//

void PrintMatrix(const std::vector<std::vector<int>> &mat)
{
    int col = mat.size();
    int row = mat[0].size();

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            std::cout << mat[i][j];
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

std::vector<std::vector<int>> TransposeMatrix(const std::vector<std::vector<int>> &mat)
{
    int col = mat.size();
    int row = mat[0].size();
    std::vector<std::vector<int>> newMat;

    newMat.resize(row);

    for (int i = 0; i < row; i++)
    {
        newMat[i].resize(col);

        for (int j = 0; j < col; j++)
        {
            newMat[i][j] = (mat[j][i]);
        }
    }

    return newMat;
}

int main(int argc, char** argv)
{
    // TODO: write your code here

    std::vector<std::vector<int>> matA{
        { 1, 1, 1 },
        { 2, 2, 2 },
        { 3, 3, 3 }
    };

    std::vector<std::vector<int>> matB{
        { 5, 5 },
        { 6, 7 },
        { 9, 1 }
    };

    PrintMatrix(matA);
    PrintMatrix(matB);

    matA = TransposeMatrix(matA);
    matB = TransposeMatrix(matB);

    PrintMatrix(matA);
    PrintMatrix(matB);
    return 0;
}
