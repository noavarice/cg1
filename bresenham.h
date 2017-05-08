#ifndef BRESENHAM_H
#define BRESENHAM_H

#define INOUT

#include <cstdint>

class QColor;
class QImage;
class QPoint;

void bresenhamCircleCurve(
        INOUT QImage& image,
        const QColor& color,
        const QPoint& start,
        const QPoint& end,
        const uint8_t radius
        );

#endif // BRESENHAM_H
