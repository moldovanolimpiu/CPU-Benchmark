#ifndef RCDMEMTRANSFER_H
#define RCDMEMTRANSFER_H

#include <QDialog>


namespace Ui {
class RCDMemtransfer;
}

class RCDMemtransfer : public QDialog
{
    Q_OBJECT

public:
    explicit RCDMemtransfer(QWidget *parent = nullptr);
    ~RCDMemtransfer();

public slots:
    void set_progress_value(int value);
    void set_progress_range(int min, int max);

signals:
    void startBenchmark(int runs);
    void startBenchmarkParam(int runs, int valueLower, int valueUpper, int traversal);

private slots:
    void onStartClicked();

private:
    Ui::RCDMemtransfer *ui;
    void setRunning(bool run);
    void onAutofillClicked();
};



#endif // RCDMEMTRANSFER_H
