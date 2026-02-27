#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memAccess.h"
#include <QDebug>
#include "progress.h"

void free_alloc_mem(int** mem_mat, int index) {
    for (int i = 0; i < index; i++) {
        free(mem_mat[i]);
    }
}


MemAccessInfo mem_access_test_best_case_size(int matSize, int runs) {
    clock_t time_start;
    clock_t time_end;
    clock_t time_dur = 0;
    MemAccessInfo mem_data;
    mem_data.exec_time = -1;
    mem_data.ops_per_sec = -1;
    double time_float;
    long long op_per_sec;
    int mat_size_rows = matSize+1;
    int mat_size_columns = matSize;
    long long ops_total = (long long)(mat_size_rows - 1) * mat_size_columns * runs;
    int i, j, k;

    int** mem_mat = (int**)malloc(mat_size_rows * sizeof(int*));

    if (mem_mat == NULL) {
        printf("Allocation failed. Retrying...\n");
        return mem_data;
    }
    for (i = 0; i < mat_size_rows; i++) {
        mem_mat[i] = (int*)malloc(mat_size_columns * sizeof(int));
        if (mem_mat[i] == NULL) {
            free_alloc_mem(mem_mat, i);
            free(mem_mat);
            mem_mat = NULL;
            return mem_data;
        }
    }

    for(k = 0; k < runs; k ++){

        for (i = 0; i < mat_size_rows; i++)
            for (j = 0; j < mat_size_columns; j++)
                mem_mat[i][j] = 0;

        time_start = clock();
        for (i = 1; i < mat_size_rows; i++) {
            for (j = 0; j < mat_size_columns; j++) {
                mem_mat[i][j] = mem_mat[i - 1][j] + 1;
            }
        }

        time_end = clock();
        time_dur += (time_end - time_start);
    }


    time_float = (double)time_dur/CLOCKS_PER_SEC;

    if(time_float==0){
        free_alloc_mem(mem_mat, mat_size_rows);
        free(mem_mat);
        mem_mat = NULL;
        mem_data.exec_time = -1;
        mem_data.ops_per_sec = -1;
        return mem_data;
    }

    op_per_sec = ops_total / time_float;

    mem_data.exec_time = time_float;
    mem_data.ops_per_sec = op_per_sec;

    free_alloc_mem(mem_mat, mat_size_rows);
    free(mem_mat);
    mem_mat = NULL;

    return mem_data;

}


MemAccessInfo run_mem_access_best_case_test2(int runs) {
    double timeSum;
    long long opsSum;
    double currentValue;
    MemAccessInfo mem_data;
    MemAccessInfo final_mem_data;

    for(int matSize = 1024; matSize <= 16384; matSize = matSize * 2){
        timeSum = 0;
        opsSum = 0;
        //for (int i = 0; i < runs; i++) {
            mem_data = mem_access_test_best_case_size(matSize, runs);
            if (mem_data.exec_time < 0) {
                while (mem_data.exec_time < 0) {
                    mem_data = mem_access_test_best_case_size(matSize, runs);
                }
            }
            timeSum += mem_data.exec_time;
            opsSum += mem_data.ops_per_sec;
        //}
        timeSum = timeSum / (double)runs;
        opsSum = opsSum / runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.ops.append(opsSum);
        final_mem_data.x_axis.append(matSize);
        if(matSize == 4096){
            final_mem_data.runs = runs;
            final_mem_data.exec_time = timeSum;
            final_mem_data.ops_per_sec = opsSum;
        }

    }
    return final_mem_data;
}

MemAccessInfo run_mem_access_best_case_test(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal) {
    double timeSum;
    long long opsSum;
    double currentValue;
    MemAccessInfo mem_data;
    MemAccessInfo final_mem_data;

    for(int matSize = valueLower; matSize <= valueUpper; matSize = logarithmic ? matSize * traversal: matSize + traversal){
        int errorCount;
        mem_data = mem_access_test_best_case_size(matSize,runs);
        if (mem_data.exec_time <= 0) {
            errorCount = 10;
            while (mem_data.exec_time <= 0 && errorCount > 0) {
                mem_data = mem_access_test_best_case_size(matSize,runs);
                errorCount--;
            }
        }
        timeSum = mem_data.exec_time;
        opsSum = mem_data.ops_per_sec;

        timeSum = timeSum / (double)runs;
        opsSum = opsSum / runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.ops.append(opsSum);
        final_mem_data.x_axis.append(matSize);


    }
    final_mem_data.runs = runs;
    final_mem_data.exec_time = final_mem_data.execTimes.last();
    final_mem_data.ops_per_sec = final_mem_data.ops.last();

    return final_mem_data;


}


