#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "memTransfer.h"
#include <QFuture>
#include "progress.h"


MemTransferInfo mem_transfer_test_size(int mb, int runs){
    MemTransferInfo test_res;
    test_res.exec_time = -1;
    test_res.mb_rate = -1;
    MemTransferInfo failed_test;
    test_res.exec_time = -1;
    test_res.mb_rate = -1;
    clock_t time_start;
    clock_t time_end;
    clock_t time_dur = 0;
    double time_float;
    double mbps;
    size_t mem_size = mb * 1024 * 1024;
    char* ptr = (char*)malloc(mem_size);
    char* ptrcpy = (char*)malloc(mem_size);

    if (ptr == NULL || ptrcpy == NULL) {
        free(ptr);
        free(ptrcpy);
        return test_res;
    }
    memset(ptr,0xAA, mem_size);
    memcpy(ptrcpy, ptr, mem_size);

    volatile unsigned char sink;
    for(int i = 0; i < runs;i++){
        time_start = clock();
        memcpy(ptrcpy, ptr, mem_size);
        time_end = clock();
        sink = ptrcpy[5];
        time_dur += (time_end - time_start);
    }




    //time_dur = time_end - time_start;
    time_float = (double)time_dur / CLOCKS_PER_SEC;
    if(time_float <=0){
        free(ptr);
        free(ptrcpy);
        ptr = NULL;
        ptrcpy = NULL;
        return failed_test;
    }
    mbps = (mem_size / (1024 * 1024)) / time_float;
    test_res.exec_time = time_float;
    test_res.mb_rate = mbps;

    free(ptr);
    free(ptrcpy);
    ptr = NULL;
    ptrcpy = NULL;
    return test_res;

}


MemTransferInfo run_mem_transfer_test2(int runs) {
    double timeSum = 0;
    double rateSum = 0;

    MemTransferInfo current_mem_data;
    MemTransferInfo final_mem_data;
    final_mem_data.exec_time = 0;
    final_mem_data.mb_rate = 0;

    for(int memSize = 500; memSize <= 1000; memSize +=100){
        timeSum = 0;
        rateSum = 0;
        //for (int i = 0; i < runs; i++) {
            current_mem_data = mem_transfer_test_size(memSize,runs);
            if (current_mem_data.exec_time < 0) {
                while (current_mem_data.exec_time < 0) {
                    current_mem_data = mem_transfer_test_size(memSize,runs);
                }
            }
            timeSum += current_mem_data.exec_time;
            rateSum += current_mem_data.mb_rate;
        //}
        timeSum = timeSum / (double)runs;
        rateSum = rateSum / (double)runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.mbRates.append(rateSum);
        final_mem_data.x_axis.append(memSize);
        if(memSize == 500){
            final_mem_data.runs = runs;
            final_mem_data.exec_time = timeSum;
            final_mem_data.mb_rate = rateSum;
        }

    }

    return final_mem_data;

}

MemTransferInfo run_mem_transfer_test(int runs, int valueLower, int valueUpper, int traversal) {
    double timeSum;
    double rateSum;

    MemTransferInfo current_mem_data;
    MemTransferInfo final_mem_data;
    final_mem_data.exec_time = 0;
    final_mem_data.mb_rate = 0;
    for(int memSize = valueLower; memSize <= valueUpper; memSize +=traversal){
        current_mem_data = mem_transfer_test_size(memSize,runs);
        if (current_mem_data.exec_time <= 0) {
            while (current_mem_data.exec_time <= 0) {
                qInfo("error");
                current_mem_data = mem_transfer_test_size(memSize,runs);
            }
        }
        timeSum = current_mem_data.exec_time;
        rateSum = current_mem_data.mb_rate;
        timeSum = timeSum / (double)runs;
        rateSum = rateSum / (double)runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.mbRates.append(rateSum);
        final_mem_data.x_axis.append(memSize);

    }
    final_mem_data.runs = runs;
    final_mem_data.exec_time = final_mem_data.execTimes.last();
    final_mem_data.mb_rate = final_mem_data.mbRates.last();

    return final_mem_data;
}

void run_mem_transfer_test_bar(QPromise<MemTransferInfo> &promise, int runs, int valueLower, int valueUpper, int traversal) {
    double timeSum;
    double rateSum;
    int total_bar_steps = 0;
    int bar_steps = 0;
    int memSize;
    for(memSize = valueLower; memSize<= valueUpper; memSize += traversal){
        total_bar_steps ++;
    }
    promise.setProgressRange(0, total_bar_steps);
    MemTransferInfo current_mem_data;
    MemTransferInfo final_mem_data;
    final_mem_data.exec_time = 0;
    final_mem_data.mb_rate = 0;

    for(memSize = valueLower; memSize <= valueUpper; memSize +=traversal){
        current_mem_data = mem_transfer_test_size(memSize,runs);
        if (current_mem_data.exec_time <= 0) {
            while (current_mem_data.exec_time <= 0) {
                qInfo("error");
                current_mem_data = mem_transfer_test_size(memSize,runs);
            }
        }
        bar_steps++;
        promise.setProgressValue(bar_steps);
        timeSum = current_mem_data.exec_time;
        rateSum = current_mem_data.mb_rate;
        timeSum = timeSum / (double)runs;
        rateSum = rateSum / (double)runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.mbRates.append(rateSum);
        final_mem_data.x_axis.append(memSize);

    }
    final_mem_data.runs = runs;
    final_mem_data.exec_time = final_mem_data.execTimes.last();
    final_mem_data.mb_rate = final_mem_data.mbRates.last();
    //future.reportResult(final_mem_data);
    promise.addResult(final_mem_data);
    //return final_mem_data;
}


MemTransferInfo run_mem_transfer_test_progress(int runs, int valueLower, int valueUpper, int traversal, ProgressFn progress_report) {
    double timeSum;
    double rateSum;

    MemTransferInfo current_mem_data;
    MemTransferInfo final_mem_data;
    final_mem_data.exec_time = 0;
    final_mem_data.mb_rate = 0;
    for(int memSize = valueLower; memSize <= valueUpper; memSize +=traversal){
        current_mem_data = mem_transfer_test_size(memSize,runs);
        if (current_mem_data.exec_time <= 0) {
            while (current_mem_data.exec_time <= 0) {
                qInfo("error");
                current_mem_data = mem_transfer_test_size(memSize,runs);
            }
        }
        timeSum = current_mem_data.exec_time;
        rateSum = current_mem_data.mb_rate;
        timeSum = timeSum / (double)runs;
        rateSum = rateSum / (double)runs;
        progress_report(1);
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.mbRates.append(rateSum);
        final_mem_data.x_axis.append(memSize);

    }
    final_mem_data.runs = runs;
    final_mem_data.exec_time = final_mem_data.execTimes.last();
    final_mem_data.mb_rate = final_mem_data.mbRates.last();

    return final_mem_data;
}



