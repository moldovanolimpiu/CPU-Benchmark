#ifndef RESDMANDELBROT_H
#define RESDMANDELBROT_H

#include <QDialog>
#include "mandelbrot.h"

namespace Ui {
class RESDMandelbrot;
}

class RESDMandelbrot : public QDialog
{
    Q_OBJECT

public:
    explicit RESDMandelbrot(QWidget *parent = nullptr);
    ~RESDMandelbrot();
    void setResults(const mandelbrotInfo& result);

private:
    Ui::RESDMandelbrot *ui;
};

#endif // RESDMANDELBROT_H
