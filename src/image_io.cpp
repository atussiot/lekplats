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
            painter.drawPoint(static_cast<int>(point.x), static_cast<int>(point.y));
        }
    }

    return image.save(QString::fromStdString(filename));
}
