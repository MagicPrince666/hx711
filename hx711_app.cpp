#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#include "hx711.h"
  
int main(int argc, char** argv) 
{
  float fvalue = 0.0;
  float value = 0.0;

  
  printf("HX711 IIO AD test v2.0\n"); 

  while(1) {
    Weight weight(1);
    if(weight.read_AIN0(&fvalue) >= 0) {
      value = fvalue * 9.2 - 7870.0;
    }
  
//    printf("fvalue = %.2f  \n", fvalue);
    printf("Weight = %.2f  g\n", value);
    value = 0.0;
    sleep(1);
  }

  return 0;
}