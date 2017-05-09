#include "bresenham.h"

#include <QColor>
#include <QImage>
#include <QPoint>

#include <QtMath>

/**
 * @brief Находит и возвращает точку, являющуюся одним из возможных центров круга, проходящего через
 * p1 и p2
 */
static QPoint getCircleCenter(
        const QPoint& p1,
        const QPoint& p2,
        uint8_t radius
        )
{
    int dx, dy;
    if (p1.x() > p2.x()) {
        dx = p1.x() - p2.x();
        dy = p1.y() - p2.y();
    } else {
        dx = p2.x() - p1.x();
        dy = p2.y() - p1.y();
    }
    qreal lengthSqr = dx * dx + dy * dy;
    int catheterLength = static_cast<int>(qSqrt(radius * radius - lengthSqr / 4));
    QPoint middle = QPoint((p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2);
    if (!dx) {
        return QPoint(-catheterLength, middle.y());
    }
    if (!dy) {
        return QPoint(middle.x(), -catheterLength);
    }
    qreal coeff = -dx / dy;
    dx = qCos(coeff) * catheterLength;
    dy = qSin(coeff) * catheterLength;
    return middle - QPoint(dx, dy);
}

static int getEpsilon(const QPoint& center, const QPoint& radiusPoint, const uint8_t radius)
{
    QPoint diff{center.x() - radiusPoint.x(), center.y() - radiusPoint.y()};
    int sqrDistance = diff.x() * diff.x() + diff.y() * diff.y();
    return qAbs(sqrDistance - radius * radius);
}

static bool upperTheLine(
        const QPoint& point,
        const QPoint& start,
        const QPoint& end
        )
{
    double dx = start.x() - end.x();
    double dy = start.y() - end.y();
    if (!dx) {
        return point.x() >= start.x();
    }
    if (!dy) {
        return point.y() <= start.y();
    }
    return point.y() <= ((dy / dx) * (point.x() - start.x()) + start.y());
}

static void setPixelsColor(
        INOUT QImage& image,
        const QColor& color,
        const QPoint& center,
        const QPoint& start,
        const QPoint& end,
        const QPoint& radiusPoint,
        bool withinRectangle
        )
{
    QPoint centerDiff{qAbs(radiusPoint.x() - center.x()), qAbs(radiusPoint.y() - center.y())};
    QPoint drawPoint{center.x() + centerDiff.x(), center.y() + centerDiff.y()};
    if (upperTheLine(drawPoint, start, end) == withinRectangle) {
        image.setPixelColor(drawPoint, color);
    }
    drawPoint = {center.x() - centerDiff.x(), center.y() + centerDiff.y()};
    if (upperTheLine(drawPoint, start, end) == withinRectangle) {
        image.setPixelColor(drawPoint, color);
    }
    drawPoint = {center.x() + centerDiff.x(), center.y() - centerDiff.y()};
    if (upperTheLine(drawPoint, start, end) == withinRectangle) {
        image.setPixelColor(drawPoint, color);
    }
    drawPoint = {center.x() - centerDiff.x(), center.y() - centerDiff.y()};
    if (upperTheLine(drawPoint, start, end) == withinRectangle) {
        image.setPixelColor(drawPoint, color);
    }
}

void bresenhamCircleCurve(
        INOUT QImage& image,
        const QPoint& start,
        const QPoint& end,
        uint8_t radius,
        const QColor& color,
        uint8_t width,
        bool withinRectangle
        )
{
    QPoint center = getCircleCenter(start, end, radius);
    QPoint rightPointOffset{1, 0};
    QPoint bottomPointOffset{0, 1};
    QPoint diagonalPointOffset{1, 1};
    radius -= width / 2;
    while (width) {
        const int bottomLimit = center.y();
        QPoint currentPoint{center.x(), bottomLimit - radius};
        setPixelsColor(image, color, center, start, end, currentPoint, withinRectangle);
        while (currentPoint.y() < bottomLimit) {
            QPoint nextPoint = currentPoint + rightPointOffset;
            int minEpsilon = getEpsilon(center, currentPoint + rightPointOffset, radius);
            int tempEpsilon = getEpsilon(center, currentPoint + diagonalPointOffset, radius);
            if (tempEpsilon < minEpsilon) {
                minEpsilon = tempEpsilon;
                nextPoint = currentPoint + bottomPointOffset;
            }
            tempEpsilon = getEpsilon(center, currentPoint + diagonalPointOffset, radius);
            if (tempEpsilon < minEpsilon) {
                nextPoint = currentPoint + diagonalPointOffset;
            }
            currentPoint = nextPoint;
            setPixelsColor(image, color, center, start, end, currentPoint, withinRectangle);
        }
        ++radius;
        --width;
    }
}
