#pragma once
#ifndef MANDELBROT_H
#define MANDELBROT_H
#include <vector>
#include <QImage>
#include "progress.h"

typedef struct {
    int runs;
    double exec_time;
    double ops_executed;

    QVector<double> execTimes;
    QVector<double> ops;
    QVector<int> x_axis;
} mandelbrotInfo;

mandelbrotInfo computeMandelbrotSetBench(int width, int height, int maxIter);
std::vector<int> computeMandelbrotSetPlot(int width, int height, int maxIter);
QImage makeImage(const std::vector<int>& iters, int width, int height, int maxIter);
mandelbrotInfo run_mandelbrot_test2(int runs);
mandelbrotInfo run_mandelbrot_test(int runs, int valueLower, int valueUpper, int traversal);
mandelbrotInfo run_mandelbrot_test_progress(int runs, int valueLower, int valueUpper, int traversal, ProgressFn progress_report);

#endif // MANDELBROT_H
