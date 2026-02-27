#include "rcdmandelbrot.h"
#include "ui_rcdmandelbrot.h"

RCDMandelbrot::RCDMandelbrot(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RCDMandelbrot)
{
    ui->setupUi(this);

    connect(ui -> btnStart, &QPushButton::clicked, this, &RCDMandelbrot::onStartClicked);
    connect(ui->btnAutofill, &QPushButton::clicked, this, &RCDMandelbrot::onAutofillClicked);
    setWindowTitle("Configure Benchmark: Floating Point Operations");
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    ui->labelWarning->setText("");
    ui->labelWarning_2->setText("");
    ui->labelWarning_3->setText("");
    ui->progressBar->hide();
}

RCDMandelbrot::~RCDMandelbrot()
{
    delete ui;
}

void RCDMandelbrot::onStartClicked(){
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

    setRunning(false);
    //emit startBenchmark(runs);
    emit startBenchmarkParam(runs,valueLower,valueUpper,traversal);
    //accept();
}

void RCDMandelbrot::setRunning(bool falseCond){
    ui->btnStart->setEnabled(falseCond);
    ui->spinRuns->setEnabled(falseCond);
    ui->spinLower->setEnabled(falseCond);
    ui->spinUpper->setEnabled(falseCond);
    ui->spinLinear->setEnabled(falseCond);
    ui->btnAutofill->setEnabled(falseCond);
    if(!falseCond)
        setWindowTitle("Benchmark running...");
}

void RCDMandelbrot::onAutofillClicked(){
    ui->spinLower->setValue(500);
    ui->spinUpper->setValue(1000);
    ui->spinLinear->setValue(100);
    ui->spinRuns->setValue(10);
}

