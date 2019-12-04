#include <QRubberBand>
#include <QMouseEvent>
#include <QWidget>
#include <QPalette>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QDebug>
#include <QResizeEvent>
#include <QPaintEvent>
#include <memory>

#pragma once

class Graphics : public QWidget {
public:
  Graphics(QWidget* parent = nullptr);
  ~Graphics();

public slots:
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void resizeEvent(QResizeEvent* event) override;
  void paintEvent(QPaintEvent* event) override;

private:
  QPoint rubberBandStart;
  std::shared_ptr<QRubberBand> rubberBand;
};


