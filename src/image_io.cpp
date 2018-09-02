#include <image_io.h>

#include <point2D.h>

#include <QImage>
#include <QPainter>

bool saveToFile(const std::string& filename, const std::vector<std::vector<Point2D>>& points)
{
    const int HEIGHT = 480;
    const int WIDTH = 640;
    const Qt::GlobalColor COLORS[5] = { Qt::yellow, Qt::red, Qt::green, Qt::blue, Qt::magenta };

    QSize imageSize{ WIDTH, HEIGHT };

    QImage image { imageSize, QImage::Format_ARGB32_Premultiplied };
    image.fill(Qt::black);
    QPainter painter { &image };

    QPen pen;
    pen.setWidth(2);
    for (size_t i = 0; i < points.size(); ++i)
    {
        pen.setColor(COLORS[ i % 5 ]);
        painter.setPen(pen);

        for (const auto& point : points[i])
        {
            painter.drawPoint(static_cast<int>(point[0]), static_cast<int>(point[1]));
        }
    }

    return image.save(QString::fromStdString(filename));
}

bool saveToFile(const std::string& filename, const std::vector<std::complex<double>>& points)
{
    constexpr int SIZE = 2560;
    constexpr auto HALF_SIZE = static_cast<double>(SIZE) / 2.0;
    constexpr std::complex<double> ROT{ 0.0, -1.0 };
    constexpr std::complex<double> CENTER{ HALF_SIZE, HALF_SIZE };

    QImage image { QSize(SIZE, SIZE), QImage::Format_ARGB32_Premultiplied };
    image.fill(Qt::black);
    QPainter painter { &image };
    painter.setPen(Qt::yellow);

    for (const auto& point : points)
    {
        // Rotate, scale and center to adapt to QImage's coordinate system
        const auto tmp = (point * ROT) * HALF_SIZE + CENTER;
        painter.drawPoint(tmp.real(), tmp.imag());
    }

    return image.save(QString::fromStdString(filename));
}

