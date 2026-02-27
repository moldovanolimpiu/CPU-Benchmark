#include "resdencrdecr.h"
#include "ui_resdencrdecr.h"
#include "chartFactory.h"
#include <QVBoxLayout>

RESDEncrdecr::RESDEncrdecr(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RESDEncrdecr)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

RESDEncrdecr::~RESDEncrdecr()
{
    delete ui;
}

void RESDEncrdecr::setResults(const encryptionDecryptionInfo& result){

    ui->tabWidget->clear();

    QWidget* execTimeTab = new QWidget();
    QVBoxLayout* execTimeLayout = new QVBoxLayout(execTimeTab);
    if(result.logarithmic){
        execTimeLayout->addWidget(makeChartLogDouble(result.execTimes, result.x_axis, QString("Execution Time: %1 Runs").arg(result.runs), "File Size (MB)", "Seconds",true));
    }else{
        execTimeLayout->addWidget(makeChartDouble(result.execTimes, result.x_axis, QString("Execution Time: %1 Runs").arg(result.runs), "File Size (MB)", "Seconds",true));
    }
    ui->tabWidget->addTab(execTimeTab,"Execution Time");

    QWidget* opsTab = new QWidget();
    QVBoxLayout* opsLayout = new QVBoxLayout(opsTab);
    if(result.logarithmic){
        opsLayout->addWidget(makeChartLogDouble(result.ops, result.x_axis, QString("Millions of INT Ops/s: %1 Runs").arg(result.runs), "File Size (MB)", "Average MINTOPS/s",false));
    }else{
        opsLayout->addWidget(makeChartDouble(result.ops, result.x_axis, QString("Millions of INT Ops/s: %1 Runs").arg(result.runs), "File Size (MB)", "Average MINTOPS/s",false));
    }
    ui->tabWidget->addTab(opsTab,"Operations");

    QWidget* fileTimeTab = new QWidget();
    QVBoxLayout* fileTimeLayout = new QVBoxLayout(fileTimeTab);
    if(result.logarithmic){
        fileTimeLayout->addWidget(makeChartLogDouble(result.fileTimes, result.x_axis, QString("Output File Write Time: %1 Runs").arg(result.runs), "File Size (MB)", "Seconds",true));
    }else{
        fileTimeLayout->addWidget(makeChartDouble(result.fileTimes, result.x_axis, QString("Output File Write Time: %1 Runs").arg(result.runs), "File Size (MB)", "Seconds",true));
    }

    ui->tabWidget->addTab(fileTimeTab,"File Write Time");


    ui->labelRuns->setText(QString("%1 Runs").arg(result.runs));

    ui->label->setText(QString("Results for Encryption and Decryption on a %1MB file").arg(result.x_axis.last()));
    ui->labelTimeExec->setText(QString("AVG Exec. Time: %1 sec").arg(result.exec_time,0, 'f', 6));
    ui->labelOpExec->setText(QString("AVG MINTOP/s : %L1").arg(result.ops_executed,0,'f',2));
    ui->labelTimeWrite->setText(QString("AVG File Write Time: %1 sec").arg(result.file_write_time,0, 'f', 6));


}
