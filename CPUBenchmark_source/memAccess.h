#pragma once

#ifndef MEMACCESS_H
#define MEMACCESS_H
#include <QVector>
#include "progress.h"

typedef struct {
    int runs;
    double exec_time;
    long long ops_per_sec;
    QVector<double> execTimes;
    QVector<long long> ops;
    QVector<int> x_axis;
} MemAccessInfo;

typedef struct {
    int runs;
    double exec_time_best;
    long long ops_per_sec_best;
    double exec_time_worst;
    long long ops_per_sec_worst;
    bool logarithmic;

    QVector<double> execTimesBest;
    QVector<long long> opsBest;
    QVector<double> execTimesWorst;
    QVector<long long> opsWorst;
    QVector<int> x_axis_final;
} AllMemAccessInfo;


MemAccessInfo mem_access_test_best_case_size(int matSize, int runs);
MemAccessInfo run_mem_access_best_case_test2(int runs);
MemAccessInfo mem_access_test_worst_case_size(int matSize, int runs);
MemAccessInfo run_mem_access_worst_case_test2(int runs);
AllMemAccessInfo run_mem_access_test2(int runs);
AllMemAccessInfo run_mem_access_test(int runs, int valueLower, int valueUppper, bool logarithmic, int traversal);
AllMemAccessInfo run_mem_access_test_progress(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal, ProgressFn progress_report);
#endif // MEMACCESS_H
