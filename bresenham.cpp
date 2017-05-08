#include "bresenham.h"

#include <QtMath>

/**
 * @brief Находит и возвращает пару точек, являющихся возможными центрами круга, проходящего через
 * p1 и p2
 */
static QPoint getCircleCenter(const QPoint& p1, const QPoint& p2, const uint8_t radius)
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

void bresenhamCircleCurve(INOUT QImage& image,
                          const QPoint& start,
                          const QPoint& end,
                          const uint8_t radius)
{
}
