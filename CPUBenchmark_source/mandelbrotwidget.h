#pragma once
#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H
#include <QWidget>
#include <QImage>

class MandelbrotWidget: public QWidget{
    Q_OBJECT

public:
    MandelbrotWidget(const std::vector<int>& iters,
                              int width, int height, int maxIter,
                              QWidget * parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QImage image;
};

#endif // MANDELBROTWIDGET_H
