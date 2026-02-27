#if defined(_MSC_VER)
#include <intrin.h>
#define cpuid(info, x) __cpuid(info, x)
#define cpuidex(info, x, y) __cpuidex(info, x, y)

#else
#include <cpuid.h>
inline void cpuid(int info[4], int function_id) {
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid(function_id, &eax, &ebx, &ecx, &edx);
    info[0] = eax; info[1] = ebx; info[2] = ecx; info[3] = edx;
}

inline void cpuidex(int info[4], int function_id, int subfunction_id) {
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid_count(function_id, subfunction_id, &eax, &ebx, &ecx, &edx);
    info[0] = eax; info[1] = ebx; info[2] = ecx; info[3] = edx;

}
#endif

#include <math.h>
#include <iostream>
#include <Windows.h>
#include "cacheinfo.h"

SYSTEM_INFO sysInfo;

char* convCharBin(unsigned int data, char* regBin) {

    int i;
    for (i = 0; i < 32; i++) {
        if (data % 2 == 0) {
            regBin[i] = '0';
        }
        else {
            regBin[i] = '1';
        }
        data = data / 2;
    }
    regBin[32] = '\0';

    return regBin;

}

int convBinValue(char* bin, int msb, int lsb) {
    int i, result = 0, power2 = 0;
    for (i = lsb; i <= msb; i++) {
        if (bin[i] == '1') {
            result |= (1 << power2);
        }
        power2++;
    }
    return result;
}

char *CPUVendor() {
    int cpuInfo[4] = { 0 };
    cpuid(cpuInfo, 0);
    char vendor[13];
    static char returnVendor[13];
    //char vendor[13];
    memcpy(vendor + 0, &cpuInfo[1], 4); // EBX
    memcpy(vendor + 4, &cpuInfo[3], 4); // EDX
    memcpy(vendor + 8, &cpuInfo[2], 4); // ECX
    vendor[12] = '\0';
    if (strcmp(vendor, "GenuineIntel") == 0) {
        strcpy_s(returnVendor, "Intel");
        return returnVendor;
    }
    if (strcmp(vendor, "AuthenticAMD") == 0) {
        strcpy_s(returnVendor, "AMD");
        return returnVendor;
    }
    strcpy_s(returnVendor, "Other");

    return returnVendor;
}

bool CPUVendorIntel() {
    int cpuInfo[4] = { 0 };
    cpuid(cpuInfo, 0);
    static char vendor[13];
    //char vendor[13];
    memcpy(vendor + 0, &cpuInfo[1], 4); // EBX
    memcpy(vendor + 4, &cpuInfo[3], 4); // EDX
    memcpy(vendor + 8, &cpuInfo[2], 4); // ECX
    vendor[12] = '\0';

    //printf("CPU Vendor: %s\n", vendor);
    if (strcmp(vendor, "GenuineIntel") == 0) {
        return true;
    }
    return false;

}


char *BrandString() {
    int cpuInfo[4] = { 0 };
    static char brandString[49];
    //call 1
    cpuid(cpuInfo, 0x80000002);

    memcpy(brandString + 0, &cpuInfo[0], 4); ///EAX
    memcpy(brandString + 4, &cpuInfo[1], 4); ///EBX
    memcpy(brandString + 8, &cpuInfo[2], 4); ///ECX
    memcpy(brandString + 12, &cpuInfo[3], 4); ///EDX

    cpuid(cpuInfo, 0x80000003);

    memcpy(brandString + 16, &cpuInfo[0], 4); ///EAX
    memcpy(brandString + 20, &cpuInfo[1], 4); ///EBX
    memcpy(brandString + 24, &cpuInfo[2], 4); ///ECX
    memcpy(brandString + 28, &cpuInfo[3], 4); ///EDX

    cpuid(cpuInfo, 0x80000004);

    memcpy(brandString + 32, &cpuInfo[0], 4); ///EAX
    memcpy(brandString + 36, &cpuInfo[1], 4); ///EBX
    memcpy(brandString + 40, &cpuInfo[2], 4); ///ECX
    memcpy(brandString + 44, &cpuInfo[3], 4); ///EDX

    brandString[48] = '\0';

    return brandString;

}

