#include <iostream>
#include <vector>

int main() {
    size_t N = 0;
    std::cin >> N;
    std::vector<int> sequenceFirst(N);
    for (size_t i = 0; i != N; ++i)
        std::cin >> sequenceFirst[i];
    size_t M = 0;
    std::cin >> M;
    std::vector<int> sequenceSecond(M);
    for (size_t i = 0; i != M; ++i)
        std::cin >> sequenceSecond[i];
    std::vector<std::vector<int>> max_sequence(N + 1, std::vector<int>(M + 1));
    for (size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j != M; ++j) {
            if (sequenceFirst[N - i - 1] == sequenceSecond[M - j - 1]) {
                max_sequence[N - i - 1][M - j - 1] = 1 + max_sequence[N - i][M - j];
            } else {
                max_sequence[N - i - 1][M - j - 1] = std::max(max_sequence[N - i][M - j - 1],
                                                              max_sequence[N - i - 1][M - j]);
            }
        }
    }
    std::vector<int> result;
    for (size_t i = 0, j = 0; max_sequence[i][j] != 0 && i < sequenceFirst.size() && j < sequenceSecond.size();) {
        //
        if (sequenceFirst[i] == sequenceSecond[j]) {
            result.push_back(sequenceFirst[i]);
            ++i;
            ++j;
        } else {
            if (max_sequence[i][j] == max_sequence[i + 1][j]) {
                ++i;
            } else {
                ++j;
            }
        }
    }
    for (auto &elem : result)
        std::cout << elem << " ";
}
