//
// Created by ZiT on 2021/7/18.
//

#include <array>
#include "base.cpp"

namespace sorting {

    namespace shell_sort {

        /**
         * @brief 生成由 Sedgewick（1986）提出的步长序列（see => https://en.wikipedia.org/wiki/Shellsort）
         * @param len 待排序的数组长度
         */
        std::vector<int> generateStepSeries(int len) {
            std::vector<int> step_series;
            int i = 0, s = 0;
            while (s < len) {
                if (i & 1) {
                    s = 8 * (int) pow(2, i) -
                        6 * (int) pow(2, (i + 1) >> 1) +
                        1;
                } else {
                    s = 9 * (int) pow(2, i) -
                        9 * (int) pow(2, i >> 1) +
                        1;
                }
                step_series.push_back(s);
                i++;
            }
            return step_series;
        }

        template<size_t N>
        void shellSort(std::array<int64_t, N> &arr) {
            std::vector<int> step_series = generateStepSeries(N);
            std::reverse(step_series.begin(), step_series.end());
            for (int s : step_series) {
                for (int i = 0; i < N; i += s) {
                    int j = i;
                    while (j - s >= 0 && arr[j] < arr[j - s]) {
                        std::swap(arr[j], arr[j - s]);
                        j -= s;
                    }
                }
            }

        }

    } // namespace shell_sort
} // namespace sorting

int main(int argc, char *argv[]) {
    const int64_t inputSize = 100;

    std::array<int64_t, inputSize> arr = sorting::base::generateRandomArray<inputSize>(50, 1000);
    std::cout << "Before sorting: ";
    sorting::base::showArray(arr);

    sorting::shell_sort::shellSort<arr.size()>(arr);

    std::cout << "After sorting: ";
    sorting::base::showArray(arr);

    assert(std::is_sorted(arr.begin(), arr.end()));
    std::cout << "Array is sorted!";

    return 0;
}