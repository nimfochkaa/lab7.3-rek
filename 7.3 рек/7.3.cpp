#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
} 

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo) {
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo) {
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo) {
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
}

void CreateRow(int** a, const int rowNo, const int colCount, const int Low, const int High, int colNo) {
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount, const int Low, const int High, int rowNo) {
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

int CalculateSumOfRow(int** a, const int rowNo, const int colCount, int colNo, int sum, bool& hasNegative) {
    if (colNo < colCount) {
        if (a[rowNo][colNo] < 0)
            hasNegative = true;
        sum += a[rowNo][colNo];
        return CalculateSumOfRow(a, rowNo, colCount, colNo + 1, sum, hasNegative);
    }
    return hasNegative ? sum : 0;
}
int CalculateSum(int** a, const int rowCount, const int colCount, int rowNo, int totalSum) 
{
        if (rowNo < rowCount) 
        {
            bool hasNegative = false;
            int rowSum = CalculateSumOfRow(a, rowNo, colCount, 0, 0, hasNegative);
            totalSum += rowSum;
            return CalculateSum(a, rowCount, colCount, rowNo + 1, totalSum);
        }
        return totalSum;
    }

bool IsMinInRow(int** a, const int rowNo, const int colIndex, const int colCount, int colNo) {
    if (colNo < colCount) {
        if (a[rowNo][colNo] < a[rowNo][colIndex])
            return false;
        return IsMinInRow(a, rowNo, colIndex, colCount, colNo + 1);
    }
    return true;
}

bool IsMaxInCol(int** a, const int colIndex, const int rowCount, int rowNo) {
    if (rowNo < rowCount) {
        if (a[rowNo][colIndex] > a[0][colIndex])
            return false;
        return IsMaxInCol(a, colIndex, rowCount, rowNo + 1);
    }
    return true;
}

void FindSaddlePointsInRow(int** a, const int rowCount, const int colCount, int rowNo, int colNo, int& No) {
    if (colNo < colCount) {
        if (IsMinInRow(a, rowNo, colNo, colCount, 0) && IsMaxInCol(a, colNo, rowCount, 0)) {
            cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << colNo << endl;
        }
        FindSaddlePointsInRow(a, rowCount, colCount, rowNo, colNo + 1, No);
    }
}

void FindSaddlePoints(int** a, const int rowCount, const int colCount, int rowNo, int& No) {
    FindSaddlePointsInRow(a, rowCount, colCount, rowNo, 0, No);
    if (rowNo < rowCount - 1)
        FindSaddlePoints(a, rowCount, colCount, rowNo + 1, No);
}

int main() {
    srand((unsigned)time(NULL));

    int Low = -7;
    int High = 7;
    int rowCount, colCount;

    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    CreateRows(a, rowCount, colCount, Low, High, 0);
    InputRows(a, rowCount, colCount, 0);
    PrintRows(a, rowCount, colCount, 0);

    int totalSum = CalculateSum(a, rowCount, colCount, 0, 0);
    cout << "Sum of elements in rows with at least one negative element: " << totalSum << endl;

    int No = 0;
    cout << "Saddle points (minimum in row and maximum in column):" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
    FindSaddlePoints(a, rowCount, colCount, 0, No);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}