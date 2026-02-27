#ifndef RCDPCGRADER_H
#define RCDPCGRADER_H

#include <QDialog>

namespace Ui {
class RCDPcgrader;
}

class RCDPcgrader : public QDialog
{
    Q_OBJECT

public:
    explicit RCDPcgrader(QWidget *parent = nullptr);
    ~RCDPcgrader();

public slots:
    void set_progress_value(int value);
    void set_progress_range(int min, int max);


signals:
    void startBenchmark();

private slots:
    void onStartClicked();

private:
    Ui::RCDPcgrader *ui;
    void setRunning(bool run);
};

#endif // RCDPCGRADER_H
