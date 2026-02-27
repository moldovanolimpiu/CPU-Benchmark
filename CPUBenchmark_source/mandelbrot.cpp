#include <stdlib.h>
#include <iostream>
#include <vector>
#include <time.h>
#include "mandelbrot.h"
#include <QImage>

mandelbrotInfo computeMandelbrotSetBench(int width, int height, int maxIter) {
    const double xmin = -2.0;
    const double xmax = 1.0;
    const double ymin = -1.25;
    const double ymax = 1.25;

    const double dx = (xmax - xmin) / (width - 1);
    const double dy = (ymax - ymin) / (height - 1);

    mandelbrotInfo mand_data;
    mand_data.exec_time = 0.0;
    mand_data.ops_executed = 0;

    mandelbrotInfo failed_data;
    failed_data.exec_time = -1;
    failed_data.ops_executed = -1;

    clock_t time_start;
    clock_t time_end;
    clock_t time_dur;
    double time_float;
    int i, j;

    //std::vector<int> iters(width * height);

    long long totalIters = 0;

    time_start = clock();

    for (j = 0; j < height; j++) {
        const double cy = ymin + j * dy;
        for (i = 0; i < width; i++) {
            const double cx = xmin + i * dx;

            double x = 0.0;
            double y = 0.0;
            double x2 = 0.0;
            double y2 = 0.0;

            int iter = 0;

            while (iter < maxIter) {
                x2 = x * x;
                y2 = y * y;
                if (x2 + y2 > 4.0)
                    break;

                double xy = x * y;
                x = x2 - y2 + cx;
                y = 2.0 * xy + cy;

                iter++;
            }
            totalIters += iter;
        }
    }
    time_end = clock();
    time_dur = time_end - time_start;
    time_float = (double)time_dur / CLOCKS_PER_SEC;
    if(time_float <= 0){
        return failed_data;
    }
    mand_data.exec_time = time_float;
    double totalFlops = totalIters * 8.0;
    double MFLOPS = totalFlops / ((double)time_float * 1000000);
    mand_data.ops_executed = (double)MFLOPS;

    return mand_data;
}


std::vector<int> computeMandelbrotSetPlot(int width, int height, int maxIter) {
    const double xmin = -2.0;
    const double xmax = 1.0;
    const double ymin = -1.25;
    const double ymax = 1.25;

    const double dx = (xmax - xmin) / (width - 1);
    const double dy = (ymax - ymin) / (height - 1);

    mandelbrotInfo mand_data;
    mand_data.exec_time = 0.0;
    mand_data.ops_executed = 0;

    clock_t time_start;
    clock_t time_end;
    clock_t time_dur;
    double time_float;
    int i, j;

    std::vector<int> iters(width * height);

    long long totalIters = 0;

    time_start = clock();

    for (j = 0; j < height; j++) {
        const double cy = ymin + j * dy;
        for (i = 0; i < width; i++) {
            const double cx = xmin + i * dx;

            double x = 0.0;
            double y = 0.0;
            double x2 = 0.0;
            double y2 = 0.0;

            int iter = 0;

            while (iter < maxIter) {
                x2 = x * x;
                y2 = y * y;
                if (x2 + y2 > 4.0)
                    break;

                double xy = x * y;
                x = x2 - y2 + cx;
                y = 2.0 * xy + cy;

                iter++;
            }
            iters[j*width +i] = iter;
            totalIters += iter;
        }
    }
    time_end = clock();
    time_dur = time_end - time_start;
    time_float = (double)time_dur / CLOCKS_PER_SEC;
    mand_data.exec_time = time_float;
    double totalFlops = totalIters * 8.0;
    double MFLOPS = totalFlops / ((double)time_float * 1000000);
    mand_data.ops_executed = MFLOPS;

    return iters;
}

