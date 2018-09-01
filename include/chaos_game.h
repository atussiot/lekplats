#pragma once

#include <complex>
#include <vector>

enum class Restriction : uint8_t
{
    None = 0,
    Previous,
    NextAntiClockwise,
    NextClockwise,
};

std::vector<std::complex<double>> chaos_game(size_t pointsCount, size_t verticesCount);

// NOTE: Implementation details, exposed only for testing purposes
std::vector<std::complex<double>> regular_polygon_vertices(const size_t verticesCount);
bool isNextTargetValid(Restriction restriction, size_t verticesCount,
                       size_t previousIndex, size_t newIndex);

