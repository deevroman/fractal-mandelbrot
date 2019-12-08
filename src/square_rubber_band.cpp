//
// Created by alexey on 08.12.2019.
//

#include "square_rubber_band.hpp"

void SquareRubberBand::resizeEvent(QResizeEvent *event) {
  if (event->size().width() != event->size().height())
    return;
//  int sz = qMin(event->size().width(), event->size().height());
//  this->resize(sz, sz);
  QRubberBand::resizeEvent(event);
}
SquareRubberBand::SquareRubberBand(QRubberBand::Shape s, QWidget *parent) : QRubberBand(s, parent) {}