char* typeFamilyModel(int select) {
    int cpuInfo[4] = { 0 };
    cpuid(cpuInfo, 1);

    unsigned int eaxval = cpuInfo[0];

    char regData[33];
    //printf("TFM: %s\n", tfm);
    convCharBin(eaxval, regData);

    int model = convBinValue(regData, 7, 4);
    int family = convBinValue(regData, 11, 8);
    int extModel = convBinValue(regData, 19, 16);
    extModel |= (extModel << 4);
    int val;
    static char returnVal[10];

    switch (select) {
    case 0:
        val = convBinValue(regData, 3, 0);
        sprintf_s(returnVal, "%d",val);
        return returnVal;
        break;

    case 1:
        sprintf_s(returnVal, "%d", model);
        return returnVal;
        break;

    case 2:
        sprintf_s(returnVal, "%d", family);
        return returnVal;
        break;
    case 3:
        val = convBinValue(regData, 13, 12);
        switch (val) {
        case 0:
            strcpy_s(returnVal, "OEM");
            return returnVal;
            break;
        case 1:
            strcpy_s(returnVal, "IOP");
            return returnVal;
            break;
        case 2:
            strcpy_s(returnVal, "Dual Processor");
            return returnVal;
            break;
        default:
            strcpy_s(returnVal, "Reserved");
            return returnVal;
            break;
        }

        break;
    case 4:

        if (model == 15) {
            val = model + extModel;
            sprintf_s(returnVal, "%d", val);
            return returnVal;
        }
        else {
            sprintf_s(returnVal, "%d", extModel);
            return returnVal;
        }
        break;
    default:
        if (family == 6 || family == 15) {
            val = family + convBinValue(regData, 27, 20);
            sprintf_s(returnVal, "%d", val);
            return returnVal;
        }
        else {
            sprintf_s(returnVal, "%d", family);
            return returnVal;
        }
    }

}

char* frequencies(int select) {
    int cpuInfo[4] = { 0 };
    cpuid(cpuInfo, 0x16);
    static char freq[20];

    //char baseFreq[5];
    //memcpy(baseFreq + 0, &cpuInfo[0], 4); ///EAX
    //baseFreq[4] = '\0';
    if (CPUVendorIntel() == true) {

        switch (select) {
        case 0:
            sprintf_s(freq, "%d", cpuInfo[0]);
            break;

        case 1:
            sprintf_s(freq, "%d", cpuInfo[1]);
            break;


        default:
            sprintf_s(freq, "%d", cpuInfo[2]);
            break;
        }
        strcat_s(freq, " MHz");
        return freq;
    }

    strcpy_s(freq, "N/A");
    return freq;

}


