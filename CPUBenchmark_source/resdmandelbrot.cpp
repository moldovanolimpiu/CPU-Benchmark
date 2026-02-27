#include "resdmandelbrot.h"
#include "ui_resdmandelbrot.h"
#include "chartFactory.h"
#include "QVBoxLayout"

RESDMandelbrot::RESDMandelbrot(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RESDMandelbrot)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

RESDMandelbrot::~RESDMandelbrot()
{
    delete ui;
}

void RESDMandelbrot::setResults(const mandelbrotInfo& result){

    ui->tabWidget->clear();

    QWidget* timeTab = new QWidget();
    QVBoxLayout* timeLayout = new QVBoxLayout(timeTab);
    timeLayout->addWidget(makeChartDouble(result.execTimes, result.x_axis, QString("Execution Time: %1 Runs").arg(result.runs), "Iterations", "Seconds",true));
    ui->tabWidget->addTab(timeTab,"Execution Time");

    QWidget* opsTab = new QWidget();
    QVBoxLayout* opsLayout = new QVBoxLayout(opsTab);
    opsLayout->addWidget(makeChartDouble(result.ops,result.x_axis, QString("Millions of Floating Point ops/s: %1 Runs").arg(result.runs),"Iterations", "MFLOPS/s",false));
    ui->tabWidget->addTab(opsTab,"Floating Point Operations");

    ui->label->setText(QString("Results of computing the Mandelbrot set for %1 iterations:").arg(result.x_axis.last()));
    ui->labelRuns->setText(QString("%1 Runs").arg(result.runs));
    ui->labelTimeExec->setText(QString("AVG Exec. Time: %1 sec").arg(result.exec_time,0, 'f', 6));
    ui->labelMFLOPs->setText(QString("AVG MFLOP/s : %L1").arg(result.ops_executed,0,'f',2));
}
