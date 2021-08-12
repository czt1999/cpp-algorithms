//
// Created by ZiT on 2021/8/11.
//
#include <iostream>

using namespace std;

namespace math {

    namespace matrix_multiplication {

        template<size_t M, size_t N, size_t K>
        void matrix_m(int a[M][N], int b[N][K], int c[M][K]) {
            for (int i = 0; i < M; ++i) {
                for (int j = 0; j < K; ++j) {
                    int sum = 0;
                    for (int k = 0; k < N; ++k) {
                        sum += a[i][k] * b[k][j];
                    }
                    c[i][j] = sum;
                }
            }
        }

        template<size_t M, size_t N>
        void show(int matrix[M][N]) {
            cout << "[" << endl;
            for (int i = 0; i < M; ++i) {
                cout << "\t[";
                for (int j = 0; j < N; ++j) {
                    cout << matrix[i][j];
                    if (j != N - 1) {
                        cout << ", ";
                    }
                }
                cout << "]";
                if (i != M - 1) {
                    cout << ", ";
                }
                cout << endl;
            }
            cout << "]" << endl;
        }

    } // namespace matrix_multiplication
} // namespace math

int main(int argc, char *argv[]) {
    const int M = 3, N = 4, K = 2;
    int a[M][N] = {
            {1, 2, 3, 4},
            {3, 2, 3, 1},
            {4, 1, 3, 2}
    };
    int b[N][K] = {
            {1, 2},
            {2, 2},
            {3, 1},
            {4, 2}
    };
    auto c = new int[M][K];
    math::matrix_multiplication::matrix_m<M, N, K>(a, b, c);
    math::matrix_multiplication::show<M, K>(c);
}