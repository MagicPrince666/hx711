#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>

#include "hx711.h"

char iiotype[16][32] = { 
        "in_voltage0_raw", 
        "in_voltage1_raw", 
        "in_voltage2_raw", 
        "in_voltage3_raw", 
        "in_voltage4_raw", 
        "in_voltage5_raw", 
        "in_voltage6_raw", 
        "in_voltage7_raw"
};

Weight::Weight(int bus) {
    filename_ = ScanDevice(bus);
    // std::cout <<"Devie is " << filename_ <<"\n";
    hx711_fp_.open(filename_, std::ios::in);
    if(!hx711_fp_.is_open()) {
        printf("open %s fail!\n", filename_.c_str());
        exit(0);
    }
}

Weight::~Weight() {
    hx711_fp_.close();
}

std::string Weight::ScanDevice(int bus) {
    char filename[80] = {0};
    if(bus == -1) { //扫描设备
        for(int i = 0; i < 10; i++) {
            int ret = sprintf(filename, "/sys/bus/iio/devices/iio:device%d/name", i);
            filename[ret] = 0;
            struct stat buffer;   
            if(stat(filename, &buffer) == 0) {
                std::ifstream iio_name;
                iio_name.open(filename, std::ios::in);
                char buff[64] = {0};
                // int len = iio_name.read(buff, sizeof(buff));
                // buff[len] = 0;
                iio_name.read(buff, sizeof(buff));
                std::string name = buff;

                int index = name.find("hx711");
                if(-1 != index) {
                    std::cout <<"find hx711 device\n";
                    int ret = sprintf(filename, "/sys/bus/iio/devices/iio:device%d/%s", i, iiotype[0]);
                    filename[ret] = 0;
                    break;
                } else {
                    std::cout <<"device name is " << name << "\n";
                }
            } else {
                // 搜索完了，没有找到对应设备
                std::cout <<"iio bus scan end\n";
                exit(0);
            }
        }
    } else {
        sprintf(filename, "/sys/bus/iio/devices/iio:device%d/%s", bus , iiotype[0]);
    }
    std::string device = filename;
    return device;
}

// return = 0: voltage value from AIN0, unit: mV 
// < 0: failed 
int Weight::read_AIN0(float *fvoltage)
{ 
    int value, ret = 0;
    char buf[20];

    hx711_fp_.seekg(0, std::ios::beg);
    hx711_fp_.read(buf, sizeof(buf));

    // convert to integer
    ret = sscanf( buf, "%d", &value );
    *fvoltage = 0.0001 * value;
    return ret;
} 