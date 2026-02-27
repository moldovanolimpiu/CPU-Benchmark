#include "cpuidwindow.h"
#include "ui_cpuidwindow.h"
#include "cpuidentification.h"
#include "cacheinfo.h"

cpuidwindow::cpuidwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cpuidwindow)
{
    ui->setupUi(this);
    ui->lineEditVendor->setText(CPUVendor());
    ui->lineEditBrand->setText(BrandString());
    setWindowTitle("CPU Identification");

    //cache
    CacheInfo cinfo1 = cacheInfo(0);
    CacheInfo cinfo2 = cacheInfo(1);
    CacheInfo cinfo3 = cacheInfo(2);
    CacheInfo cinfo4 = cacheInfo(3);
    ui->lineEditCCL1D->setText(cinfo1.size_share);
    ui->lineEditCCL1DW->setText(cinfo1.way);
    ui->lineEditCCL1I->setText(cinfo2.size_share);
    ui->lineEditCCL1IW->setText(cinfo2.way);
    ui->lineEditCCL2U->setText(cinfo3.size_share);
    ui->lineEditCCL2UW->setText(cinfo3.way);
    ui->lineEditCCL3U->setText(cinfo4.size_share);
    ui->lineEditCCL3UW->setText(cinfo4.way);

    //TFM
    ui->lineEditStepping->setText(typeFamilyModel(0));
    ui->lineEditType->setText(typeFamilyModel(3));
    ui->lineEditModel->setText(typeFamilyModel(1));
    ui->lineEditExtMod->setText(typeFamilyModel(4));
    ui->lineEditFamily->setText(typeFamilyModel(2));
    ui->lineEditExtFam->setText(typeFamilyModel(5));

    ui->lineEditArchi->setText(architecture());
    ui->lineEditPageSize->setText(pageSize());

    ui->lineEditFBase->setText(frequencies(0));
    ui->lineEditFMax->setText(frequencies(1));
    ui->lineEditFBus->setText(frequencies(2));

    ui->lineEditCores->setText(coreNumberChar());
    ui->lineEditThreads->setText(threadNumber());

}

cpuidwindow::~cpuidwindow()
{
    delete ui;
}
