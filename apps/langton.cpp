#include <QImage>
#include <QPainter>

#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

static const size_t WIDTH = 160, HEIGHT = 100;
static const int CELL_SIZE = 10;
constexpr size_t IMG_WIDTH = WIDTH * CELL_SIZE + WIDTH + 1;
constexpr size_t IMG_HEIGHT = HEIGHT * CELL_SIZE + HEIGHT + 1;

using grid_t = std::array<std::array<bool, HEIGHT>, WIDTH>;
using heatmap_t = std::array<std::array<int, HEIGHT>, WIDTH>;
using coordinate_t = std::pair<size_t, size_t>;
using coordinates_t = std::vector<coordinate_t>;
using bounding_box_t = std::pair<coordinate_t, coordinate_t>;

void draw_cell(QPainter& painter, const int x, const int y)
{
    const auto x_start = x * (CELL_SIZE + 1);
    const auto y_start = y * (CELL_SIZE + 1);
    const auto x_end = x_start + CELL_SIZE;
    const auto y_end = y_start + CELL_SIZE;

    for (auto i = x_start; i < x_end; ++i) for (auto j = y_start; j < y_end; ++j)
        painter.drawPoint(i, j);
}

void draw_grid(QPainter& painter)
{
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor{ 50, 50, 50 });
    painter.setPen(pen);
    for (size_t i = 0; i <= WIDTH; ++i) for (size_t j = 0; j < IMG_HEIGHT; ++j)
        painter.drawPoint(i * (CELL_SIZE + 1), j);
    for (size_t j = 0; j <= HEIGHT; ++j) for (size_t i = 0; i < IMG_WIDTH; ++i)
        painter.drawPoint(i, j * (CELL_SIZE + 1));
}

bool save_grid(const grid_t& grid, const std::string& filename)
{
    QSize image_size { IMG_WIDTH, IMG_HEIGHT };
    QImage image { image_size, QImage::Format_ARGB32_Premultiplied };
    image.fill(Qt::black);
    QPainter painter { &image };
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    for (size_t i = 0; i < WIDTH; ++i) for (size_t j = 0; j < HEIGHT; ++j)
        if (grid[i][j]) draw_cell(painter, i, j);
    draw_grid(painter);
    return image.save(QString::fromStdString(filename));
}

bool save_heatmap(const heatmap_t& heatmap, const std::string& filename)
{
    QSize image_size { IMG_WIDTH, IMG_HEIGHT };
    QImage image { image_size, QImage::Format_ARGB32_Premultiplied };
    image.fill(Qt::black);
    QPainter painter { &image };
    QPen pen;
    pen.setWidth(1);
    for (size_t i = 0; i < WIDTH; ++i) for (size_t j = 0; j < HEIGHT; ++j) {
        const auto v = heatmap[i][j];
        if (v != 0) {
            QColor color{ 0, 57 + v * 6 , 0 };
            if (!color.isValid()) {
                color = Qt::green;
                std::cout << "WARNING: saturation at " << i << "," << j << ":" << v << std::endl;
            }
            pen.setColor(color);
            painter.setPen(pen);
            draw_cell(painter, i, j);
        }
    }
    draw_grid(painter);
    return image.save(QString::fromStdString(filename));
}

grid_t create_empty_grid()
{
    grid_t grid;
    for (size_t i = 0; i < WIDTH; ++i) for (size_t j = 0; j < HEIGHT; ++j) grid[i][j] = false;
    return grid;
}

heatmap_t create_empty_heatmap()
{
    heatmap_t heatmap;
    for (size_t i = 0; i < WIDTH; ++i) for (size_t j = 0; j < HEIGHT; ++j) heatmap[i][j] = 0;
    return heatmap;
}

bool ant_in_grid(const size_t ant_x, const size_t ant_y)
{
    return ant_x > 0 && ant_y > 0 && ant_x < WIDTH && ant_y < HEIGHT;
}

size_t rotate_ant(const size_t ant_direction, const bool cell_on)
{
    auto new_direction = ant_direction + (cell_on ? 1 : 3);
    if (new_direction > 3) new_direction %= 4;
    return new_direction;
}

bool langtons_ant()
{
    auto grid = create_empty_grid();
    auto heatmap = create_empty_heatmap();

    size_t ant_x = WIDTH / 2;
    size_t ant_y = HEIGHT / 2;
    size_t ant_direction = 0;
    size_t iterations = 0;

    while (ant_in_grid(ant_x, ant_y)) {
        ++heatmap[ant_x][ant_y];
        const auto cell_on = grid[ant_x][ant_y];
        ant_direction = rotate_ant(ant_direction, cell_on);
        grid[ant_x][ant_y] = !cell_on;
        switch (ant_direction) {
        case 0:
            --ant_y;
            break;
        case 1:
            --ant_x;
            break;
        case 2:
            ++ant_y;
            break;
        case 3:
            ++ant_x;
            break;
        default:
            std::cerr << "Wrong ant direction, stopping..." << std::endl;
            return false;
        }
        ++iterations;
    }
    std::cout << "Ant escaped after " << iterations << " iterations!" << std::endl;

    const std::string langton_filename{ "langton.png" };
    const std::string heatmap_filename{ "langton-heatmap.png" };

    return save_grid(grid, langton_filename) && save_heatmap(heatmap, heatmap_filename);
}

bounding_box_t compute_bounding_box(const grid_t& grid)
{
    bounding_box_t bb { { WIDTH, HEIGHT }, { 0, 0 } };

    for (size_t i = 0; i < WIDTH; ++i) for (size_t j = 0; j < HEIGHT; ++j) {
        if (grid[i][j]) {
            if (i > bb.second.first) bb.second.first = i;
            if (i < bb.first.first) bb.first.first = i;
            if (j > bb.second.second) bb.second.second = j;
            if (j < bb.first.second) bb.first.second = j;
        }
    }

    return bb;
}