QImage makeImage(const std::vector<int>& iters, int width, int height, int maxIter){
    QImage img (width, height, QImage::Format_RGB32);

    for(int y = 0; y < height; y++){
        QRgb *row = reinterpret_cast<QRgb*>(img.scanLine(y));
        for(int x = 0; x < width; x++){
            int iter = iters[y * width + x];

            int v;

            if(iter == maxIter){
                    v = 0;
                }
            else{
                v = (int)(255.0*sqrt( (double)iter/maxIter) );
                }
            row[x] = qRgb(0, v, v);

        }
    }

    return img;
}


mandelbrotInfo run_mandelbrot_test2(int runs) {
    double timeSum = 0;
    double mflopSum = 0;

    mandelbrotInfo final_data;
    mandelbrotInfo mand_data;

    int i;
    int iterations;
    for(iterations = 500; iterations <= 1000; iterations += 100){
        for (i = 0; i < runs; i++) {
            mand_data = computeMandelbrotSetBench(1000, 1000, iterations);
            if(mand_data.exec_time == -1){
                while(mand_data.exec_time == -1){
                    mand_data = computeMandelbrotSetBench(1000,1000,iterations);
                }
            }
            timeSum += mand_data.exec_time;
            mflopSum += mand_data.ops_executed;
        }
        timeSum = timeSum / (double)runs;
        mflopSum = mflopSum / (double)runs;

        final_data.execTimes.append(timeSum);
        final_data.ops.append(mflopSum);
        final_data.x_axis.append(iterations);

        if(iterations == 1000){
            final_data.exec_time = timeSum;
            final_data.ops_executed = (double)mflopSum;
            final_data.runs = runs;
        }

    }
    return final_data;
}

mandelbrotInfo run_mandelbrot_test(int runs, int valueLower, int valueUpper, int traversal) {
    double timeSum = 0;
    double mflopSum = 0;
    int errorCount;
    mandelbrotInfo final_data;
    mandelbrotInfo mand_data;

    int i;
    int iterations;
    for(iterations = valueLower; iterations <= valueUpper; iterations += traversal){
        timeSum = 0;
        mflopSum = 0;
        for (i = 0; i < runs; i++) {
            mand_data = computeMandelbrotSetBench(1000, 1000, iterations);
            if(mand_data.exec_time == -1){
                errorCount = 10;
                while(mand_data.exec_time == -1 && errorCount > 0){
                    mand_data = computeMandelbrotSetBench(1000,1000,iterations);
                    errorCount--;
                }
            }
            timeSum += mand_data.exec_time;
            mflopSum += mand_data.ops_executed;
        }
        timeSum = timeSum / (double)runs;
        mflopSum = mflopSum / (double)runs;

        final_data.execTimes.append(timeSum);
        final_data.ops.append(mflopSum);
        final_data.x_axis.append(iterations);


    }
    final_data.exec_time = final_data.execTimes.last();
    final_data.ops_executed = final_data.ops.last();
    final_data.runs = runs;
    return final_data;
}


mandelbrotInfo run_mandelbrot_test_progress(int runs, int valueLower, int valueUpper, int traversal, ProgressFn progress_report) {
    double timeSum = 0;
    double mflopSum = 0;
    int errorCount;
    mandelbrotInfo final_data;
    mandelbrotInfo mand_data;

    int i;
    int iterations;
    for(iterations = valueLower; iterations <= valueUpper; iterations += traversal){
        timeSum = 0;
        mflopSum = 0;
        for (i = 0; i < runs; i++) {
            progress_report(1);
            mand_data = computeMandelbrotSetBench(1000, 1000, iterations);
            if(mand_data.exec_time == -1){
                errorCount = 10;
                while(mand_data.exec_time == -1 && errorCount > 0){
                    mand_data = computeMandelbrotSetBench(1000,1000,iterations);
                    errorCount--;
                }
            }
            timeSum += mand_data.exec_time;
            mflopSum += mand_data.ops_executed;
        }
        timeSum = timeSum / (double)runs;
        mflopSum = mflopSum / (double)runs;

        final_data.execTimes.append(timeSum);
        final_data.ops.append(mflopSum);
        final_data.x_axis.append(iterations);


    }
    final_data.exec_time = final_data.execTimes.last();
    final_data.ops_executed = final_data.ops.last();
    final_data.runs = runs;
    return final_data;
}

