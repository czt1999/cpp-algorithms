//
// Created by ZiT on 2021/7/18.
//

#include <array>
#include "base.cpp"

namespace sorting {

    namespace bubble_sort {

        template<size_t N>
        void bubbleSort(std::array<int64_t, N> &arr) {
            bool swap_check = true;
            // 若一轮遍历中没有发生交换，说明已经排好序，可以（提前）结束
            for (int j = N - 1; j > 0 && swap_check; --j) {
                swap_check = false;
                for (int i = 0; i < j; ++i) {
                    if (arr[i] > arr[i + 1]) {
                        swap_check = true;
                        std::swap(arr[i], arr[i + 1]);
                    }
                }
            }
        }

    } // namespace bubble_sort
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

    sorting::bubble_sort::bubbleSort<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}