#include <van_eck_sequence.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[])
{
    static const int N = 1000;
    std::cout << "Number of iterations: " << N << std::endl << std::endl;
    for (int ini = 0; ini < 11; ++ini) {
        const auto S = generate_van_eck_seq_stats(N, ini);
        std::cout << "[" << ini << "] ";
        std::cout << "Number of elements: " << S.size() << " - ";
        std::cout << "First missing value: " << first_missing_value(S) << " - ";
        std::cout << "Highest value: " << highest_value(S) << std::endl;
    }
    return EXIT_SUCCESS;
}

