#include <iostream>

using namespace std;

const int N = 4;

//This function prints the matrix.
void printMatrix(int n, int C[][N]) {

    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << C[i][j] << "\t";
        cout << endl;
    }
}

//This function multiplies matrices.
void matrixMultiplication(int A[][N], int B[][N], int C[][N]) {

    for (int i = 0; i < N / 2; i++) {
        for (int j = 0; j < N / 2; j++) {
            C[i][j] = 0;

            for (int t = 0; t < N / 2; t++)
                C[i][j] = C[i][j] + A[i][t] * B[t][j];
        }
    }
}

//This function sums matrices.
void matrixSum(int n, int A[][N], int B[][N], int C[][N]) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    }
}

//This function subs matrices.
void matrixSub(int n, int A[][N], int B[][N], int C[][N]) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    }
}

void strassen(int n, int A[][N], int B[][N], int C[][N]) {

    int A11[N][N], A12[N][N], A21[N][N], A22[N][N];
    int B11[N][N], B12[N][N], B21[N][N], B22[N][N];
    int C11[N][N], C12[N][N], C21[N][N], C22[N][N];
    int M1[N][N], M2[N][N], M3[N][N], M4[N][N], M5[N][N], M6[N][N], M7[N][N];
    int AA[N][N], BB[N][N];

    if (n == 2)
        matrixMultiplication(A, B, C);
    else {

        for (int i = 0; i < n / 2; i++) {
            for (int j = 0; j < n / 2; j++) {

                A11[i][j] = A[i][j];
                A12[i][j] = A[i][j + n / 2];
                A21[i][j] = A[i + n / 2][j];
                A22[i][j] = A[i + n / 2][j + n / 2];

                B11[i][j] = B[i][j];
                B12[i][j] = B[i][j + n / 2];
                B21[i][j] = B[i + n / 2][j];
                B22[i][j] = B[i + n / 2][j + n / 2];
            }
        }

        matrixSum(n / 2, A11, A22, AA);  // AA = A11 + A22
        matrixSum(n / 2, B11, B22, BB);  // BB = B11 + B22
        strassen(n / 2, AA, BB, M1);     // M1 = (A11 + A22) * (B11 + B22)

        matrixSum(n / 2, A21, A22, AA);  // AA = A21 + A22
        strassen(n / 2, AA, B11, M2);    // M2 = (A21 + A22) * B11

        matrixSub(n / 2, B12, B22, BB);  // BB = B12 - B22
        strassen(n / 2, A11, BB, M3);    // M3 = A11 * (B12 - B22)

        matrixSub(n / 2, B21, B11, BB);  // BB = B21 - B11
        strassen(n / 2, A22, BB, M4);    // M4 = A22 * (B21 - B11)

        matrixSum(n / 2, A11, A12, AA);  // AA = A11 + A12
        strassen(n / 2, AA, B22, M5);    // M5 = (A11 + A12) * B22

        matrixSub(n / 2, A21, A11, AA);  // AA = A21 - A11
        matrixSum(n / 2, B11, B12, BB);  // BB = B11 + B12
        strassen(n / 2, AA, BB, M6);     // M6 = (A21 - A11) * (B11 + B12)

        matrixSub(n / 2, A12, A22, AA);  // AA = A12 - A22
        matrixSum(n / 2, B21, B22, BB);  // BB = B21 + B22
        strassen(n / 2, AA, BB, M7);     // M7 = (A12 - A22) * (B21 + B22)

        matrixSum(n / 2, M1, M4, AA);    // AA = M1 + M4
        matrixSub(n / 2, AA, M5, BB);    // BB = (M1 + M4) - M5
        matrixSum(n / 2, BB, M7, C11);   // C11 = (M1 + M4 - M5) + M7

        matrixSum(n / 2, M3, M5, C12);   // C12 = M3 + M5
        matrixSum(n / 2, M2, M4, C21);   // C21 = M2 + M4

        matrixSum(n / 2, M1, M3, AA);    // AA = M1 + M3
        matrixSub(n / 2, AA, M2, BB);    // BB = (M1 + M3) - M2
        matrixSum(n / 2, BB, M6, C22);   // C22 = (M1 + M3 - M2) + M6

        for (int i = 0; i < n / 2; i++) { 
            for (int j = 0; j < n / 2; j++) {

                C[i][j] = C11[i][j];
                C[i][j + n / 2] = C12[i][j];
                C[i + n / 2][j] = C21[i][j];
                C[i + n / 2][j + n / 2] = C22[i][j];
            }
        }
    }
}

int main() {

    int A[N][N] = {
        {2, 2, 3, 1},
        {1, 4, 1, 2},
        {2, 3, 1, 1},
        {1, 3, 1, 2}
    };

    int B[N][N] = {
        {2, 1, 2, 1},
        {3, 1, 2, 1},
        {3, 2, 1, 1},
        {1, 4, 3, 2}
    };

    int C[N][N];

    cout << "\nA Matrix : \n";
    printMatrix(N, A);
    cout << "\nB Matrix : \n";
    printMatrix(N, B);

    strassen(N, A, B, C);

    cout << "\nA * B Matrix : \n";
    printMatrix(N, C);

    return 0;
}

