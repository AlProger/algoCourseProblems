#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int>::iterator partition(std::vector<int>::iterator left,
                                     std::vector<int>::iterator right, int elem) {
    while (left <= right) {
        while (*left < elem) ++left;
        while (*right > elem) --right;
        if (left <= right) std::swap(*left++, *right--);
    }
    return left;
}

void quicksort(std::vector<int>::iterator left, std::vector<int>::iterator right) {
    while (left < right) {
        auto elem = left + rand() % (right - left + 1);
        std::vector<int>::iterator pivot = partition(left, right, *elem);
        quicksort(left, pivot - 1);
        left = pivot;
    }
}

int main() {
    size_t N = 0;
    std::cin >> N;
    std::vector<int> array(N);
    for (size_t i = 0; i != N; ++i) {
        std::cin >> array[i];
    }
    if (N != 0)
        quicksort(array.begin(), array.end() - 1);
    for (auto elem : array) {
        std::cout << elem << " ";
    }
}
