#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cpuidentification.h"
#include "memTransfer.h"
#include "rcdmemtransfer.h"
#include "resdmemtransfer.h"
#include "memAccess.h"
#include "rcdmemaccess.h"
#include "resdmemaccess.h"
#include "encrDecr.h"
#include "rcdencrdecr.h"
#include "resdencrdecr.h"
#include "mandelbrot.h"
#include "rcdmandelbrot.h"
#include "resdmandelbrot.h"
#include "pcGrader.h"
#include "rcdpcgrader.h"
#include "resdpcgrader.h"
#include "mandelbrotwidget.h"
#include <QFutureWatcher>
#include <QtConcurrent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , cpuIDWindow(nullptr)
{
    ui->setupUi(this);
    //ui->lineEditVendor->setText(CPUVendor());
    //ui->lineEditBrand->setText(BrandString());
    ui->labelTitle->setStyleSheet("font: 40pt");
    ui->labelVersion->setStyleSheet("font: 10pt");
    setWindowTitle("CPU Benchmark");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(!cpuIDWindow){
        cpuIDWindow = new cpuidwindow(this);
    }
    cpuIDWindow->show();
    //this->hide();
}
void MainWindow::on_runMemTransferBtn_clicked(){
    if(!memTransferConfigDialog){
        memTransferConfigDialog = new RCDMemtransfer(this);
        connect(memTransferConfigDialog, &RCDMemtransfer::startBenchmarkParam, this, &MainWindow::startMemTransferBenchmark);
    }

    memTransferConfigDialog ->show();
}

void MainWindow::startMemTransferBenchmark(int runs, int valueLower, int valueUpper, int traversal){
    QFutureWatcher<MemTransferInfo> *watcher = new QFutureWatcher<MemTransferInfo>(this);

    connect(watcher, &QFutureWatcher<MemTransferInfo>::finished, this, [=]() {
        MemTransferInfo result = watcher->result();
        RESDMemtransfer* dlg = new RESDMemtransfer(this);
        dlg->setResults(result);
        dlg->show();
        memTransferConfigDialog->close();
        memTransferConfigDialog->deleteLater();
        memTransferConfigDialog = nullptr;
        watcher->deleteLater();
    });

    QFuture<MemTransferInfo> future = QtConcurrent::run(run_mem_transfer_test, runs, valueLower, valueUpper, traversal);
    //connect(watcher, &QFutureWatcher<MemTransferInfo>::progressValueChanged, memTransferConfigDialog, &RCDMemtransfer::set_progress_value);
    //connect(watcher, &QFutureWatcher<MemTransferInfo>::progressRangeChanged, memTransferConfigDialog, &RCDMemtransfer::set_progress_range);
    watcher->setFuture(future);

}

void MainWindow::on_runMemAccessBtn_clicked(){
    if(!memAccessConfigDialog){
        memAccessConfigDialog = new RCDMemaccess(this);
        connect(memAccessConfigDialog, &RCDMemaccess::startBenchmarkParam, this, &MainWindow::startMemAccessBenchmark);
    }

    memAccessConfigDialog -> show();
}

void MainWindow::startMemAccessBenchmark(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal){
    QFutureWatcher<AllMemAccessInfo> *watcher = new QFutureWatcher<AllMemAccessInfo>(this);

    connect(watcher, &QFutureWatcher<AllMemAccessInfo>::finished, this, [=](){
        AllMemAccessInfo result = watcher -> result();
        RESDMemaccess* dlg = new RESDMemaccess(this);
        dlg->setResults(result);
        dlg->show();
        memAccessConfigDialog->close();
        memAccessConfigDialog->deleteLater();
        memAccessConfigDialog = nullptr;
        watcher->deleteLater();
    });

    QFuture<AllMemAccessInfo> future = QtConcurrent::run(run_mem_access_test, runs, valueLower, valueUpper, logarithmic, traversal);
    watcher-> setFuture(future);
}

void MainWindow::on_runEncrDecrBtn_clicked(){
    if(!encrDecrConfigDialog){
        encrDecrConfigDialog = new RCDEncrdecr(this);
        connect(encrDecrConfigDialog, &RCDEncrdecr::startBenchmarkParam, this, &MainWindow::startEncrDecrBenchmark);
    }

    encrDecrConfigDialog -> show();
}