bool is_inside_grid(const bounding_box_t bb)
{
    if (bb.first.first == 1 || bb.first.second == 1
        || bb.second.first == WIDTH - 1 || bb.second.second == HEIGHT - 1)
        return false;
    return true;
}

bool save_iteration(const grid_t& grid, const size_t it, const std::string& prefix)
{
    const std::string file_extension{ ".png" };
    std::stringstream ss;
    ss << std::setw(3) << std::setfill('0') << it;
    const std::string filename = prefix + ss.str() + file_extension;
    return save_grid(grid, filename);
}

std::uint8_t count_alive_neighbors(const grid_t& grid, const size_t i, const size_t j)
{
    static const coordinates_t neighbors {
        { -1, -1 }, { 0, -1 }, { 1, -1 },
        { -1, 0 },             { 1, 0 },
        { -1, 1 },  { 0, 1},   { 1, 1 }
    };

    std::uint8_t neighbors_count = 0;
    for (const auto& n : neighbors) {
        if (grid[i + n.first][j + n.second]) ++neighbors_count;
    }

    return neighbors_count;
}

bool cellular_automaton_test()
{
    auto grid = create_empty_grid();
    const auto orig_x = WIDTH / 2, orig_y = HEIGHT / 2;
    grid[orig_x][orig_y] = true;
    bounding_box_t bb { { orig_x, orig_y }, { orig_x, orig_y } };
    size_t it = 0;

    const std::string prefix{ "cell-test-" };
    if (!save_iteration(grid, it, prefix)) return false;

    while (is_inside_grid(bb)) {
        ++it;
        coordinates_t to_mark;

        for (size_t i = bb.first.first - 1; i <= bb.second.first + 1; ++i)
        for (size_t j = bb.first.second - 1; j <= bb.second.second + 1; ++j) {
            if (grid[i][j]) continue;

            const auto neighbors_count = count_alive_neighbors(grid, i, j);
            if (neighbors_count == 1 || neighbors_count == 3)
                to_mark.emplace_back(coordinate_t{ i, j });
        }

        for (const auto& coord : to_mark) grid[coord.first][coord.second] = true;
        bb = compute_bounding_box(grid);
        std::cout << it << " : " << to_mark.size() << " new cells - bounding box tl("
                  << bb.first.first << ";" << bb.first.second << ") br(" << bb.second.first
                  << ";" << bb.second.second << ")" << std::endl;

        if (!save_iteration(grid, it, prefix)) return false;
    }

    return true;
}

size_t population(const grid_t& grid)
{
    size_t count = 0;
    for (size_t i = 0; i < WIDTH; ++i) for (size_t j = 0; j < HEIGHT; ++j)
        if (grid[i][j]) ++count;
    return count;
}

coordinate_t bounding_box_size(const bounding_box_t& bb)
{
    const auto width = bb.second.first - bb.first.first;
    const auto height = bb.second.second - bb.first.second;
    return coordinate_t{ width, height };
}

bool game_of_life()
{
    auto grid = create_empty_grid();
    grid [WIDTH / 2][HEIGHT / 2] = true;
    grid [WIDTH / 2 + 1][HEIGHT / 2] = true;
    grid [WIDTH / 2 + 2][HEIGHT / 2 - 1] = true;
    grid [WIDTH / 2 + 2][HEIGHT / 2 + 1] = true;
    grid [WIDTH / 2 + 2][HEIGHT / 2 - 3] = true;
    grid [WIDTH / 2 + 3][HEIGHT / 2 - 2] = true;

    grid [WIDTH / 2 + 4][HEIGHT / 2 - 8] = true;
    grid [WIDTH / 2 + 5][HEIGHT / 2 - 7] = true;
    grid [WIDTH / 2 + 4][HEIGHT / 2 - 7] = true;
    grid [WIDTH / 2 + 5][HEIGHT / 2 - 8] = true;

    auto bb = compute_bounding_box(grid);
    size_t it = 0;

    const std::string prefix { "game-of-life-" };
    if (!save_iteration(grid, it, prefix)) return false;

    coordinates_t to_life, to_death;

    do {
        ++it;
        to_life.clear();
        to_death.clear();

        for (size_t i = bb.first.first - 1; i <= bb.second.first + 1; ++i)
        for (size_t j = bb.first.second - 1; j <= bb.second.second + 1; ++j) {
            const auto neighbors_count = count_alive_neighbors(grid, i, j);
            if (grid[i][j]) {
                if (neighbors_count < 2 || neighbors_count > 3)
                    to_death.emplace_back(coordinate_t{ i, j });
            } else {
                if (neighbors_count == 3)
                    to_life.emplace_back(coordinate_t{ i, j });
            }
        }

        for (const auto& coord : to_life) grid[coord.first][coord.second] = true;
        for (const auto& coord : to_death) grid[coord.first][coord.second] = false;

        bb = compute_bounding_box(grid);
        if (!save_iteration(grid, it, prefix)) return false;

        const auto pop = population(grid);
        const auto bb_size = bounding_box_size(bb);
        std::cout << it << " - Population = " << pop << " - BB = " << bb_size.first << "*"
                  << bb_size.second << std::endl;

    } while (is_inside_grid(bb) && (to_life.size() != 0 || to_death.size() != 0));

    return true;
}

int main(int argc, char* argv[])
{
    if (!langtons_ant() || !cellular_automaton_test() || !game_of_life()) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

