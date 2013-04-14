/**
 * VSHSR Dancepad Project
 * SPI Test on Raspberry Pi
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wiringPiSPI.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/* Dancepads Color Definition */
union DP_Color {
    struct {
        unsigned int is_cmd   :  1;
        unsigned int operator :  5;
        unsigned int argument : 10;
    } cmd;
    struct {
        unsigned int is_cmd : 1;
        unsigned int red    : 5;
        unsigned int green  : 6;
        unsigned int blue   : 5;
    } rgb;
    unsigned char bytes[2];
    unsigned int is_command : 1;
};

/* Test Read and Write for SPI */
int testWiringPi(union DP_Color color)
{
    int channel = 1;
    int speed = 500000;
    unsigned char * data = color.bytes;
    int fd = wiringPiSPISetup(channel, speed);
    if (fd == -1) {
        printf( "Error: %s\n", strerror(errno));
    } else {
        printf("SPI Device FD:\t%d\n", fd);
        int ret = wiringPiSPIDataRW(channel, data, ARRAY_SIZE(data));
        if (ret == -1) {
            printf( "Error: %s\n", strerror(errno));
        } else {
            printf("Bytes Written:\t%d\n", ret);
            printf("Resonse Data:\t%d, %d\n", data[0], data[1]);
        }
    }

    return EXIT_SUCCESS;
}

/* Application Entry  Point */
int main(int argc, char *argv[])
{
    union DP_Color x;
    printf("Size of Struct: %d\n", sizeof(x));
    x.rgb.red   = 31;
    x.rgb.green = 31;
    x.rgb.blue  = 31;
    printf("Bytes: %d, %d\n", x.bytes[0], x.bytes[1]);

    int r = testWiringPi(x);
    printf("Test Result: %d\n", r);
    return EXIT_SUCCESS;
}
