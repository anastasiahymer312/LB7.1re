#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** S, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** S, const int rowCount, const int colCount, int i, int j);
void Sort(int** S, const int rowCount, const int colCount, int i0, int i1);
void Change(int** S, const int row1, const int row2, const int colCount, int j);
void Calc(int** S, const int rowCount, const int colCount, int& sum, int& count, int i, int j);

int main()
{
    srand((unsigned)time(NULL));
    const int rowCount = 7;  
    const int colCount = 6;  
    int sum = 0;             
    int count = 0;           
    int** S = new int* [rowCount];

    for (int i = 0; i < rowCount; i++)
        S[i] = new int[colCount];

    Create(S, rowCount, colCount, 9, 61, 0, 0); 
    cout << "Original Matrix:" << endl;
    Print(S, rowCount, colCount, 0, 0);         
    Sort(S, rowCount, colCount, 0, 0);         
    cout << "Sorted Matrix:" << endl;
    Print(S, rowCount, colCount, 0, 0);        
    Calc(S, rowCount, colCount, sum, count, 0, 0); 
    cout << "Sum = " << sum << endl;             
    cout << "Count = " << count << endl;        
    cout << "Modified Matrix:" << endl;
    Print(S, rowCount, colCount, 0, 0);        

    for (int i = 0; i < rowCount; i++)
        delete[] S[i];
    delete[] S;

    return 0;
}


void Create(int** S, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    S[i][j] = Low + rand() % (High - Low + 1); 
    if (j < colCount - 1) {
        Create(S, rowCount, colCount, Low, High, i, j + 1); 
    }
    else if (i < rowCount - 1) {
        Create(S, rowCount, colCount, Low, High, i + 1, 0); 
    }
}


void Print(int** S, const int rowCount, const int colCount, int i, int j)
{
    cout << setw(4) << S[i][j]; 
    if (j < colCount - 1) {
        Print(S, rowCount, colCount, i, j + 1); 
    }
    else if (i < rowCount - 1) {
        cout << endl;
        Print(S, rowCount, colCount, i + 1, 0); 
    }
    else {
        cout << endl << endl;
    }
}


void Sort(int** S, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 >= rowCount - 1) return;

    if (i1 < rowCount - i0 - 1) {
        if ((S[i0][0] > S[i1][0]) || 
            (S[i0][0] == S[i1][0] && S[i0][1] < S[i1][1]) || 
            (S[i0][0] == S[i1][0] && S[i0][1] == S[i1][1] && S[i0][2] < S[i1][2])) { 
            Change(S, i0, i1, colCount, 0); 
        }
        Sort(S, rowCount, colCount, i0, i1 + 1); 
    }
    else {
        Sort(S, rowCount, colCount, i0 + 1, 0); 
    }
}

void Change(int** S, const int row1, const int row2, const int colCount, int j)
{
    if (j < colCount) {
        int tmp = S[row1][j];
        S[row1][j] = S[row2][j];
        S[row2][j] = tmp; 
        Change(S, row1, row2, colCount, j + 1); 
    }
}

void Calc(int** S, const int rowCount, const int colCount, int& sum, int& count, int i, int j)
{
    if (i >= rowCount) return; 

    if (j < colCount) {
        if (!(S[i][j] % 2 != 0 && (i + j) % 7 == 0)) { 
            sum += S[i][j];
            count++;        
            S[i][j] = 0;    
        }
        Calc(S, rowCount, colCount, sum, count, i, j + 1); 
    }
    else {
        Calc(S, rowCount, colCount, sum, count, i + 1, 0); 
    }
}
