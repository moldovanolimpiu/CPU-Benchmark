#ifndef RCDENCRDECR_H
#define RCDENCRDECR_H

#include <QDialog>

namespace Ui {
class RCDEncrdecr;
}

class RCDEncrdecr : public QDialog
{
    Q_OBJECT

public:
    explicit RCDEncrdecr(QWidget *parent = nullptr);
    ~RCDEncrdecr();

signals:
    void startBenchmark(int runs);
    void startBenchmarkParam(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal);

private slots:
    void onStartClicked();

private:
    Ui::RCDEncrdecr *ui;
    void setRunning(bool run);
    void onModeChanged(int type);
    void onAutofillClicked();
};

#endif // RCDENCRDECR_H
