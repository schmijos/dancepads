#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <wiringPiSPI.h>
#include "utils.h"
#include "uds.h"

void *run_spi(void *arg);
void *run_tty(void *arg);
void *run_uds(void *arg);
void sigfunc(int sig_no);

int main() {
	// TODO Take Args for uds input and service
	
	// Take end signal
    struct sigaction sa = {{0}};
	sa.sa_handler = &sigfunc;
	sigaction(SIGINT, &sa, NULL);
	
	// Threads & Mutex
    pthread_t tty_thread;
	//pthread_t uds_thread;
	pthread_t spi_thread;
	dp_exchange_t params;
	pthread_mutex_init (&params.mutex, NULL);

	// TODO Monitor and Set the right Thread Priority
	pthread_create(&spi_thread, NULL, run_spi, &params);
	usleep(100000);
	pthread_create(&tty_thread, NULL, run_tty, &params);
	//pthread_create(&uds_thread, NULL, run_uds, &params);
	//pthread_join(uds_thread, NULL);
	pthread_join(tty_thread, NULL);
	pthread_join(spi_thread, NULL);
 	
	return 0;
}

void sigfunc(int sig_no)
{
	printf("Signal %d", sig_no);
	exit(EXIT_FAILURE);
}

void* run_uds(void* arg){ 
	dp_exchange_t* p = (dp_exchange_t*)(arg);
	uds_listen(p);
	printf("uds server ended abnormally!\n");
	return NULL;
}

void* run_tty(void* arg){ 
	dp_exchange_t* p = (dp_exchange_t*)(arg);
	
	while(1) {
		int padnr, rgb, r, g, b;

		printf("Commit Command [padnr rgbflag red green blue]: ");
		scanf("%d", &padnr);
		scanf("%d", &rgb);
		scanf("%d", &r);
		scanf("%d", &g);
		scanf("%d", &b);

		// Commit command to choosen pad
		pthread_mutex_lock(&p->mutex);
		  p->padnr = padnr;
		  p->command.rgb.r = r;
		  p->command.rgb.g = g;
		  p->command.rgb.b = b;
		  p->command.is_rgb = rgb;
    	pthread_mutex_unlock(&p->mutex);

		// Await result
		printf("Awaiting result from pad %d\n", p->padnr);
		while(p == 0) {
			usleep(10000);
		}
		printf("SPI Status: %d %d\n", p->padnr, p->status.is_pressed);

		usleep(10000);
	}
	return NULL;
}

void* run_spi(void* arg){ 
	dp_exchange_t* p = (dp_exchange_t*)(arg);

	// Initialize SPI Device
    int channel = 1;
    int speed = 500000;
    int fd = wiringPiSPISetup(channel, speed);
    if (fd == -1) {
        printf( "SPI Setup Error: %s\n", strerror(errno));
		return NULL;
    }
    printf("SPI Device FD:\t%d\n", fd);
	
	// Data Exchange Loop
	while(1) {
		// Commit Status
		pthread_mutex_lock(&p->mutex);
		
		// Consume Command
		if (p->command.is_not_empty) {
			// Debug Output: Say, what we got here
    		printf("\n\nSPI: Write to Pad %d\n", p->padnr);
			if (p->command.is_rgb) {
    			printf("  Type:\tRGB data\n");
				printf("  Data:\trgb(%d,%d,%d)\n", 
					p->command.rgb.r * 8,
					p->command.rgb.g * 8,
					p->command.rgb.b * 8);
			} else {
    			printf("  Type:\tCommand\n");
				printf("  Data:\tTODO");
			}
			printf("  Size:\t%d Bytes\n\n", sizeof(p->command.bytes));

			// SPI Read and Write
    	  	unsigned char* data = p->command.bytes;
          	int ret = wiringPiSPIDataRW(channel, data, ARRAY_SIZE(data));
          	if (ret == -1) {
        		printf( "Error at SpiRW: %s\n", strerror(errno));
          	} else {
            	printf("Bytes Written:\t%d\n", ret);
            	printf("Resonse Data:\t%d, %d\n", data[0], data[1]);
				// TODO Status entgegennehmen
        	}

			// TODO Status Output

			// Actually consume command by setting everything back to zero
			p->command.is_not_empty = 0;
		}

    	pthread_mutex_unlock(&p->mutex);
		
		usleep(1000000);
	}
	return NULL;
}
