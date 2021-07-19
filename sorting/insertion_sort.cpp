//
// Created by ZiT on 2021/7/18.
//

#include <array>
#include "base.cpp"

namespace sorting {

    namespace insertion_sort {

        template<size_t N>
        void insertionSort(std::array<int64_t, N> &arr) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < i; ++j) {
                    if (arr[i] < arr[j]) { // 若使用 <= 则破坏稳定性
                        for (int k = i; k > j; --k) {
                            std::swap(arr[k], arr[k - 1]);
                        }
                    }
                }
            }
        }

    } // namespace insertion_sort
} // namespace sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::insertion_sort::insertionSort<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}