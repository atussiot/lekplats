#pragma once

#include <string>
#include <vector>

struct Point2D;

bool saveToFile(const std::string& filename,
                const std::vector<Point2D>& points, const std::vector<Point2D>& points_2);
bool saveToFile(const std::vector<Point2D>& points);

