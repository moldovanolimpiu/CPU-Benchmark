#include "resdmemaccess.h"
#include "ui_resdmemaccess.h"
#include "chartFactory.h"
#include <QVBoxLayout>

RESDMemaccess::RESDMemaccess(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RESDMemaccess)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

RESDMemaccess::~RESDMemaccess()
{
    delete ui;
}

void RESDMemaccess::setResults(const AllMemAccessInfo& result){

    ui->tabWidget->clear();

    QWidget* bestTimeTab = new QWidget();
    QVBoxLayout* bestTimeLayout = new QVBoxLayout(bestTimeTab);
    if(result.logarithmic){
        bestTimeLayout->addWidget(makeChartLogDouble(result.execTimesBest, result.x_axis_final, QString("Best Case Execution Time: %1 Runs").arg(result.runs), "Square Matrix Size", "Seconds",true));
    }else{
        bestTimeLayout->addWidget(makeChartDouble(result.execTimesBest, result.x_axis_final, QString("Best Case Execution Time: %1 Runs").arg(result.runs), "Square Matrix Size", "Seconds",true));
    }
    ui->tabWidget->addTab(bestTimeTab,"Best Case Execution Time");

    QWidget* bestOpsTab = new QWidget();
    QVBoxLayout* bestOpsLayout = new QVBoxLayout(bestOpsTab);
    if(result.logarithmic){
        bestOpsLayout->addWidget(makeChartLongLongLog(result.opsBest, result.x_axis_final, QString("Best Case Operations/Second: %1 Runs").arg(result.runs), "Square Matrix Size", "Operations"));
    }else{
        bestOpsLayout->addWidget(makeChartLongLong(result.opsBest, result.x_axis_final, QString("Best Case Operations/Second: %1 Runs").arg(result.runs), "Square Matrix Size", "Operations"));
    }
    ui->tabWidget->addTab(bestOpsTab,"Best Case Operations");

    QWidget* worstTimeTab = new QWidget();
    QVBoxLayout* worstTimeLayout = new QVBoxLayout(worstTimeTab);
    if(result.logarithmic){
        worstTimeLayout->addWidget(makeChartLogDouble(result.execTimesWorst, result.x_axis_final, QString("Worst Case Execution Time: %1 Runs").arg(result.runs), "Square Matrix Size", "Seconds",true));
    }else{
        worstTimeLayout->addWidget(makeChartDouble(result.execTimesWorst, result.x_axis_final, QString("Worst Case Execution Time: %1 Runs").arg(result.runs), "Square Matrix Size", "Seconds",true));
    }
    ui->tabWidget->addTab(worstTimeTab,"Worst Case Execution Time");

    QWidget* worstOpsTab = new QWidget();
    QVBoxLayout* worstOpsLayout = new QVBoxLayout(worstOpsTab);
    if(result.logarithmic){
        worstOpsLayout->addWidget(makeChartLongLongLog(result.opsWorst, result.x_axis_final, QString("Worst Case Operations/Second: %1 Runs").arg(result.runs), "Square Matrix Size", "Operations"));
    }else{
        worstOpsLayout->addWidget(makeChartLongLong(result.opsWorst, result.x_axis_final, QString("Worst Case Operations/Second: %1 Runs").arg(result.runs), "Square Matrix Size", "Operations"));
    }
    ui->tabWidget->addTab(worstOpsTab,"Worst Case Operations");

    ui->labelRuns->setText(QString("%1 Runs").arg(result.runs));
    ui->label->setText(QString("Results for Memory Access performed on a %1 x %1 square matrix:").arg(result.x_axis_final.last()));
    ui->labelBestTime->setText(QString("Best case AVG Time: %1 sec").arg(result.exec_time_best,0, 'f', 6));
    ui->labelBestOps->setText(QString("Best Case Accesses/s : %L1").arg(result.ops_per_sec_best));
    ui->labelWorstTime->setText(QString("Worst case AVG Time: %1 sec").arg(result.exec_time_worst,0, 'f', 6));
    ui->labelWorstOps->setText(QString("Worst Case Accesses/s : %L1").arg(result.ops_per_sec_worst));


}
