#include "rcdencrdecr.h"
#include "ui_rcdencrdecr.h"

RCDEncrdecr::RCDEncrdecr(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RCDEncrdecr)
{
    ui->setupUi(this);

    connect(ui -> btnStart, &QPushButton::clicked, this, &RCDEncrdecr::onStartClicked);
    connect(ui -> comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RCDEncrdecr::onModeChanged);
    connect(ui->btnAutofill, &QPushButton::clicked, this, &RCDEncrdecr::onAutofillClicked);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowTitle("Configure Benchmark: Integer Operations");
    ui->labelWarning->setText("");
    ui->labelWarning_2->setText("");
    ui->labelWarning_3->setText("");
    onModeChanged(ui->comboBox->currentIndex());
    ui->progressBar->hide();
}

RCDEncrdecr::~RCDEncrdecr()
{
    delete ui;
}

void RCDEncrdecr::onStartClicked(){
    int runs = ui->spinRuns->value();
    int valueLower = ui->spinLower->value();
    int valueUpper = ui->spinUpper->value();
    bool logarithmic;
    int traversal;
    int index = ui->comboBox->currentIndex();
    if(index == 0){
        logarithmic = false;
        traversal = ui->spinLinear->value();
    }else{
        logarithmic = true;
        traversal = 2;
    }
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
    emit startBenchmarkParam(runs,valueLower,valueUpper,logarithmic,traversal);
    //accept();
}

void RCDEncrdecr::setRunning(bool falseCond){
    ui->btnStart->setEnabled(falseCond);
    ui->spinRuns->setEnabled(falseCond);
    ui->comboBox->setEnabled(falseCond);
    ui->spinLower->setEnabled(falseCond);
    ui->spinUpper->setEnabled(falseCond);
    ui->spinLinear->setEnabled(falseCond);
    ui->btnAutofill->setEnabled(falseCond);
    if(!falseCond)
        setWindowTitle("Benchmark running...");
}

void RCDEncrdecr::onModeChanged(int type){
    switch(type){
    case 0:
        ui->spinRuns->setEnabled(true);
        ui->spinLinear->setEnabled(true);
        //ui->spinLogarithmic->setEnabled(false);
        ui->labelLinear->setEnabled(true);
        ui->labelLog->setEnabled(false);
        ui->comboBox->setCurrentIndex(type);
        break;
    default:
        ui->spinRuns->setEnabled(true);
        ui->spinLinear->setEnabled(false);
        //ui->spinLogarithmic->setEnabled(true);
        ui->labelLinear->setEnabled(false);
        ui->labelLog->setEnabled(true);
        ui->comboBox->setCurrentIndex(type);
        break;
    }
}

void RCDEncrdecr::onAutofillClicked(){
    ui->spinLower->setValue(8);
    ui->spinUpper->setValue(128);
    onModeChanged(1);
    ui->spinRuns->setValue(10);
}
