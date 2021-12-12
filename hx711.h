#pragma once

#include <fcntl.h>
#include <string>
#include <fstream>

class Weight
{
public:
    Weight(int bus = 0);
    ~Weight();
    int read_AIN0(float *fvoltage);

private:
    std::string ScanDevice(int bus);
    char setpin_[64] = {0};
    std::string filename_;
    std::ifstream hx711_fp_;
};

