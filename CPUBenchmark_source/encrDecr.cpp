#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdint>
#include "encrDecr.h"
#include <QDebug>
#include <QDir>

uint32_t bit32_key = 0xBA3A;

uint32_t modInverse32(uint32_t a) {
    uint32_t x = a;
    x = x * (2 - a * x);
    x = x * (2 - a * x);
    x = x * (2 - a * x);
    x = x * (2 - a * x);
    x = x * (2 - a * x);
    return x;
}

uint32_t inverse15435 = modInverse32(15435);
volatile uint32_t burn_div_var;

void resetBuffer(uint32_t* buffer, size_t size) {
    for (size_t i = 0; i < size; i++) {
        buffer[i] = 0;
    }
}

int file_generator(char *name, int size){

    FILE* f = fopen(name, "wb");
    if (!f) return -1;

    const char line[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\n";
    const size_t len = sizeof(line) - 1;

    size_t mb = (size_t)size;
    size_t target = mb * 1024 * 1024;
    size_t written = 0;

    while (written < target) {
        fwrite(line, 1, len, f);
        written += len;
    }

    fclose(f);
    return 0;
}


encryptionDecryptionInfo read_file_encr_size(int fileSize) {
    FILE* fileptr=NULL;
    FILE* fileptrOut = NULL;

    clock_t time_start;
    clock_t time_end;
    clock_t time_dur;
    double time_float;

    uint32_t buffer[1024] = { 0 };
    unsigned char bufferChar[1024];
    size_t bytesRead;
    int i;

    encryptionDecryptionInfo failed_data;
    failed_data.exec_time = -1;
    failed_data.ops_executed = -1;
    failed_data.file_write_time = -1;
    encryptionDecryptionInfo encr_data;
    encr_data.exec_time = 0;
    encr_data.ops_executed= 0;
    encr_data.file_write_time = 0;

    char filename_in[30];
    char filename_out[30];

    snprintf(filename_in, sizeof(filename_in),"fileEncrIn%d.txt", fileSize);
    snprintf(filename_out, sizeof(filename_out),"fileEncrOut%d.txt", fileSize);

    if(file_generator(filename_in,fileSize)<0){
        qInfo("File generation failed");
        return failed_data;
    }

    fileptr = fopen(filename_in, "rb");
    if (fileptr == NULL) {
        qInfo("File %s failed to open",filename_in);
        return failed_data;
    }else{
         qInfo("File %s opened", filename_in);
    }

    fileptrOut = fopen(filename_out, "wb");
    if (fileptrOut == NULL) {
        fclose(fileptr);
        return failed_data;
    }


    while ((bytesRead = fread(bufferChar, sizeof(unsigned char), 1024, fileptr)) > 0) {


        for (i = 0; i < bytesRead; i++){
            buffer[i] = bufferChar[i];
            //printf("%d ", buffer[i]);
        }
        time_start = clock();
        for (i = 0; i < bytesRead; i++) {
            buffer[i] = buffer[i] - 13;
            buffer[i] = buffer[i] * 15435;
            buffer[i] = buffer[i] ^ bit32_key;
            buffer[i] = buffer[i] + 27;
            burn_div_var = buffer[i] / 3412;
        }
        time_end = clock();
        time_dur = time_end - time_start;
        time_float = (double)time_dur / CLOCKS_PER_SEC;

        encr_data.exec_time += time_float;
        encr_data.ops_executed += bytesRead * 5;

        time_start = clock();
        fwrite(buffer, sizeof(uint32_t), bytesRead, fileptrOut);
        time_end = clock();
        time_dur = time_end - time_start;
        time_float = (double)time_dur / CLOCKS_PER_SEC;

        encr_data.file_write_time += time_float;

        resetBuffer(buffer, bytesRead);

    }
    if(encr_data.exec_time == 0){
        fclose(fileptr);
        fclose(fileptrOut);
        return failed_data;

    }
    encr_data.ops_executed = encr_data.ops_executed / encr_data.exec_time;

    if(bytesRead < 1024){
        if(ferror(fileptr)){
            fclose(fileptr);
            fclose(fileptrOut);
            return failed_data;

        }
    }

    fclose(fileptr);
    fclose(fileptrOut);
    encr_data.inputFile = filename_in;

    return encr_data;

}

encryptionDecryptionInfo read_file_decr_size(int fileSize) {
    FILE* fileptr = NULL;
    FILE* fileptrOut = NULL;

    clock_t time_start;
    clock_t time_end;
    clock_t time_dur;
    double time_float;

    uint32_t buffer[1024] = { 0 };
    unsigned char bufferChar[1024];
    size_t intsRead;
    int i;

    encryptionDecryptionInfo failed_data;
    failed_data.exec_time = -1;
    failed_data.ops_executed = -1;
    failed_data.file_write_time = -1;

    encryptionDecryptionInfo decr_data;
    decr_data.exec_time = 0;
    decr_data.ops_executed = 0;
    decr_data.file_write_time = 0;

    char filename_in[30];
    char filename_out[30];

    snprintf(filename_in, sizeof(filename_in),"fileEncrOut%d.txt", fileSize);
    snprintf(filename_out, sizeof(filename_out),"fileDecrOut%d.txt", fileSize);


    fileptr = fopen(filename_in, "rb");
    if (fileptr == NULL) {
        qInfo("File %s failed to open",filename_in);
        return failed_data;
    }
    else{
        qInfo("File %s opened", filename_in);
    }

    fileptrOut = fopen(filename_out, "wb");
    if (fileptrOut == NULL) {
        fclose(fileptr);
        return failed_data;
    }



    while ((intsRead = fread(buffer, sizeof(uint32_t), 1024, fileptr)) > 0) {

        time_start = clock();
        for (i = 0; i < intsRead; i++) {
            buffer[i] = buffer[i] - 27;
            buffer[i] = buffer[i] ^ bit32_key;
            buffer[i] = buffer[i] * inverse15435;
            buffer[i] = buffer[i] + 13;
            burn_div_var = buffer[i] / 3412;
        }
        time_end = clock();
        time_dur = time_end - time_start;
        time_float = (double)time_dur / CLOCKS_PER_SEC;

        decr_data.exec_time += time_float;
        decr_data.ops_executed += intsRead * 5;


        for (i = 0; i < intsRead; i++) {
            bufferChar[i] = (unsigned char)buffer[i];
            //printf("%d ", buffer[i]);

        }
        time_start = clock();
        fwrite(bufferChar, sizeof(unsigned char), intsRead, fileptrOut);
        time_end = clock();
        time_dur = time_end - time_start;
        time_float = (double)time_dur / CLOCKS_PER_SEC;

        decr_data.file_write_time += time_float;

        resetBuffer(buffer, intsRead);

    }
    if(decr_data.exec_time == 0){
        fclose(fileptr);
        fclose(fileptrOut);
        return failed_data;

    }
    decr_data.ops_executed = decr_data.ops_executed / decr_data.exec_time;

    if(intsRead < 1024){
        if(ferror(fileptr)){
            fclose(fileptr);
            fclose(fileptrOut);
            return failed_data;

        }
    }
    decr_data.inputFile = filename_in;
    decr_data.outputFile = filename_out;
    fclose(fileptr);
    fclose(fileptrOut);
    return decr_data;
}


encryptionDecryptionInfo run_encryption_decryption_test2(int runs) {
    double time_sum = 0;
    double ops_sum = 0;
    double writetime_sum = 0;
    encryptionDecryptionInfo encr_data;
    encryptionDecryptionInfo decr_data;
    encryptionDecryptionInfo final_data;
    int i;
    int fileSize;
    for(fileSize = 8; fileSize <= 128; fileSize = fileSize * 2){
        time_sum = 0;
        ops_sum = 0;
        writetime_sum = 0;
        for (i = 0; i < runs; i++) {
            encr_data = read_file_encr_size(fileSize);
            if (encr_data.exec_time == -1) {
                while (encr_data.exec_time == -1) {
                    encr_data = read_file_encr_size(fileSize);
                }
            }
            time_sum += encr_data.exec_time;
            ops_sum += encr_data.ops_executed;
            writetime_sum += encr_data.file_write_time;
        }

        qInfo("Removing %s",encr_data.inputFile);
        if(remove(encr_data.inputFile) == 0){
            qInfo("%d MB file deleted successfully (encr input)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (encr input)", fileSize);
        }


        for (i = 0; i < runs; i++) {
            decr_data = read_file_decr_size(fileSize);
            if (decr_data.exec_time == -1) {
                while (decr_data.exec_time == -1) {
                    decr_data = read_file_decr_size(fileSize);
                }
            }
            time_sum += decr_data.exec_time;
            ops_sum += decr_data.ops_executed;
            writetime_sum += decr_data.file_write_time;
        }

        time_sum = time_sum / (double)runs;
        ops_sum = (double)ops_sum / (double)(runs * 1000000);
        writetime_sum = writetime_sum / (double)runs;

        final_data.execTimes.append(time_sum);
        final_data.ops.append(ops_sum);
        final_data.fileTimes.append(writetime_sum);
        final_data.x_axis.append(fileSize);


        qInfo("Removing %s",decr_data.inputFile);
        if(remove(decr_data.inputFile) == 0){
            qInfo("%d MB file deleted successfully (decr input)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (decr input)", fileSize);
        }

        qInfo("Removing %s",decr_data.outputFile);
        if(remove(decr_data.outputFile) == 0){
            qInfo("%d MB file deleted successfully (decr output)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (decr output)", fileSize);
        }

        if(fileSize == 64){
            final_data.runs = runs;
            final_data.exec_time = time_sum;
            final_data.ops_executed = ops_sum;
            final_data.file_write_time = writetime_sum;
        }


    }


    return final_data;
}


encryptionDecryptionInfo run_encryption_decryption_test(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal) {
    double time_sum = 0;
    double ops_sum = 0;
    double writetime_sum = 0;
    encryptionDecryptionInfo encr_data;
    encryptionDecryptionInfo decr_data;
    encryptionDecryptionInfo final_data;
    int i;
    int fileSize;
    for(fileSize = valueLower; fileSize <= valueUpper; fileSize = logarithmic ? fileSize * traversal : fileSize + traversal){
        time_sum = 0;
        ops_sum = 0;
        writetime_sum = 0;
        for (i = 0; i < runs; i++) {
            encr_data = read_file_encr_size(fileSize);
            if (encr_data.exec_time == -1) {
                while (encr_data.exec_time == -1) {
                    encr_data = read_file_encr_size(fileSize);
                }
            }
            time_sum += encr_data.exec_time;
            ops_sum += encr_data.ops_executed;
            writetime_sum += encr_data.file_write_time;
        }

        qInfo("Removing %s",encr_data.inputFile);
        if(remove(encr_data.inputFile) == 0){
            qInfo("%d MB file deleted successfully (encr input)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (encr input)", fileSize);
        }


        for (i = 0; i < runs; i++) {
            decr_data = read_file_decr_size(fileSize);
            if (decr_data.exec_time == -1) {
                while (decr_data.exec_time == -1) {
                    decr_data = read_file_decr_size(fileSize);
                }
            }
            time_sum += decr_data.exec_time;
            ops_sum += decr_data.ops_executed;
            writetime_sum += decr_data.file_write_time;
        }

        time_sum = time_sum / (double)runs;
        ops_sum = (double)ops_sum / (double)(runs * 1000000);
        writetime_sum = writetime_sum / (double)runs;

        final_data.execTimes.append(time_sum);
        final_data.ops.append(ops_sum);
        final_data.fileTimes.append(writetime_sum);
        final_data.x_axis.append(fileSize);


        qInfo("Removing %s",decr_data.inputFile);
        if(remove(decr_data.inputFile) == 0){
            qInfo("%d MB file deleted successfully (decr input)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (decr input)", fileSize);
        }

        qInfo("Removing %s",decr_data.outputFile);
        if(remove(decr_data.outputFile) == 0){
            qInfo("%d MB file deleted successfully (decr output)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (decr output)", fileSize);
        }

    }
    final_data.runs = runs;
    final_data.logarithmic = logarithmic;
    final_data.exec_time = final_data.execTimes.last();
    final_data.ops_executed = final_data.ops.last();
    final_data.file_write_time = final_data.fileTimes.last();

    return final_data;
}

encryptionDecryptionInfo run_encryption_decryption_test_progress(int runs, int valueLower, int valueUpper, bool logarithmic, int traversal, ProgressFn progress_report) {
    double time_sum = 0;
    double ops_sum = 0;
    double writetime_sum = 0;
    encryptionDecryptionInfo encr_data;
    encryptionDecryptionInfo decr_data;
    encryptionDecryptionInfo final_data;
    int i;
    int fileSize;
    for(fileSize = valueLower; fileSize <= valueUpper; fileSize = logarithmic ? fileSize * traversal : fileSize + traversal){
        time_sum = 0;
        ops_sum = 0;
        writetime_sum = 0;
        for (i = 0; i < runs; i++) {
            progress_report(1);
            encr_data = read_file_encr_size(fileSize);
            if (encr_data.exec_time == -1) {
                while (encr_data.exec_time == -1) {
                    encr_data = read_file_encr_size(fileSize);
                }
            }
            time_sum += encr_data.exec_time;
            ops_sum += encr_data.ops_executed;
            writetime_sum += encr_data.file_write_time;
        }

        qInfo("Removing %s",encr_data.inputFile);
        if(remove(encr_data.inputFile) == 0){
            qInfo("%d MB file deleted successfully (encr input)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (encr input)", fileSize);
        }


        for (i = 0; i < runs; i++) {
            progress_report(1);
            decr_data = read_file_decr_size(fileSize);
            if (decr_data.exec_time == -1) {
                while (decr_data.exec_time == -1) {
                    decr_data = read_file_decr_size(fileSize);
                }
            }
            time_sum += decr_data.exec_time;
            ops_sum += decr_data.ops_executed;
            writetime_sum += decr_data.file_write_time;
        }

        time_sum = time_sum / (double)runs;
        ops_sum = (double)ops_sum / (double)(runs * 1000000);
        writetime_sum = writetime_sum / (double)runs;

        final_data.execTimes.append(time_sum);
        final_data.ops.append(ops_sum);
        final_data.fileTimes.append(writetime_sum);
        final_data.x_axis.append(fileSize);


        qInfo("Removing %s",decr_data.inputFile);
        if(remove(decr_data.inputFile) == 0){
            qInfo("%d MB file deleted successfully (decr input)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (decr input)", fileSize);
        }

        qInfo("Removing %s",decr_data.outputFile);
        if(remove(decr_data.outputFile) == 0){
            qInfo("%d MB file deleted successfully (decr output)", fileSize);
        }else{
            qInfo("%d MB file failed to delete (decr output)", fileSize);
        }

    }
    final_data.runs = runs;
    final_data.logarithmic = logarithmic;
    final_data.exec_time = final_data.execTimes.last();
    final_data.ops_executed = final_data.ops.last();
    final_data.file_write_time = final_data.fileTimes.last();

    return final_data;
}
