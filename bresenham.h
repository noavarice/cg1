#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <QImage>
#include <QPoint>

#define INOUT

void bresenhamCircleCurve(INOUT QImage& image,
                          const QPoint& start,
                          const QPoint& end,
                          const uint8_t radius);

#endif // BRESENHAM_H
