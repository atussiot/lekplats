#include <image_io.h>

#include <point2D.h>

#include <QImage>
#include <QPainter>

const int HEIGHT = 480;
const int WIDTH = 640;

bool saveToFile(const std::string& filename,
                const std::vector<Point2D>& points, const std::vector<Point2D>& points_2)
{
    QSize imageSize{ WIDTH, HEIGHT };

    QImage image { imageSize, QImage::Format_ARGB32_Premultiplied };
    image.fill(Qt::black);
    QPainter painter { &image };

    QPen pen{ Qt::red };
    pen.setWidth(2);
    painter.setPen(pen);

    for (const auto& point : points)
    {
        painter.drawPoint(static_cast<int>(point.x), static_cast<int>(point.y));
    }

    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    for (const auto& point : points_2)
    {
        painter.drawPoint(static_cast<int>(point.x), static_cast<int>(point.y));
    }

    return image.save(QString::fromStdString(filename));
}

bool saveToFile(const std::vector<Point2D>& points)
{
    QSize imageSize{ WIDTH, HEIGHT };

    QImage image { imageSize, QImage::Format_ARGB32_Premultiplied };
    image.fill(Qt::black);

    QPainter painter { &image };
    QPen pen{ Qt::white };
    pen.setWidth(2);
    painter.setPen(pen);

    for (const auto& point : points)
    {
        painter.drawPoint(static_cast<int>(point.x), static_cast<int>(point.y));
    }

    return image.save("test_1.png");
}

