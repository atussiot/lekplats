#pragma once

#include <complex>
#include <random>
#include <vector>

enum class Restriction : uint8_t
{
    None = 0,
    Previous, ///< The same vertex cannot be selected twice in a row
    NextAntiClockwise,
    NextClockwise,
};

class ChaosGame
{
public:
    size_t pointsCount = 500000; ///< Number of points to generate
    size_t polygonSize = 5; ///< Number of vertices in the polygon defining the playground
    /// Each point is the fraction of the distance between the previous point and the target vertex
    double fraction = 0.5;
    /// The choice of the next target vertex may be retricted
    Restriction restriction = Restriction::None;

    ChaosGame() { }
    ChaosGame(size_t points, size_t polygon, Restriction restr)
        : pointsCount(points), polygonSize(polygon), restriction(restr) { }

    std::vector<std::complex<double>> generate_points();

private:
    std::complex<double> get_random();

    std::random_device _rd;
    std::mt19937 _generator{ _rd() };
};

// NOTE: Implementation details, exposed only for testing purposes
std::vector<std::complex<double>> regular_polygon_vertices(size_t polygonSize);
size_t getNextIndex(size_t polygonSize, size_t index, bool clockwise);
bool isNextTargetValid(const ChaosGame* game, size_t previousIndex, size_t newIndex);

