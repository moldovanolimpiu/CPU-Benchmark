#ifndef CPUIDENTIFICATION_H
#define CPUIDENTIFICATION_H

#endif // CPUIDENTIFICATION_H
#pragma once

#include "cacheinfo.h"
char* CPUVendor();
char* BrandString();
char* typeFamilyModel(int select);
char* frequencies(int select);
char* threadNumber();
CacheInfo cacheInfo(int select);
int coreNumberInt();
char* coreNumberChar();
char* architecture();
char* pageSize();
