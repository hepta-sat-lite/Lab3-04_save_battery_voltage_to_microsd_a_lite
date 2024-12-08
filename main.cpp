#include "mbed.h"
#include "LITE_CDH.h"
#include "LITE_EPS.h"
 
RawSerial pc(USBTX,USBRX,9600);
LITE_EPS  eps(PA_0,PA_4);
LITE_CDH  cdh(PB_5, PB_4, PB_3, PA_8, "sd", PA_3);
 
int main()
{

    float batvol;
    char str[100];
    mkdir("/sd/mydir", 0777);
    FILE *fp = fopen("/sd/mydir/test.txt","w");
    if(fp == NULL) {
        error("Could not open file for write\r\n");
    }
    for(int i = 0; i < 10; i++) {
        eps.vol(&batvol);
        fprintf(fp,"%f\r\n",batvol);
    }
    fclose(fp);
    fp = fopen("/sd/mydir/test.txt","r");
    for(int j = 0; j < 10; j++) {
        fgets(str,100,fp);
        pc.puts(str);
    }
    fclose(fp);
    pc.printf("Goodbye!!\r\n");
}