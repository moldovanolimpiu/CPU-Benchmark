#include "resdpcgrader.h"
#include "ui_resdpcgrader.h"
#include "chartFactory.h"
#include <QVBoxLayout>



RESDPcgrader::RESDPcgrader(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RESDPcgrader)
{
    ui->setupUi(this);
    connect(ui -> btnSaveCharts, &QPushButton::clicked, this, &RESDPcgrader::saveChartList);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
}

RESDPcgrader::~RESDPcgrader()
{
    delete ui;
}

void RESDPcgrader::setResults(const pcGraderInfo& result){

    ui->tabWidget->clear();
    saved_charts.clear();
    saved_names.clear();

    //memory transfer
    QWidget* memtrs_time_tab = new QWidget();
    QVBoxLayout* memtrs_time_layout = new QVBoxLayout(memtrs_time_tab);
    QChartView* memtrs_time_chart = makeChartDouble(result.memtrs_execTimes, result.memtrs_x_axis, QString("Memory Transfer Execution Time: %1 Runs").arg(result.memtrs_runs), "Size (MB)", "Seconds",true);
    saved_charts.append(memtrs_time_chart);
    saved_names.append("1_MT_Execution_Time");
    memtrs_time_layout->addWidget(memtrs_time_chart);
    ui->tabWidget->addTab(memtrs_time_tab,"MT Execution Time");

    QWidget* memtrs_speed_tab = new QWidget();
    QVBoxLayout* memtrs_speed_layout = new QVBoxLayout(memtrs_speed_tab);
    QChartView* memtrs_speed_chart = makeChartDouble(result.memtrs_mbRates,result.memtrs_x_axis, QString("Memory Transfer Rate: %1 Runs").arg(result.memtrs_runs),"Size (MB)", "MB/s",false);
    saved_charts.append(memtrs_speed_chart);
    saved_names.append("2_MT_Transfer_Rates");
    memtrs_speed_layout->addWidget(memtrs_speed_chart);
    ui->tabWidget->addTab(memtrs_speed_tab,"MT Transfer Rates");

    //memory access
    QWidget* memacc_best_time_tab = new QWidget();
    QVBoxLayout* memacc_best_time_layout = new QVBoxLayout(memacc_best_time_tab);
    QChartView* memacc_best_time_chart = makeChartDouble(result.memacc_execTimesBest, result.memacc_x_axis_final, QString("Memory Access Best Case Execution Time: %1 Runs").arg(result.memacc_runs), "Square Matrix Size", "Seconds",true);
    saved_charts.append(memacc_best_time_chart);
    saved_names.append("3_MA_Best_Case_Execution_Time");
    memacc_best_time_layout->addWidget(memacc_best_time_chart);
    ui->tabWidget->addTab(memacc_best_time_tab,"MA Best Case Execution Time");

    QWidget* memacc_best_ops_tab = new QWidget();
    QVBoxLayout* memacc_best_ops_layout = new QVBoxLayout(memacc_best_ops_tab);
    QChartView* memacc_best_ops_chart = makeChartLongLong(result.memacc_opsBest, result.memacc_x_axis_final, QString("Memory Access Best Case Operations/Second: %1 Runs").arg(result.memacc_runs), "Square Matrix Size", "Operations");
    saved_charts.append(memacc_best_ops_chart);
    saved_names.append("4_MA_Best_Case_Operations");
    memacc_best_ops_layout->addWidget(memacc_best_ops_chart);
    ui->tabWidget->addTab(memacc_best_ops_tab,"MA Best Case Operations");

    QWidget* memacc_worst_time_tab = new QWidget();
    QVBoxLayout* memacc_worst_time_layout = new QVBoxLayout(memacc_worst_time_tab);
    QChartView* memacc_worst_time_chart = makeChartDouble(result.memacc_execTimesWorst, result.memacc_x_axis_final, QString("Memory Access Worst Case Execution Time: %1 Runs").arg(result.memacc_runs), "Square Matrix Size", "Seconds",true);
    saved_charts.append(memacc_worst_time_chart);
    saved_names.append("5_MA_Worst_Case_Execution_Time");
    memacc_worst_time_layout->addWidget(memacc_worst_time_chart);
    ui->tabWidget->addTab(memacc_worst_time_tab,"MA Worst Case Execution Time");

    QWidget* memacc_worst_ops_tab = new QWidget();
    QVBoxLayout* memacc_worst_ops_layout = new QVBoxLayout(memacc_worst_ops_tab);
    QChartView* memacc_worst_ops_chart = makeChartLongLong(result.memacc_opsWorst, result.memacc_x_axis_final, QString("Memory Access Worst Case Operations/Second: %1 Runs").arg(result.memacc_runs), "Square Matrix Size", "Operations");
    saved_charts.append(memacc_worst_ops_chart);
    saved_names.append("6_MA_Worst_Case_Operations");
    memacc_worst_ops_layout->addWidget(memacc_worst_ops_chart);
    ui->tabWidget->addTab(memacc_worst_ops_tab,"MA Worst Case Operations");

    //integer operations
    QWidget* encdec_exec_time_tab = new QWidget();
    QVBoxLayout* encdec_exec_time_layout = new QVBoxLayout(encdec_exec_time_tab);
    QChartView* encdec_exec_time_chart = makeChartLogDouble(result.encdec_execTimes, result.encdec_x_axis, QString("Encryption/Decryption Execution Time: %1 Runs").arg(result.encdec_runs), "File Size (MB)", "Seconds",true);
    saved_charts.append(encdec_exec_time_chart);
    saved_names.append("7_INTOPS_Execution_Time");
    encdec_exec_time_layout->addWidget(encdec_exec_time_chart);
    ui->tabWidget->addTab(encdec_exec_time_tab,"INTOPS Execution Time");

    QWidget* encdec_ops_tab = new QWidget();
    QVBoxLayout* encdec_ops_layout = new QVBoxLayout(encdec_ops_tab);
    QChartView* encdec_ops_chart = makeChartLogDouble(result.encdec_ops, result.encdec_x_axis, QString("Encryption/Decryption Millions of INT Ops/s: %1 Runs").arg(result.encdec_runs), "File Size (MB)", "Average MINTOPS/s",false);
    saved_charts.append(encdec_ops_chart);
    saved_names.append("8_INTOPS_Operations");
    encdec_ops_layout->addWidget(encdec_ops_chart);
    ui->tabWidget->addTab(encdec_ops_tab,"INTOPS Operations");

    QWidget* encdec_file_time_tab = new QWidget();
    QVBoxLayout* encdec_file_time_layout = new QVBoxLayout(encdec_file_time_tab);
    QChartView* encdec_file_time_chart = makeChartLogDouble(result.encdec_fileTimes, result.encdec_x_axis, QString("Encryption/Decryption Output File Write Time: %1 Runs").arg(result.encdec_runs), "File Size (MB)", "Seconds",true);
    saved_charts.append(encdec_file_time_chart);
    saved_names.append("9_INTOPS_File_Write_Time");
    encdec_file_time_layout->addWidget(encdec_file_time_chart);
    ui->tabWidget->addTab(encdec_file_time_tab,"INTOPS File Write Time");

    //floating point operations

    QWidget* mandel_time_tab = new QWidget();
    QVBoxLayout* mandel_time_layout = new QVBoxLayout(mandel_time_tab);
    QChartView* mandel_time_chart = makeChartDouble(result.mandel_execTimes, result.mandel_x_axis, QString("Mandelbrot Set Execution Time: %1 Runs").arg(result.mandel_runs), "Iterations", "Seconds",true);
    saved_charts.append(mandel_time_chart);
    saved_names.append("10_FLOPS_Execution_Time");
    mandel_time_layout->addWidget(mandel_time_chart);
    ui->tabWidget->addTab(mandel_time_tab ,"FLOPS Execution Time");

    QWidget* mandel_ops_tab = new QWidget();
    QVBoxLayout* mandel_ops_layout = new QVBoxLayout(mandel_ops_tab);
    QChartView* mandel_ops_chart = makeChartDouble(result.mandel_ops,result.mandel_x_axis, QString("Mandelbrot Set Millions of Floating Point ops/s: %1 Runs").arg(result.mandel_runs),"Iterations", "MFLOPS/s",false);
    saved_charts.append(mandel_ops_chart);
    saved_names.append("11_FLOPS_Operations");
    mandel_ops_layout->addWidget(mandel_ops_chart);
    ui->tabWidget->addTab(mandel_ops_tab,"FLOPS Operations");




    ui->labelMemTransferText->setText(QString("Memory Transfer results for %1MB of memory:").arg(result.memtrs_x_axis.last()));
    ui->labelMemtrsRuns->setText(QString("%1 Runs").arg(result.memtrs_runs));
    ui->labelMemtrsTimeExec->setText(QString("AVG Time: %1 sec").arg(result.memtrs_exec_time,0, 'f', 6));
    ui->labelMemtrsMBRate->setText(QString("Transfer Rate: %L1 MB/s").arg(result.memtrs_mb_rate,0,'f',2));

    ui->labelMemaccText->setText(QString("Results for Memory Access performed on a %1 x %1 square matrix:").arg(result.memacc_x_axis_final.last()));
    ui->labelMemaccRuns->setText(QString("%1 Runs").arg(result.memacc_runs));
    ui->labelMemaccTimeBest->setText(QString("Best Case AVG Time: %1 sec").arg(result.memacc_exec_time_best,0, 'f', 6));
    ui->labelMemaccOpsBest->setText(QString("Best Case Accesses/s: %L1").arg(result.memacc_ops_per_sec_best));
    ui->labelMemaccTimeWorst->setText(QString("Worst Case AVG Time: %1 sec").arg(result.memacc_exec_time_worst,0, 'f', 6));
    ui->labelMemaccOpsWorst->setText(QString("Worst Case Accesses/s: %L1").arg(result.memacc_ops_per_sec_worst));

    ui->labelIntText->setText(QString("Results for Encryption and Decryption on a %1MB file").arg(result.encdec_x_axis.last()));
    ui->labelIntRuns->setText(QString("%1 Runs").arg(result.encdec_runs));
    ui->labelIntTimeExec->setText(QString("AVG Time: %1 sec").arg(result.encdec_exec_time,0, 'f', 6));
    ui->labelIntOpsExec->setText(QString("AVG MINTOP/s : %L1").arg(result.encdec_ops_executed,0,'f',2));
    ui->labelIntTimeWrite->setText(QString("AVG File Write Time: %1 sec").arg(result.encdec_file_write_time,0, 'f', 6));

    ui->labelFlopText->setText(QString("Results of computing the Mandelbrot set for %1 iterations:").arg(result.mandel_x_axis.last()));
    ui->labelFlopRuns->setText(QString("%1 Runs").arg(result.mandel_runs));
    ui->labelFlopTimeExec->setText(QString("AVG Exec. Time: %1 sec").arg(result.mandel_exec_time,0, 'f', 6));
    ui->labelFlopOpsExec->setText(QString("AVG MFLOP/s : %L1").arg(result.mandel_ops_executed,0,'d',1));

    ui->textEdit->setText(QString("%1").arg(result.final_grade,0,'f',2));
    ui->textEdit->setStyleSheet(QStringLiteral("font: 26pt"));
    ui->label->setStyleSheet("font:20pt");
}

void RESDPcgrader::saveChartList(){
    for(int i = 0; i < saved_names.size(); i++){
        saveChart(saved_charts[i],saved_names[i],this);
    }

}
