//
// Created by alexey on 08.12.2019.
//

#ifndef FRACTAL_SRC_SQUARE_RUBBER_BAND_HPP_
#define FRACTAL_SRC_SQUARE_RUBBER_BAND_HPP_

#include <QRubberBand>
#include <QResizeEvent>

class SquareRubberBand : public QRubberBand {
public:
  explicit SquareRubberBand(QRubberBand::Shape s, QWidget* parent = nullptr);

public slots:
  void resizeEvent(QResizeEvent* event) override;
};

#endif //FRACTAL_SRC_SQUARE_RUBBER_BAND_HPP_
