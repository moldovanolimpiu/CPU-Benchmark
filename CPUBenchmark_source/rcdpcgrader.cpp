#include "rcdpcgrader.h"
#include "ui_rcdpcgrader.h"

RCDPcgrader::RCDPcgrader(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RCDPcgrader)
{
    ui->setupUi(this);

    connect(ui -> btnStart, &QPushButton::clicked, this, &RCDPcgrader::onStartClicked);

    setWindowTitle("Configure Benchmark");
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->labelStandby->setText("");
    ui->labelClose->setText("");
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
    ui->label->setStyleSheet("font: 20pt");

}

RCDPcgrader::~RCDPcgrader()
{
    delete ui;
}

void RCDPcgrader::onStartClicked(){
    setRunning(false);
     ui->progressBar->show();
    emit startBenchmark();
    //accept();
}

void RCDPcgrader::setRunning(bool falseCond){
    ui->btnStart->setEnabled(falseCond);
    ui->labelStandby->setText("Standby... This might take a while (~5 minutes)");
    ui->labelClose->setText("Please do not close the application");
    if(!falseCond)
        setWindowTitle("Benchmark running...");
}

void RCDPcgrader::set_progress_value(int value) {
    ui->progressBar->setValue(value);
}

void RCDPcgrader::set_progress_range(int min, int max) {
    ui->progressBar->setRange(min, max);
}



