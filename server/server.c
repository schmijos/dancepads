#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include "utils.h"
#include "uds.h"

void *run_spi(void *arg);
void *run_tty(void *arg);
void *run_uds(void *arg);
void sigfunc(int sig_no);

int main() {
	// Take end signal
    struct sigaction sa = {{0}};
	sa.sa_handler = &sigfunc;
	sigaction(SIGINT, &sa, NULL);
	
	// Threads & Mutex
    pthread_t tty_thread, uds_thread, spi_thread;
	params_t params;
	pthread_mutex_init (&params.mutex , NULL);

	//pthread_create(&spi_thread, NULL, run_spi, &params);
	pthread_create(&uds_thread, NULL, run_uds, &params);
	//pthread_create(&tty_thread, NULL, run_tty, &params);

	//pthread_join(spi_thread, NULL);
	pthread_join(uds_thread, NULL);
	//pthread_join(tty_thread, NULL);
 	
	return 0;
}

void sigfunc(int sig_no)
{
	printf("Signal %d",sig_no);
	exit(EXIT_FAILURE);
}

void* run_uds(void* arg){ 
	params_t* p = (params_t*)(arg);
	uds_listen(p);
	printf("uds server ended abnormally!");
}

void* run_tty(void* arg){ 
	params_t* p = (params_t*)(arg);
	while(1) {
		// SPI Status Output
		printf("SPI Status: %d\n", p->status);

		// Read Command from stdin
		int cmd, r, g, b;
		scanf("%d", &cmd);
		scanf("%d", &r);
		scanf("%d", &g);
		scanf("%d", &b);

		// Commit Command
		pthread_mutex_lock(&p->mutex);
		p->command = cmd;
    	pthread_mutex_unlock(&p->mutex);
		
		usleep(10000);
	}
}

void* run_spi(void* arg){ 
	params_t* p = (params_t*)(arg);
	int i = 0;
	while(1) {
		// Commit Status
		pthread_mutex_lock(&p->mutex);
		p->status = ++i;
		if (p->command != 0) {
    		printf("SPI got command %d\n", p->command);
			p->command = 0;
		}
    	pthread_mutex_unlock(&p->mutex);
		usleep(1000000);
	}
}
