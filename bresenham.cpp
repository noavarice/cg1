#include "bresenham.h"

#include <QColor>
#include <QImage>
#include <QPoint>

#include <QtMath>

/**
 * @brief Находит и возвращает пару точек, являющихся возможными центрами круга, проходящего через
 * p1 и p2
 */
static QPoint getCircleCenter(
        const QPoint& p1,
        const QPoint& p2,
        const uint8_t radius
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

void bresenhamCircleCurve(
        INOUT QImage& image,
        const QColor& color,
        const QPoint& start,
        const QPoint& end,
        const uint8_t radius
        )
{
    QPoint center = getCircleCenter(start, end, radius);
    QPoint rightPointOffset{1, 0};
    QPoint bottomPointOffset{0, 1};
    QPoint diagonalPointOffset{1, 1};
    const int bottomLimit = center.y();
    QPoint currentPoint{center.x(), bottomLimit - radius};
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
        image.setPixelColor(nextPoint, color);
    }
}