MemAccessInfo mem_access_test_worst_case_size(int matSize, int runs) {
    clock_t time_start;
    clock_t time_end;
    clock_t time_dur = 0;
    MemAccessInfo mem_data;
    mem_data.exec_time = -1;
    mem_data.ops_per_sec = -1;
    double time_float;
    long long op_per_sec;
    int mat_size_rows = matSize;
    int mat_size_columns = matSize + 1;
    long long ops_total = (long long)(mat_size_columns - 1) * mat_size_rows * runs;
    int i, j, k;

    int** mem_mat = (int**)malloc(mat_size_rows * sizeof(int*));

    if (mem_mat == NULL) {
        printf("Allocation failed. Retrying...\n");
        return mem_data;
    }
    for (i = 0; i < mat_size_rows; i++) {
        mem_mat[i] = (int*)malloc(mat_size_columns * sizeof(int));
        if (mem_mat[i] == NULL) {
            free_alloc_mem(mem_mat, i);
            free(mem_mat);
            mem_mat = NULL;
            return mem_data;
        }
    }

    for(k = 0; k < runs; k++){

        for (i = 0; i < mat_size_rows; i++)
            for (j = 0; j < mat_size_columns; j++)
                mem_mat[i][j] = 0;

        time_start = clock();
        for (j = 1; j < mat_size_columns; j++) {
            for (i = 0; i < mat_size_rows; i++) {
                mem_mat[i][j] = mem_mat[i][j-1] + 1;
            }
        }
        time_end = clock();
        time_dur += (time_end - time_start);
    }

    time_float = (double)time_dur / CLOCKS_PER_SEC;

    if(time_float==0){
        free_alloc_mem(mem_mat, mat_size_rows);
        free(mem_mat);
        mem_mat = NULL;
        mem_data.exec_time = -1;
        mem_data.ops_per_sec = -1;
        return mem_data;
    }

    op_per_sec = ops_total / time_float;

    mem_data.exec_time = time_float;
    mem_data.ops_per_sec = op_per_sec;

    free_alloc_mem(mem_mat, mat_size_rows);
    free(mem_mat);
    mem_mat = NULL;

    return mem_data;

}



MemAccessInfo run_mem_access_worst_case_test2(int runs) {
    double timeSum;
    long long opsSum;
    double currentValue;
    MemAccessInfo mem_data;
    MemAccessInfo final_mem_data;
    for(int matSize = 1024; matSize <= 16384; matSize = matSize * 2){
        timeSum = 0;
        opsSum = 0;
        //for (int i = 0; i < runs; i++) {
            mem_data = mem_access_test_worst_case_size(matSize,runs);
            if (mem_data.exec_time < 0) {
                while (mem_data.exec_time < 0) {
                    mem_data = mem_access_test_worst_case_size(matSize,runs);
                }
            }
            timeSum += mem_data.exec_time;
            opsSum += mem_data.ops_per_sec;
        //}
        timeSum = timeSum / (double)runs;
        opsSum = opsSum / runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.ops.append(opsSum);
        final_mem_data.x_axis.append(matSize);
        if(matSize == 4096){
            final_mem_data.runs = runs;
            final_mem_data.exec_time = timeSum;
            final_mem_data.ops_per_sec = opsSum;
        }
    }
    return final_mem_data;
}

