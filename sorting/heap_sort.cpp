//
// Created by ZiT on 2021/7/18.
//
#include <array>
#include "base.cpp"

namespace sorting {

    namespace heap_sort {

        /**
         * @brief 在 arr[0,...,k-1] 已经是一个大顶堆的情况下，
         *        向上调整 arr[k]，使 arr[0,...,k] 也成为大顶堆
         */
        template<size_t N>
        void adjustUp(std::array<int64_t, N> &arr, int k) {
            while (k > 0 && arr[k] > arr[(k - 1) >> 1]) {
                std::swap(arr[k], arr[(k - 1) >> 1]);
                k = (k - 1) >> 1;
            }
        }

        /**
         * @brief 以树的抽象模型看，在 arr[0] 的双侧（直到 arr[k]）皆是大顶堆
         *        的情况下，向下调整 arr[0]，使 arr[0,...,k] 也成为大顶堆
         */
        template<size_t N>
        void adjustDown(std::array<int64_t, N> &arr, int k) {
            int i = 0, j = 1;
            while (j <= k) {
                if (j + 1 <= k && arr[j] < arr[j + 1]) {
                    ++j;
                }
                if (arr[i] < arr[j]) {
                    std::swap(arr[i], arr[j]);
                    i = j;
                    j = (j << 1) + 1;
                } else {
                    break;
                }
            }
        }

        template<size_t N>
        std::array<int64_t, N> buildHeap(std::array<int64_t, N> arr) {
            for (int i = 0; i < N; ++i) {
                adjustUp(arr, i);
            }
            return arr;
        }

        template<size_t N>
        void heapSort(std::array<int64_t, N> &arr) {
            std::array<int64_t, N> heap = buildHeap(arr);
            for (int i = 0; i < N; ++i) {
                std::swap(heap[0], heap[N - i - 1]);
                adjustDown(heap, N - i - 2);
            }
            arr = heap;
        }

    } // namespace heap_sort
} // namespace sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::heap_sort::heapSort<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}