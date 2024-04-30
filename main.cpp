#include <iostream>
#include <cassert>

#include "Matrix.h"

/**
 * @brief main - main функция
 *
 * Пример вызова функций
 * @return
 */
int main(int, char const **)
{
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);
    for(auto c: matrix)
    {
        int x,y,v;
        std::tie(x, y, v) = c;
        std::cout<<x<<y<<v<<std::endl;
        //std::cout<<"["<<x<<"]["<<y<<"] = "<<v<<std::endl;
    }

    std::cout<<"Matrix diagonal"<<std::endl;
    Matrix<int, 0> dMatrix;
    dMatrix[0][0] = 0;
    dMatrix[1][1] = 1;
    dMatrix[2][2] = 2;
    dMatrix[3][3] = 3;
    dMatrix[4][4] = 4;
    dMatrix[5][5] = 5;
    dMatrix[6][6] = 6;
    dMatrix[7][7] = 7;
    dMatrix[8][8] = 8;
    dMatrix[9][9] = 9;

    dMatrix[0][9] = 9;
    dMatrix[1][8] = 8;
    dMatrix[2][7] = 7;
    dMatrix[3][6] = 6;
    dMatrix[4][5] = 5;
    dMatrix[5][4] = 4;
    dMatrix[6][3] = 3;
    dMatrix[7][2] = 2;
    dMatrix[8][1] = 1;
    dMatrix[9][0] = 0;

    dMatrix.printValues(std::make_pair(1,1), std::make_pair(8,8));
    std::cout<<"size = " <<dMatrix.size()<<std::endl;
    for(auto c: dMatrix)
    {
        int x,y,v;
        std::tie(x, y, v) = c;
        std::cout<<"["<<x<<"]["<<y<<"] = "<<v<<std::endl;
    }
    return 0;
}
