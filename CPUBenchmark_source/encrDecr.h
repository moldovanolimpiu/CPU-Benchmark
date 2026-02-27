#pragma once
#ifndef ENCRDECR_H
#define ENCRDECR_H
#include <QVector>
#include "progress.h"

typedef struct {
    int runs;
    double exec_time;
    double ops_executed;
    double file_write_time;
    char *inputFile;
    char *outputFile;
    bool logarithmic;

    QVector<double> execTimes;
    QVector<double> ops;
    QVector<double> fileTimes;
    QVector<int> x_axis;
} encryptionDecryptionInfo;

encryptionDecryptionInfo read_file_encr_size(int fileSize);
encryptionDecryptionInfo read_file_decr_size(int fileSize);
encryptionDecryptionInfo run_encryption_decryption_test2(int runs);
encryptionDecryptionInfo run_encryption_decryption_test(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal);
encryptionDecryptionInfo run_encryption_decryption_test_progress(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal, ProgressFn progress_report);
#endif // ENCRDECR_H
