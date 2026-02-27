#ifndef RCDMEMACCESS_H
#define RCDMEMACCESS_H

#include <QDialog>

namespace Ui {
class RCDMemaccess;
}

class RCDMemaccess : public QDialog
{
    Q_OBJECT

public:
    explicit RCDMemaccess(QWidget *parent = nullptr);
    ~RCDMemaccess();

public slots:
    void set_progress_value(int value);
    void set_progress_range(int min, int max);


signals:
    void startBenchmark(int runs);
    void startBenchmarkParam(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal);

private slots:
    void onStartClicked();

private:
    Ui::RCDMemaccess *ui;
    void setRunning(bool run);
    void onModeChanged(int type);
    void onAutofillClicked();
};

#endif // RCDMEMACCESS_H
