//
// Created by ZiT on 2021/7/17.
//

#include <array>
#include "base.cpp"

namespace sorting {

    namespace merge_sort {

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
        void mergeSort(std::array<int64_t, N> &arr, int low, int high) {
            if (low < high) {
                int64_t mid = low + ((high - low) >> 1);
                mergeSort(arr, low, mid);
                mergeSort(arr, mid + 1, high);
                merge(arr, low, mid, high);
            }
        }

    } // namespace merge_sort
} // namespace sorting



/**
 * @brief Main function
 * @param argc commandline argument count (ignored)
 * @param argv commandline array of arguments (ignored)
 * @returns 0 on exit
 */
int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::merge_sort::mergeSort<arr.size()>(arr, 0, arr.size() - 1);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}