#include <stdio.h>
#include "memTransfer.h"
#include "memAccess.h"
#include "encrDecr.h"
#include "mandelbrot.h"
#include "pcGrader.h"
#include <QDebug>
#include <QtLogging>
using namespace std;

double clamp_score(double lowLimit, double number, double upLimit){
    if(number < lowLimit) return lowLimit;
    if(number > upLimit) return upLimit;
    return number;
}
pcGraderGrades clamp_all_scores(double lowLimit, pcGraderGrades aux, double upLimit){
    aux.memtrs_exec_time_score = clamp_score(lowLimit, aux.memtrs_exec_time_score, upLimit);
    aux.memtrs_mb_rate_score = clamp_score(lowLimit, aux.memtrs_mb_rate_score, upLimit);
    aux.memacc_exec_time_best_score = clamp_score(lowLimit, aux.memacc_exec_time_best_score, upLimit);
    aux.memacc_ops_per_sec_best_score = clamp_score(lowLimit,  aux.memacc_ops_per_sec_best_score, upLimit);
    aux.memacc_exec_time_worst_score = clamp_score(lowLimit,  aux.memacc_exec_time_worst_score, upLimit);
    aux.memacc_ops_per_sec_worst_score = clamp_score(lowLimit,  aux.memacc_ops_per_sec_worst_score, upLimit);
    aux.encdec_exec_time_score = clamp_score(lowLimit,  aux.encdec_exec_time_score, upLimit);
    aux.encdec_ops_executed_score = clamp_score(lowLimit,  aux.encdec_ops_executed_score, upLimit);
    aux.encdec_file_write_time_score = clamp_score(lowLimit,  aux.encdec_file_write_time_score, upLimit);
    aux.mandel_exec_time_score = clamp_score(lowLimit,  aux.mandel_exec_time_score, upLimit);
    aux.mandel_ops_executed_score = clamp_score(lowLimit,  aux.mandel_ops_executed_score, upLimit);
    return aux;
}

double calculateGrade(pcGraderGrades aux){
    double memtrs_weight_sum =  aux.memtrs_exec_time_weight + aux.memtrs_mb_rate_weight;
    double memtrs_log_sum = aux.memtrs_exec_time_weight * std::log(aux.memtrs_exec_time_score) +
                    aux.memtrs_mb_rate_weight * std::log(aux.memtrs_mb_rate_score);
    double memtrs_final = std::exp(memtrs_log_sum/memtrs_weight_sum);

    double memacc_weight_sum = aux.memacc_exec_time_best_weight + aux.memacc_exec_time_worst_weight + aux.memacc_ops_per_sec_best_weight + aux.memacc_ops_per_sec_worst_weight;
    double memacc_log_sum = aux.memacc_exec_time_best_weight * std::log(aux.memacc_exec_time_best_score) +
                            aux.memacc_ops_per_sec_best_weight * std::log(aux.memacc_ops_per_sec_best_score) +
                            aux.memacc_exec_time_worst_weight * std::log(aux.memacc_exec_time_worst_score) +
                            aux.memacc_ops_per_sec_worst_weight * std::log(aux.memacc_ops_per_sec_worst_score);
    double memacc_final = std::exp(memacc_log_sum/memacc_weight_sum);

    double encdec_weight_sum = aux.encdec_exec_time_weight + aux.encdec_file_write_time_weight + aux.encdec_ops_executed_weight;
    double encdec_log_sum = aux.encdec_exec_time_weight * std::log(aux.encdec_exec_time_score) +
                            aux.encdec_ops_executed_weight * std::log(aux.encdec_ops_executed_score) +
                            aux.encdec_file_write_time_weight * std::log(aux.encdec_file_write_time_score);
    double encdec_final = std::exp(encdec_log_sum/encdec_weight_sum);

    double mandel_weight_sum = aux.mandel_exec_time_weight + aux.mandel_ops_executed_weight;
    double mandel_log_sum = aux.mandel_exec_time_weight * std::log(aux.mandel_exec_time_score) +
                            aux.mandel_ops_executed_weight * std::log(aux.mandel_ops_executed_score);
    double mandel_final = std::exp(mandel_log_sum/mandel_weight_sum);

    double final_grade_weight_sum = 1;
    double final_grade_log_sum = 0.25 * std::log(memtrs_final) +
                                 0.25 * std::log(memacc_final) +
                                 0.25 * std::log(encdec_final) +
                                 0.25 * std::log(mandel_final);
    double final_grade_final = std::exp(final_grade_log_sum/final_grade_weight_sum);
    final_grade_final = 5.0 * log2(final_grade_final) + 5.0;
    //qInfo() <<final_grade_final;
    final_grade_final = clamp_score(0.0, final_grade_final, 10.0);
    return final_grade_final;
}

