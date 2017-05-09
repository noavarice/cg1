#ifndef BRESENHAM_H
#define BRESENHAM_H

#define INOUT

#include <cstdint>

class QColor;
class QImage;
class QPoint;

void bresenhamCircleCurve(
        INOUT QImage& image,
        const QPoint& start,
        const QPoint& end,
        uint8_t radius,
        const QColor& color,
        uint8_t width
        );

#endif // BRESENHAM_H