MemAccessInfo run_mem_access_worst_case_test(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal) {
    double timeSum;
    long long opsSum;
    double currentValue;
    int errorCount;
    MemAccessInfo mem_data;
    MemAccessInfo final_mem_data;

    for(int matSize = valueLower; matSize <= valueUpper; matSize = logarithmic ? matSize * traversal: matSize + traversal){

        mem_data = mem_access_test_worst_case_size(matSize,runs);
        if (mem_data.exec_time <= 0) {
            errorCount = 10;
            while (mem_data.exec_time <= 0 && errorCount > 0 ) {
                mem_data = mem_access_test_worst_case_size(matSize,runs);
                errorCount--;
            }
        }
        timeSum = mem_data.exec_time;
        opsSum = mem_data.ops_per_sec;

        timeSum = timeSum / (double)runs;
        opsSum = opsSum / runs;
        final_mem_data.execTimes.append(timeSum);
        final_mem_data.ops.append(opsSum);
        final_mem_data.x_axis.append(matSize);
    }
    final_mem_data.runs = runs;
    final_mem_data.exec_time = final_mem_data.execTimes.last();
    final_mem_data.ops_per_sec = final_mem_data.ops.last();
    return final_mem_data;
}


AllMemAccessInfo run_mem_access_test2(int runs) {
    MemAccessInfo best_case_data = run_mem_access_best_case_test2(runs);
    MemAccessInfo worst_case_data = run_mem_access_worst_case_test2(runs);

    AllMemAccessInfo total_data;
    total_data.runs = runs;
    total_data.exec_time_best = best_case_data.exec_time;
    total_data.exec_time_worst = worst_case_data.exec_time;
    total_data.ops_per_sec_best = best_case_data.ops_per_sec;
    total_data.ops_per_sec_worst = worst_case_data.ops_per_sec;

    total_data.execTimesBest = best_case_data.execTimes;
    total_data.opsBest = best_case_data.ops;
    total_data.execTimesWorst = worst_case_data.execTimes;
    total_data.opsWorst = worst_case_data.ops;
    total_data.x_axis_final = best_case_data.x_axis;


    return total_data;
}

AllMemAccessInfo run_mem_access_test(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal) {
    MemAccessInfo best_case_data = run_mem_access_best_case_test(runs, valueLower, valueUpper, logarithmic, traversal);
    MemAccessInfo worst_case_data = run_mem_access_worst_case_test(runs, valueLower, valueUpper, logarithmic, traversal);
    qInfo("Here");

    AllMemAccessInfo total_data;
    total_data.logarithmic = logarithmic;
    total_data.runs = runs;
    total_data.exec_time_best = best_case_data.exec_time;
    total_data.exec_time_worst = worst_case_data.exec_time;
    total_data.ops_per_sec_best = best_case_data.ops_per_sec;
    total_data.ops_per_sec_worst = worst_case_data.ops_per_sec;

    total_data.execTimesBest = best_case_data.execTimes;
    total_data.opsBest = best_case_data.ops;
    total_data.execTimesWorst = worst_case_data.execTimes;
    total_data.opsWorst = worst_case_data.ops;
    total_data.x_axis_final = best_case_data.x_axis;


    return total_data;
}

AllMemAccessInfo run_mem_access_test_progress(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal, ProgressFn progress_report) {
    int i;
    int total_steps = 0;
    for(i = valueLower; i <= valueUpper; i = logarithmic ? i * traversal: i + traversal){
        total_steps++;
    }
    total_steps = total_steps * 2;


    MemAccessInfo best_case_data = run_mem_access_best_case_test(runs, valueLower, valueUpper, logarithmic, traversal);
    progress_report(total_steps);
    MemAccessInfo worst_case_data = run_mem_access_worst_case_test(runs, valueLower, valueUpper, logarithmic, traversal);
    progress_report(total_steps);
    qInfo("Here");

    AllMemAccessInfo total_data;
    total_data.logarithmic = logarithmic;
    total_data.runs = runs;
    total_data.exec_time_best = best_case_data.exec_time;
    total_data.exec_time_worst = worst_case_data.exec_time;
    total_data.ops_per_sec_best = best_case_data.ops_per_sec;
    total_data.ops_per_sec_worst = worst_case_data.ops_per_sec;

    total_data.execTimesBest = best_case_data.execTimes;
    total_data.opsBest = best_case_data.ops;
    total_data.execTimesWorst = worst_case_data.execTimes;
    total_data.opsWorst = worst_case_data.ops;
    total_data.x_axis_final = best_case_data.x_axis;


    return total_data;
}




