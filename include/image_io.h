#pragma once

#include <complex>
#include <string>
#include <vector>

struct Point2D;

/// @brief Save sets of points to an image
///
/// @param filename path to a valib image file name (must contain the extension, e.g. .png)
///
/// Each set will have a different color (up to 5 colors)
bool saveToFile(const std::string& filename, const std::vector<std::vector<Point2D>>& points);

/// Similar to the above, but assumes that the points are complex numbers inside the unit circle
bool saveToFile(const std::string& filename, const std::vector<std::complex<double>>& points);