void MainWindow::startEncrDecrBenchmark(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal){
    QFutureWatcher<encryptionDecryptionInfo> *watcher = new QFutureWatcher<encryptionDecryptionInfo>(this);

    connect(watcher, &QFutureWatcher<encryptionDecryptionInfo>::finished, this,[=](){
        encryptionDecryptionInfo result = watcher -> result();
        RESDEncrdecr* dlg = new RESDEncrdecr(this);
        dlg->setResults(result);
        dlg->show();

        encrDecrConfigDialog->close();
        encrDecrConfigDialog->deleteLater();
        encrDecrConfigDialog = nullptr;
        watcher->deleteLater();
    });
    QFuture<encryptionDecryptionInfo> future = QtConcurrent::run(run_encryption_decryption_test,runs, valueLower, valueUpper, logarithmic, traversal);
    watcher->setFuture(future);
}

void MainWindow::on_runMandelbrot_clicked(){
    if(!mandelbrotConfigDialog){
        mandelbrotConfigDialog = new RCDMandelbrot(this);
        connect(mandelbrotConfigDialog, &RCDMandelbrot::startBenchmarkParam, this, &MainWindow::startMandelbrotBenchmark);
    }
    mandelbrotConfigDialog -> show();
}

void MainWindow::startMandelbrotBenchmark(int runs, int valueLower, int valueUpper, int traversal){
    QFutureWatcher<mandelbrotInfo> *watcher = new QFutureWatcher<mandelbrotInfo>(this);

    connect(watcher, &QFutureWatcher<mandelbrotInfo>::finished, this, [=](){
        mandelbrotInfo result = watcher -> result();
        RESDMandelbrot* dlg = new RESDMandelbrot(this);
        dlg->setResults(result);

        int plotWidth = 1000;
        int plotHeight = 700;
        int plotMaxIter = 1000;


        std::vector<int> results = computeMandelbrotSetPlot(plotWidth, plotHeight, plotMaxIter);

        MandelbrotWidget *mandelWidget = new MandelbrotWidget(results,plotWidth,plotHeight,plotMaxIter);
        mandelWidget ->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
        mandelWidget->show();
        mandelbrotConfigDialog -> close();
        mandelbrotConfigDialog -> deleteLater();
        mandelbrotConfigDialog = nullptr;
        watcher->deleteLater();
    });
    QFuture<mandelbrotInfo> future = QtConcurrent::run(run_mandelbrot_test,runs,valueLower, valueUpper, traversal);
    watcher -> setFuture(future);
}

void MainWindow::on_runPcGrader_clicked(){
    if(!pcGraderConfigDialog){
        pcGraderConfigDialog = new RCDPcgrader(this);
        connect(pcGraderConfigDialog, &RCDPcgrader::startBenchmark, this, &MainWindow::startPcGraderBenchmark);
    }
    pcGraderConfigDialog -> show();
}

void MainWindow::startPcGraderBenchmark(){
    QFutureWatcher<pcGraderInfo> *watcher = new QFutureWatcher<pcGraderInfo>(this);

    connect(watcher, &QFutureWatcher<pcGraderInfo>::finished, this, [=](){
        pcGraderInfo result = watcher -> result();
        RESDPcgrader* dlg = new RESDPcgrader(this);
        dlg->setResults(result);

        int plotWidth = 1000;
        int plotHeight = 700;
        int plotMaxIter = 1000;

        std::vector<int> results = computeMandelbrotSetPlot(plotWidth, plotHeight, plotMaxIter);

        MandelbrotWidget *mandelWidget = new MandelbrotWidget(results,plotWidth,plotHeight,plotMaxIter);
        mandelWidget ->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
        mandelWidget->show();
        pcGraderConfigDialog -> close();
        pcGraderConfigDialog -> deleteLater();
        pcGraderConfigDialog = nullptr;
        watcher -> deleteLater();
    });
    QFuture<pcGraderInfo> future = QtConcurrent::run(grade_pc_bar);
    connect(watcher, &QFutureWatcher<pcGraderInfo>::progressValueChanged, pcGraderConfigDialog, &RCDPcgrader::set_progress_value);
    connect(watcher, &QFutureWatcher<pcGraderInfo>::progressRangeChanged, pcGraderConfigDialog, &RCDPcgrader::set_progress_range);

    watcher -> setFuture(future);
}