pcGraderGrades base_line_data(){
    pcGraderGrades base_line;

    base_line.memtrs_exec_time = 0.147300;
    base_line.memtrs_exec_time_weight = 0.8;
    base_line.memtrs_mb_rate = 101.83;
    base_line.memtrs_mb_rate_weight = 0.2;

    base_line.memacc_exec_time_best = 0.130600;
    base_line.memacc_exec_time_best_weight = 0.4;
    base_line.memacc_ops_per_sec_best = 205540165;
    base_line.memacc_ops_per_sec_best_weight = 0.1;
    base_line.memacc_exec_time_worst = 1.948400;
    base_line.memacc_exec_time_worst_weight = 0.4;
    base_line.memacc_ops_per_sec_worst = 13777225;
    base_line.memacc_ops_per_sec_worst_weight = 0.1;

    base_line.encdec_exec_time = 0.372900;
    base_line.encdec_exec_time_weight = 0.6;
    base_line.encdec_ops_executed = 7468.33;
    base_line.encdec_ops_executed_weight = 0.2;
    base_line.encdec_file_write_time = 1.470500;
    base_line.encdec_file_write_time_weight = 0.2;

    base_line.mandel_exec_time = 0.884000;
    base_line.mandel_exec_time_weight = 0.7;
    base_line.mandel_ops_executed = 1867.5;
    base_line.mandel_ops_executed_weight = 0.3;
    return base_line;
}


pcGraderInfo grade_pc2() {
    MemTransferInfo memTransferRes = run_mem_transfer_test(10,500,1500,100);
    AllMemAccessInfo memAccessRes = run_mem_access_test(10,2048,16384,true,2);
    encryptionDecryptionInfo encrDecrRes = run_encryption_decryption_test(10,8,128,true,2);
    mandelbrotInfo mandelbrotRes = run_mandelbrot_test(10,500,1000,100);


    pcGraderInfo pc_info;

    pc_info.memtrs_runs = memTransferRes.runs;
    pc_info.memtrs_exec_time = memTransferRes.exec_time;
    pc_info.memtrs_mb_rate = memTransferRes.mb_rate;
    pc_info.memtrs_execTimes = memTransferRes.execTimes;
    pc_info.memtrs_mbRates = memTransferRes.mbRates;
    pc_info.memtrs_x_axis = memTransferRes.x_axis;

    pc_info.memacc_runs = memAccessRes.runs;
    pc_info.memacc_exec_time_best = memAccessRes.exec_time_best;
    pc_info.memacc_ops_per_sec_best = memAccessRes.ops_per_sec_best;
    pc_info.memacc_exec_time_worst = memAccessRes.exec_time_worst;
    pc_info.memacc_ops_per_sec_worst = memAccessRes.ops_per_sec_worst;

    pc_info.memacc_execTimesBest = memAccessRes.execTimesBest;
    pc_info.memacc_opsBest = memAccessRes.opsBest;
    pc_info.memacc_execTimesWorst = memAccessRes.execTimesWorst;
    pc_info.memacc_opsWorst = memAccessRes.opsWorst;
    pc_info.memacc_x_axis_final = memAccessRes.x_axis_final;

    pc_info.encdec_runs = encrDecrRes.runs;
    pc_info.encdec_exec_time = encrDecrRes.exec_time;
    pc_info.encdec_ops_executed = encrDecrRes.ops_executed;
    pc_info.encdec_file_write_time = encrDecrRes.file_write_time;
    pc_info.encdec_execTimes = encrDecrRes.execTimes;
    pc_info.encdec_ops = encrDecrRes.ops;
    pc_info.encdec_fileTimes = encrDecrRes.fileTimes;
    pc_info.encdec_x_axis = encrDecrRes.x_axis;

    pc_info.mandel_runs = mandelbrotRes.runs;
    pc_info.mandel_exec_time = mandelbrotRes.exec_time;
    pc_info.mandel_ops_executed = mandelbrotRes.ops_executed;
    pc_info.mandel_execTimes = mandelbrotRes.execTimes;
    pc_info.mandel_ops = mandelbrotRes.ops;
    pc_info.mandel_x_axis = mandelbrotRes.x_axis;

    return pc_info;
}

