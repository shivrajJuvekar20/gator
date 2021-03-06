/**
 * Copyright (C) Arm Limited 2010-2016. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef PMUXML_H
#define PMUXML_H

#include <set>
#include <string>
#include <vector>

#include "ClassBoilerPlate.h"

class GatorCpu
{
public:
    GatorCpu(std::string coreName, std::string id, std::string counterSet, const char * dtName,
             const char * speName, const std::set<int> & cpuIds, int pmncCounters, bool isV8);

    GatorCpu(const GatorCpu & that, const char * speName)
            : mCoreName(that.mCoreName),
              mId(that.mId),
              mCounterSet(that.mCounterSet),
              mDtName(that.mDtName),
              mSpeName(speName),
              mCpuIds(that.mCpuIds),
              mPmncCounters(that.mPmncCounters),
              mIsV8(that.mIsV8)
    {
    }

    CLASS_DEFAULT_COPY_MOVE(GatorCpu)
    ;

    const char *getCoreName() const
    {
        return mCoreName.c_str();
    }

    const char *getId() const
    {
        return mId.c_str();
    }

    const char *getCounterSet() const
    {
        return mCounterSet.c_str();
    }

    const char *getDtName() const
    {
        return (!mDtName.empty() ? mDtName.c_str() : nullptr);
    }

    const char *getSpeName() const
    {
        return (!mSpeName.empty() ? mSpeName.c_str() : nullptr);
    }

    bool getIsV8() const
    {
        return mIsV8;
    }

    const std::vector<int> & getCpuIds() const
    {
        return mCpuIds;
    }

    int getMinCpuId() const
    {
        return mCpuIds.front();
    }

    int getMaxCpuId() const
    {
        return mCpuIds.back();
    }

    int getPmncCounters() const
    {
        return mPmncCounters;
    }

    bool hasCpuId(int cpuId) const;

private:
    std::string mCoreName;
    std::string mId;
    std::string mCounterSet;
    std::string mDtName;
    std::string mSpeName;
    std::vector<int> mCpuIds;
    int mPmncCounters;
    bool mIsV8;
};

bool operator==(const GatorCpu & a, const GatorCpu & b);
bool operator<(const GatorCpu & a, const GatorCpu & b);

class UncorePmu
{
public:
    UncorePmu(std::string coreName, std::string id, std::string counterSet, int pmncCounters,
              bool hasCyclesCounter);

    CLASS_DEFAULT_COPY_MOVE(UncorePmu)
    ;

    const char *getCoreName() const
    {
        return mCoreName.c_str();
    }

    const char *getId() const
    {
        return mId.c_str();
    }

    const char *getCounterSet() const
    {
        return mCounterSet.c_str();
    }

    int getPmncCounters() const
    {
        return mPmncCounters;
    }

    bool getHasCyclesCounter() const
    {
        return mHasCyclesCounter;
    }

private:
    std::string mCoreName;
    std::string mId;
    std::string mCounterSet;
    int mPmncCounters;
    bool mHasCyclesCounter;
};

struct PmuXML
{
    static const char * const DEFAULT_XML;
    static const unsigned DEFAULT_XML_LEN;

    const GatorCpu *findCpuByName(const char * const name) const;
    const GatorCpu *findCpuById(const int cpuid) const;
    const UncorePmu *findUncoreByName(const char * const name) const;

    std::vector<GatorCpu> cpus;
    std::vector<UncorePmu> uncores;
};

#endif // PMUXML_H
