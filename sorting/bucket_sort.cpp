//
// Created by ZiT on 2021/7/18.
//

#include <array>
#include "base.cpp"

namespace sorting {

    namespace bucket_sort {

        template<size_t N>
        void bucketSort(std::array<int64_t, N> &arr, int64_t max) {
            int *bucket = new int[max + 1];
            for (int i = 0; i < N; ++i) {
                bucket[i]++;
            }
            int k = 0;
            for (int i = 0; i <= max; ++i) {
                for (int j = 0; j < bucket[i]; ++j) {
                    arr[k++] = i;
                }
            }
            delete[] bucket;
        }

    } //namespace bucket_sort
} // namespace sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::bucket_sort::bucketSort<arr.size()>(arr, 1000);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}