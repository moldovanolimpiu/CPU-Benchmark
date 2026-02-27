#include "rcdmemaccess.h"
#include "ui_rcdmemaccess.h"

RCDMemaccess::RCDMemaccess(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RCDMemaccess)
{
    ui->setupUi(this);

    connect(ui -> btnStart, &QPushButton::clicked, this, &RCDMemaccess::onStartClicked);
    connect(ui -> comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RCDMemaccess::onModeChanged);
    connect(ui->btnAutofill, &QPushButton::clicked, this, &RCDMemaccess::onAutofillClicked);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    setWindowTitle("Configure Benchmark: Memory Access");
    ui->labelWarning->setText("");
    ui->labelWarning_2->setText("");
    ui->labelWarning_3->setText("");
    onModeChanged(ui->comboBox->currentIndex());
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);
    ui->progressBar->hide();
}

RCDMemaccess::~RCDMemaccess()
{
    delete ui;
}

void RCDMemaccess::onStartClicked(){
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
    //ui->progressBar->show();
    setRunning(false);
    //emit startBenchmark(runs);
    emit startBenchmarkParam(runs, valueLower, valueUpper, logarithmic, traversal);
    //accept();
}

void RCDMemaccess::setRunning(bool falseCond){
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

void RCDMemaccess::onModeChanged(int type){
    switch(type){
    case 0:
        ui->spinRuns->setEnabled(true);
        ui->spinLinear->setEnabled(true);
        ui->labelLinear->setEnabled(true);
        ui->labelLog->setEnabled(false);
        ui->comboBox->setCurrentIndex(type);
        break;
    default:
        ui->spinRuns->setEnabled(true);
        ui->spinLinear->setEnabled(false);
        ui->labelLinear->setEnabled(false);
        ui->labelLog->setEnabled(true);
        ui->comboBox->setCurrentIndex(type);
        break;
    }
}

void RCDMemaccess::onAutofillClicked(){
    ui->spinLower->setValue(2048);
    ui->spinUpper->setValue(16384);
    onModeChanged(0);
    ui->spinLinear->setValue(1024);
    ui->spinRuns->setValue(10);
}

void RCDMemaccess::set_progress_value(int value) {
    ui->progressBar->setValue(value);
}

void RCDMemaccess::set_progress_range(int min, int max) {
    ui->progressBar->setRange(min, max);
}
