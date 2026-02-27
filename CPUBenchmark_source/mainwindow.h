#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cpuidwindow.h"
#include "rcdmemtransfer.h"
#include "rcdmemaccess.h"
#include "rcdencrdecr.h"
#include "rcdmandelbrot.h"
#include "rcdpcgrader.h"
#include "memTransfer.h"
#include <QFuture>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_runMemTransferBtn_clicked();
    void startMemTransferBenchmark(int runs, int valueLower, int valueUpper, int traversal);
    void on_runMemAccessBtn_clicked();
    void startMemAccessBenchmark(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal);
    void on_runEncrDecrBtn_clicked();
    void startEncrDecrBenchmark(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal);
    void on_runMandelbrot_clicked();
    void startMandelbrotBenchmark(int runs, int valueLower, int valueUpper, int traversal);
    void on_runPcGrader_clicked();
    void startPcGraderBenchmark();

private:
    Ui::MainWindow *ui;
    cpuidwindow *cpuIDWindow;
    RCDMemtransfer* memTransferConfigDialog = nullptr;
    RCDMemaccess* memAccessConfigDialog = nullptr;
    RCDEncrdecr* encrDecrConfigDialog = nullptr;
    RCDMandelbrot* mandelbrotConfigDialog = nullptr;
    RCDPcgrader* pcGraderConfigDialog = nullptr;
};
#endif // MAINWINDOW_H