CacheInfo cacheInfo(int select) {
    int ecx;
    switch (select) {
    case 0:
        ecx = 0;
        break;
    case 1:
        ecx = 1;
        break;
    case 2:
        ecx = 2;
        break;
    default:
        ecx = 3;
        break;
    }

    int cpuInfo[4] = { 0 };
    if (CPUVendorIntel() == true) {
        cpuidex(cpuInfo, 4, ecx);
    }
    else {
        cpuidex(cpuInfo, 0x8000001D, ecx);
    }
    //PROCESS EAX INFO
    unsigned int exval = cpuInfo[0];
    char regBinEAX[33];
    convCharBin(exval, regBinEAX);

    //PROCESS EBX INFO
    exval = cpuInfo[1];
    char regBinEBX[33];
    convCharBin(exval, regBinEBX);

    //PROCESS ECX INFO
    exval = cpuInfo[2];
    char regBinECX[33];
    convCharBin(exval, regBinECX);


    //int type = convBinValue(regBinEAX, 4, 0);
    //printf("%d\n", type);

    CacheInfo inst;
    int assoc_way = convBinValue(regBinEBX, 31, 22) + 1;
    int size = assoc_way * (convBinValue(regBinEBX, 21, 12) + 1) * (convBinValue(regBinEBX, 11, 0) + 1) * (convBinValue(regBinECX, 31, 0) + 1);
    int nrDiv = 0;
    int tassoc = convBinValue(regBinEAX, 9, 9);

    char size_char[20];
    char way_char[10];

    while (size > 1023) {
        size = size / 1024;
        nrDiv++;
    }
    sprintf_s(size_char,"%d", size);
    //sprintf_s(way_char, "%d", assoc_way);
    strcpy_s(inst.size_share, size_char);


    switch (nrDiv) {
    case 0:
        strcat_s(inst.size_share, " Bytes");
        break;
    case 1:
        strcat_s(inst.size_share, " KBytes");
        break;
    case 2:
        strcat_s(inst.size_share, " MBytes");
        break;
    case 3:
        strcat_s(inst.size_share, " GBytes");
        break;
    default:
        strcat_s(inst.size_share, " N/A");
        break;
    }
    if (tassoc == 0) {
        sprintf_s(way_char, "%d", assoc_way);
        strcat_s(way_char, "-way");
        strcpy_s(inst.way, way_char);
    }
    else {
        strcpy_s(inst.way, "TA");
    }


    return inst;


}

int coreNumberInt() {
    DWORD size = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, NULL, &size);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)malloc(size);
    int physical_cores = 0;
    if (GetLogicalProcessorInformationEx(RelationProcessorCore, buffer, &size)) {

        int logical_processors = 0;

        char* ptr = (char*)buffer;
        char* end = ptr + size;

        while (ptr < end) {
            SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr;
            physical_cores++;

            ptr += info->Size;
        }

        //printf("Physical cores: %d\n", physical_cores);
    }

    free(buffer);
    return physical_cores;
}

char* coreNumberChar() {
    static char res[10];
    int corz = coreNumberInt();
    sprintf_s(res, "%d", corz);
    return res;
}

char* threadNumber() {
    GetNativeSystemInfo(&sysInfo);
    int cores = sysInfo.dwNumberOfProcessors;
    static char res[10];
    sprintf_s(res, "%d", cores);
    return res;
}

char* architecture() {
    GetNativeSystemInfo(&sysInfo);
    int archi = sysInfo.wProcessorArchitecture;
    static char res[25];
    switch (archi) {
    case 9:
        if (CPUVendorIntel() == true) {
            strcpy_s(res, "Intel x64");
        }
        else {
            strcpy_s(res, "AMD x64");
        }
        return res;
    case 5:
        strcpy_s(res, "ARM");
        return res;
    case 12:
        strcpy_s(res, "ARM64");
        return res;
    case 6:
        strcpy_s(res, "Intel Itanium-Based");
        return res;
    case 0:
        strcpy_s(res, "x86");
        return res;
    default:
        strcpy_s(res, "Unknown Architecture");
        return res;
    }

}

char* pageSize() {
    GetNativeSystemInfo(&sysInfo);
    int pageSize = sysInfo.dwPageSize;
    int nrDiv = 0;
    static char res[25];
    while (pageSize > 1023) {
        pageSize = pageSize / 1024;
        nrDiv++;
    }
    sprintf_s(res, "%d", pageSize);
    switch (nrDiv) {
    case 0:
        strcat_s(res, " Bytes");
        break;
    case 1:
        strcat_s(res, " KBytes");
        break;
    case 2:
        strcat_s(res, " MBytes");
        break;
    case 3:
        strcat_s(res, " GBytes");
        break;
    default:
        strcat_s(res, " N/A");
        break;
    }
    return res;
}


