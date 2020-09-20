#include <QImage>
#include <QPainter>

#include <array>
#include <cstdlib>
#include <iostream>

static const size_t WIDTH = 160, HEIGHT = 100;
static const int CELL_SIZE = 10;
constexpr size_t IMG_WIDTH = WIDTH * CELL_SIZE + WIDTH + 1;
constexpr size_t IMG_HEIGHT = HEIGHT * CELL_SIZE + HEIGHT + 1;

using grid_t = std::array<std::array<bool, HEIGHT>, WIDTH>;
using heatmap_t = std::array<std::array<int, HEIGHT>, WIDTH>;
using coordinates_t = std::vector<std::pair<size_t, size_t>>;

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

bool cellular_automaton_test()
{
    auto grid = create_empty_grid();
    grid[WIDTH / 2][HEIGHT / 2] = true;

    const coordinates_t neighbors {
        { -1, -1 }, { 0, -1 }, { 1, -1 },
        { -1, 0 },             { 1, 0 },
        { -1, 1 },  { 0, 1},   { 1, 1 }
    };

    const std::string file_prefix{ "cell-test-" };
    const std::string file_extension{ ".png" };
    const std::string first_file = file_prefix + "0" + file_extension;
    if (!save_grid(grid, first_file)) return false;

    for (size_t it = 1; it < HEIGHT / 2; ++it) {
        coordinates_t to_mark;

        for (size_t i = 1; i < WIDTH - 1; ++i) for (size_t j = 1; j < HEIGHT - 1; ++j) {
            if (grid[i][j]) continue;

            std::uint8_t neighbors_count = 0;
            for (const auto& n : neighbors) {
                if (grid[i + n.first][j + n.second]) ++neighbors_count;
            }

            if (neighbors_count == 1 || neighbors_count == 3)
                to_mark.emplace_back(std::pair<size_t, size_t>{ i, j });
        }

        for (const auto& coord : to_mark) grid[coord.first][coord.second] = true;

        const std::string filename = file_prefix + std::to_string(it) + file_extension;
        if (!save_grid(grid, filename)) return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    if (!langtons_ant() || !cellular_automaton_test()) return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

