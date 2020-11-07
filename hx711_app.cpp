#include <stdio.h>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <math.h>  

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
              

// return = 0: voltage value from AIN0, unit: mV 
// < 0: failed 
int read_AIN0(float *fvoltage) 
{ 
    int value, ret = 0; 
    char filename[80]; 
    FILE *fp; 
    char buf[20]; 

    sprintf( filename, "/sys/bus/iio/devices/iio:device0/%s", iiotype[0]); 
    fp = fopen(filename, "rt" ); 
    if( fp==NULL ) { 
        printf("open %s fail!\n", filename); 
        *fvoltage = 0.0; 
        ret = -1; 
        return ret; 
    } 
    fread( buf, 1, sizeof(buf), fp ); 
    fclose(fp); 

    // convert to integer 
    sscanf( buf, "%d", &value ); 
    *fvoltage = 1.0 * value; 
    return ret; 
} 

       
int main(int argc, char** argv) 
{ 
  int ret = 0;
  int times = 10;
  float fvalue = 0.0;
  float value = 0.0;

  if(argc >= 2) {
    times = atoi(argv[1]);
  }

  printf("HX711 IIO AD test v2.0\n"); 
  printf("AIN0 = %.2f\n", fvalue);

  while(1) {
    for( int i = 0; i < times; i++) {
      if(read_AIN0(&fvalue) >= 0) { 
        value += fvalue;
      }
    }
    value = value/times;
    printf("AIN0 = %.2f  \n", value);
    value = 0.0;
    usleep(100000);
  }

  return ret; 
}