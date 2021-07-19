//
// Created by ZiT on 2021/7/16.
//
#include "iostream"
#include "base.cpp"

namespace sorting {

    namespace quick_sort {

        /**
         * @brief
         * @param arr
         * @param low
         * @param high
         * @return final position of the pivot element
         */
        template<size_t N>
        int64_t partition(std::array<int64_t, N> &arr, int low, int high) {
            int64_t pivot = arr[low];
            int l = low, h = high;
            while (l < h) {
                while (l < h && arr[h] >= pivot) { h--; }
                arr[l] = arr[h];
                while (l < h && arr[l] <= pivot) { l++; }
                arr[h] = arr[l];
            }
            arr[l] = pivot;
            return l;
        }

        template<size_t N>
        void quickSort(std::array<int64_t, N> &arr, int low, int high) {
            if (low < high) {
                int pos = partition(arr, low, high);
                quickSort(arr, low, pos - 1);
                quickSort(arr, pos + 1, high);
            }
        }

    } // namespace quick_sort
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

    sorting::quick_sort::quickSort<arr.size()>(arr, 0, arr.size() - 1);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}