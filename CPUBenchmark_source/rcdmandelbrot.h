#ifndef RCDMANDELBROT_H
#define RCDMANDELBROT_H

#include <QDialog>

namespace Ui {
class RCDMandelbrot;
}

class RCDMandelbrot : public QDialog
{
    Q_OBJECT

public:
    explicit RCDMandelbrot(QWidget *parent = nullptr);
    ~RCDMandelbrot();

signals:
    void startBenchmark(int runs);
    void startBenchmarkParam(int runs, int valueLower, int valueUpper, int traversal);

private slots:
    void onStartClicked();

private:
    Ui::RCDMandelbrot *ui;
    void setRunning(bool run);
    void onAutofillClicked();
};

#endif // RCDMANDELBROT_H
