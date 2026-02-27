#pragma once
#ifndef PCGRADER_H
#define PCGRADER_H
#include <QVector>
#include <QPromise>

typedef struct {
    //mem transfer
    int memtrs_runs;
    double memtrs_exec_time;
    double memtrs_mb_rate;
    QVector<double> memtrs_execTimes;
    QVector<double> memtrs_mbRates;
    QVector<int> memtrs_x_axis;

    //mem access
    int memacc_runs;
    double memacc_exec_time_best;
    long long memacc_ops_per_sec_best;
    double memacc_exec_time_worst;
    long long memacc_ops_per_sec_worst;
    QVector<double> memacc_execTimesBest;
    QVector<long long> memacc_opsBest;
    QVector<double> memacc_execTimesWorst;
    QVector<long long> memacc_opsWorst;
    QVector<int> memacc_x_axis_final;

    //encrdecr
    int encdec_runs;
    double encdec_exec_time;
    double encdec_ops_executed;
    double encdec_file_write_time;
    QVector<double> encdec_execTimes;
    QVector<double> encdec_ops;
    QVector<double> encdec_fileTimes;
    QVector<int> encdec_x_axis;

    //mandelbrot
    int mandel_runs;
    double mandel_exec_time;
    double mandel_ops_executed;
    QVector<double> mandel_execTimes;
    QVector<double> mandel_ops;
    QVector<int> mandel_x_axis;

    double final_grade;

} pcGraderInfo;

typedef struct {
    //mem transfer
    int memtrs_runs;
    double memtrs_exec_time;
    double memtrs_mb_rate;
    double memtrs_exec_time_weight;
    double memtrs_mb_rate_weight;
    double memtrs_exec_time_score;
    double memtrs_mb_rate_score;


    //mem access
    int memacc_runs;
    double memacc_exec_time_best;
    long long memacc_ops_per_sec_best;
    double memacc_exec_time_worst;
    long long memacc_ops_per_sec_worst;
    double memacc_exec_time_best_weight;
    double memacc_ops_per_sec_best_weight;
    double memacc_exec_time_worst_weight;
    double memacc_ops_per_sec_worst_weight;
    double memacc_exec_time_best_score;
    double memacc_ops_per_sec_best_score;
    double memacc_exec_time_worst_score;
    double memacc_ops_per_sec_worst_score;

    //encrdecr
    int encdec_runs;
    double encdec_exec_time;
    double encdec_ops_executed;
    double encdec_file_write_time;
    double encdec_exec_time_weight;
    double encdec_ops_executed_weight;
    double encdec_file_write_time_weight;
    double encdec_exec_time_score;
    double encdec_ops_executed_score;
    double encdec_file_write_time_score;

    //mandelbrot
    int mandel_runs;
    double mandel_exec_time;
    double mandel_ops_executed;
    double mandel_exec_time_weight;
    double mandel_ops_executed_weight;
    double mandel_exec_time_score;
    double mandel_ops_executed_score;


} pcGraderGrades;

pcGraderInfo grade_pc2();
void grade_pc_bar(QPromise<pcGraderInfo>& promise);

#endif // PCGRADER_H
