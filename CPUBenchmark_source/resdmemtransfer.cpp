#include "resdmemtransfer.h"
#include "ui_resdmemtransfer.h"
#include "chartFactory.h"
#include <QVBoxLayout>
#include <QDebug>

RESDMemtransfer::RESDMemtransfer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RESDMemtransfer)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

RESDMemtransfer::~RESDMemtransfer()
{
    delete ui;
}

void RESDMemtransfer::setResults(const MemTransferInfo& result){

    ui->tabWidget->clear();

    /*
    QWidget* summaryTab = new QWidget();
    QVBoxLayout* summaryLayout = new QVBoxLayout(summaryTab);
    summaryLayout->addWidget(new QLabel(QString("Average: %1 MB/s").arg(result.mb_rate,0,'f',2)));
    ui->tabWidget->addTab(summaryTab, "Summary");
    */

    QWidget* timeTab = new QWidget();
    QVBoxLayout* timeLayout = new QVBoxLayout(timeTab);
    timeLayout->addWidget(makeChartDouble(result.execTimes, result.x_axis, QString("Execution Time: %1 Runs").arg(result.runs), "Size (MB)", "Seconds",true));
    ui->tabWidget->addTab(timeTab,"Execution Time");

    QWidget* speedTab = new QWidget();
    QVBoxLayout* speedLayout = new QVBoxLayout(speedTab);
    speedLayout->addWidget(makeChartDouble(result.mbRates,result.x_axis, QString("Memory Transfer Rate: %1 Runs").arg(result.runs),"Size (MB)", "MB/s",false));
    ui->tabWidget->addTab(speedTab,"Transfer Rates");

    ui->label500->setText(QString("Memory Transfer results for %1MB of memory:").arg(result.x_axis.last()));
    ui->labelRuns->setText(QString("%1 Runs").arg(result.runs));
    ui->labelTime->setText(QString("AVG Time: %1 sec").arg(result.exec_time,0, 'f', 6));
    ui->labelSpeed->setText(QString("Transfer Rate: %L1 MB/s").arg(result.mb_rate,0,'f',2));


}
