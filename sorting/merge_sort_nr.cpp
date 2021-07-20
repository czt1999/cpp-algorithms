//
// Created by ZiT on 2021/7/19.
//

#include <array>
#include <algorithm>
#include "base.cpp"

namespace sorting {

    /**
     * non-recursive merge sorting
     */
    namespace merge_sort_nr {

        template<size_t N>
        void merge(std::array<int64_t, N> &arr, int l, int m, int r) {
            int i, j, k;
            int L_len = m - l + 1, R_len = r - m;
            auto *L = new int64_t[L_len];
            auto *R = new int64_t[R_len];

            i = l;
            for (; i <= m; i++) { L[i - l] = arr[i]; }
            for (; i <= r; i++) { R[i - m - 1] = arr[i]; }

            i = j = 0;
            k = l;
            for (; k <= r && i < L_len && j < R_len; k++) {
                if (L[i] <= R[j]) {
                    arr[k] = L[i++];
                } else {
                    arr[k] = R[j++];
                }
            }
            while (i < L_len) {
                arr[k++] = L[i++];
            }
            while (j < R_len) {
                arr[k++] = R[j++];
            }

            delete[] L;
            delete[] R;
        }

        template<size_t N>
        void mergeSortNR(std::array<int64_t, N> &arr) {
            for (int i = 1; i < N; i <<= 1) {
                int j = 0;
                while (j < N) {
                    int l = j;
                    int r = (j + 2 * i - 1 < N) ? (j + 2 * i - 1) : (N - 1);
                    if (r > l) {
                        int m = (j + i - 1 < N) ? (j + i - 1) : j;
                        merge(arr, l, m, r);
                    }
                    j = r + 1;
                }
            }
        }

    } // namespace merge_sort_nr
} //sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::merge_sort_nr::mergeSortNR<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}