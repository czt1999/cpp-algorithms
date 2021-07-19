//
// Created by ZiT on 2021/7/18.
//

#include <array>
#include "base.cpp"

namespace sorting {
    
    namespace selection_sort {
        
        template<size_t N>
        void selectionSort(std::array<int64_t, N>& arr) {
            for (int i = 0; i < N; ++i) {
                int64_t min = INT64_MAX;
                int min_index = i;
                for (int j = i; j < N; ++j) {
                    if (arr[j] < min) {
                        min = arr[j];
                        min_index = j;
                    }
                }
                std::swap(arr[min_index], arr[i]);
            }
        }
        
    } // namespace selection_sort
} // namespace sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::selection_sort::selectionSort<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}