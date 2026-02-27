#include "rcdmemtransfer.h"
#include "ui_rcdmemtransfer.h"

RCDMemtransfer::RCDMemtransfer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RCDMemtransfer)
{
    ui->setupUi(this);

    connect(ui -> btnStart, &QPushButton::clicked, this, &RCDMemtransfer::onStartClicked);
    connect(ui->btnAutofill, &QPushButton::clicked, this, &RCDMemtransfer::onAutofillClicked);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowTitle("Configure Benchmark: Memory Transfer");
    ui->labelWarning->setText("");
    ui->labelWarning_2->setText("");
    ui->labelWarning_3->setText("");
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
}

RCDMemtransfer::~RCDMemtransfer()
{
    delete ui;
}

void RCDMemtransfer::onStartClicked(){
    int runs = ui->spinRuns->value();
    int valueLower = ui->spinLower->value();
    int valueUpper = ui->spinUpper->value();
    int traversal = ui->spinLinear->value();

    if(runs < 1){
        runs = 1;
    }
    if(runs >20){
        runs = 20;
    }
    if(valueLower >= valueUpper){
        ui->labelWarning->setText("ERROR! The Upper Index value must be");
        ui->labelWarning_2->setText("greater than the value of the");
        ui->labelWarning_3->setText("Lower Index!");
        return;
    }

    ui->labelWarning->setText("");
    ui->labelWarning_2->setText("");
    ui->labelWarning_3->setText("");
    //ui->progressBar->show();


    setRunning(false);
    //emit startBenchmark(runs);
    emit startBenchmarkParam(runs, valueLower, valueUpper, traversal);
    //accept();
}

void RCDMemtransfer::setRunning(bool falseCond){
    ui->btnStart->setEnabled(falseCond);
    ui->spinRuns->setEnabled(falseCond);
    ui->spinLower->setEnabled(falseCond);
    ui->spinUpper->setEnabled(falseCond);
    ui->spinLinear->setEnabled(falseCond);
    ui->btnAutofill->setEnabled(falseCond);
    if(!falseCond)
        setWindowTitle("Benchmark running...");
}


void RCDMemtransfer::onAutofillClicked(){
    ui->spinLower->setValue(500);
    ui->spinUpper->setValue(1500);
    ui->spinLinear->setValue(100);
    ui->spinRuns->setValue(10);
}

void RCDMemtransfer::set_progress_value(int value) {
    ui->progressBar->setValue(value);
}

void RCDMemtransfer::set_progress_range(int min, int max) {
    ui->progressBar->setRange(min, max);
}




