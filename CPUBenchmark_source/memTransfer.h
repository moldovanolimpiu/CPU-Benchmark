#pragma once
#ifndef MEMTRANSFER_H
#define MEMTRANSFER_H
#include <QVector>
#include <QFuture>
#include "progress.h"

typedef struct {
    int runs;
    double exec_time;
    double mb_rate;

    QVector<double> execTimes;
    QVector<double> mbRates;
    QVector<int> x_axis;
} MemTransferInfo;

MemTransferInfo mem_transfer_test_size(int mb);
MemTransferInfo run_mem_transfer_test2(int runs);
MemTransferInfo run_mem_transfer_test(int runs, int valueLower, int valueUpper, int traversal);
void run_mem_transfer_test_bar(QPromise<MemTransferInfo> &promise, int runs, int valueLower, int valueUpper, int traversal);
MemTransferInfo run_mem_transfer_test_progress(int runs, int valueLower, int valueUpper, int traversal, ProgressFn progress_report);
#endif // MEMTRANSFER_H
