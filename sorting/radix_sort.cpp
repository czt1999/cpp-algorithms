//
// Created by ZiT on 2021/7/18.
//

#include <array>
#include <queue>
#include "base.cpp"

namespace sorting {

    namespace radix_sort {

        /**
         * @brief 返回给定整数的第 k 位数字（最末位为第 1 位））
         */
        int64_t numAt(int64_t a, int k) {
            for (int i = 1; i < k; i++) {
                a /= 10;
            }
            return a % 10;
        }

        template<size_t N>
        void radixSort(std::array<int64_t, N> &arr) {
            int n = 0;
            std::queue<int64_t> buckets[10];
            for (int64_t mx = base::max(arr); mx > 0; mx /= 10, ++n);
            for (int k = 1; k <= n; ++k) {
                // 数组 => 桶中的队列
                for (int64_t a : arr) {
                    buckets[numAt(a, k)].push(a);
                }
                int i = 0;
                // 桶中的队列 => 数组
                for (auto &bucket : buckets) {
                    while (!bucket.empty()) {
                        arr[i++] = bucket.front();
                        bucket.pop();
                    }
                }
            }
        }

    } // namespace radix_sort
} // namespace sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::radix_sort::radixSort<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}