void grade_pc_bar(QPromise<pcGraderInfo>& promise) {

    int total_steps = 11 + 30 + 100 + 60;
    promise.setProgressRange(0,total_steps);
    int progress = 0;
    auto forward = [&](int step){
        progress += step;
        promise.setProgressValue(progress);
    };

    MemTransferInfo memTransferRes = run_mem_transfer_test_progress(10,500,1500,100, [&](int s){forward (s);});
    AllMemAccessInfo memAccessRes = run_mem_access_test_progress(10,2048,16384,false,1024, [&](int s){forward (s);});
    encryptionDecryptionInfo encrDecrRes = run_encryption_decryption_test_progress(10,8,128,true,2, [&](int s){forward (s);});
    mandelbrotInfo mandelbrotRes = run_mandelbrot_test_progress(10,500,1000,100, [&](int s){forward (s);});

    pcGraderInfo pc_info;

    pcGraderGrades aux = base_line_data();
    pc_info.memtrs_runs = memTransferRes.runs;
    pc_info.memtrs_exec_time = memTransferRes.exec_time;
    pc_info.memtrs_mb_rate = memTransferRes.mb_rate;
    pc_info.memtrs_execTimes = memTransferRes.execTimes;
    pc_info.memtrs_mbRates = memTransferRes.mbRates;
    pc_info.memtrs_x_axis = memTransferRes.x_axis;

    pc_info.memacc_runs = memAccessRes.runs;
    pc_info.memacc_exec_time_best = memAccessRes.exec_time_best;
    pc_info.memacc_ops_per_sec_best = memAccessRes.ops_per_sec_best;
    pc_info.memacc_exec_time_worst = memAccessRes.exec_time_worst;
    pc_info.memacc_ops_per_sec_worst = memAccessRes.ops_per_sec_worst;
    pc_info.memacc_execTimesBest = memAccessRes.execTimesBest;
    pc_info.memacc_opsBest = memAccessRes.opsBest;
    pc_info.memacc_execTimesWorst = memAccessRes.execTimesWorst;
    pc_info.memacc_opsWorst = memAccessRes.opsWorst;
    pc_info.memacc_x_axis_final = memAccessRes.x_axis_final;


    pc_info.encdec_runs = encrDecrRes.runs;
    pc_info.encdec_exec_time = encrDecrRes.exec_time;
    pc_info.encdec_ops_executed = encrDecrRes.ops_executed;
    pc_info.encdec_file_write_time = encrDecrRes.file_write_time;
    pc_info.encdec_execTimes = encrDecrRes.execTimes;
    pc_info.encdec_ops = encrDecrRes.ops;
    pc_info.encdec_fileTimes = encrDecrRes.fileTimes;
    pc_info.encdec_x_axis = encrDecrRes.x_axis;

    pc_info.mandel_runs = mandelbrotRes.runs;
    pc_info.mandel_exec_time = mandelbrotRes.exec_time;
    pc_info.mandel_ops_executed = mandelbrotRes.ops_executed;
    pc_info.mandel_execTimes = mandelbrotRes.execTimes;
    pc_info.mandel_ops = mandelbrotRes.ops;
    pc_info.mandel_x_axis = mandelbrotRes.x_axis;

    aux.memtrs_exec_time_score = aux.memtrs_exec_time / memTransferRes.exec_time;
    aux.memtrs_mb_rate_score = memTransferRes.mb_rate / aux.memtrs_mb_rate;
    aux.memacc_exec_time_best_score = aux.memacc_exec_time_best / memAccessRes.exec_time_best;
    aux.memacc_ops_per_sec_best_score = memAccessRes.ops_per_sec_best / aux.memacc_ops_per_sec_best;
    aux.memacc_exec_time_worst_score = aux.memacc_exec_time_worst/ memAccessRes.exec_time_worst;
    aux.memacc_ops_per_sec_worst_score = memAccessRes.ops_per_sec_worst / aux.memacc_ops_per_sec_worst;
    aux.encdec_exec_time_score = aux.encdec_exec_time/ encrDecrRes.exec_time;
    aux.encdec_ops_executed_score = encrDecrRes.ops_executed / aux.encdec_ops_executed;
    aux.encdec_file_write_time_score = aux.encdec_file_write_time / encrDecrRes.file_write_time;
    aux.mandel_exec_time_score = aux.mandel_exec_time / mandelbrotRes.exec_time;
    aux.mandel_ops_executed_score = mandelbrotRes.ops_executed / aux.mandel_ops_executed;

    aux = clamp_all_scores(0.25, aux, 4.0);
    pc_info.final_grade = calculateGrade(aux);
    /*qInfo() << aux.memtrs_exec_time_score;
    qInfo() << aux.memtrs_mb_rate_score;
    qInfo() << aux.memacc_exec_time_best_score;
    qInfo() << aux.memacc_ops_per_sec_best_score;
    qInfo() << aux.memacc_exec_time_worst_score;
    qInfo() << aux.memacc_ops_per_sec_worst_score;
    qInfo() << aux.encdec_exec_time_score;
    qInfo() << aux.encdec_ops_executed_score;
    qInfo() << aux.encdec_file_write_time_score;
    qInfo() << aux.mandel_exec_time_score;
    qInfo() << aux.mandel_ops_executed_score;
    */
    promise.addResult(pc_info);
    //return pc_info;
}

