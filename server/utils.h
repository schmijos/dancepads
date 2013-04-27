#ifndef UTILS_H_
#define UTILS_H_

#define PAD_COUNT 10
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

// pack content for SPI transfer
union dp_command {
	unsigned int is_rgb : 1 __attribute__ ((packed));
	struct {
		unsigned int   : 1 __attribute__ ((packed));
		unsigned int r : 5 __attribute__ ((packed));
		unsigned int g : 5 __attribute__ ((packed));
		unsigned int b : 5 __attribute__ ((packed));
	} rgb;
	unsigned char bytes[2];
	unsigned int is_not_empty : 16 __attribute__ ((packed));
};
typedef union dp_command dp_command_t;

// pack content for SPI transfer
union dp_status {
	unsigned int is_pressed : 1 __attribute__ ((packed));
	struct {
		unsigned int       : 1 __attribute__ ((packed));
		unsigned int value : 7 __attribute__ ((packed));
	} data;
	unsigned char byte;
};
typedef union dp_status dp_status_t;

struct dp_exchange {
    pthread_mutex_t mutex;
	unsigned int padnr;
	dp_command_t command;
	dp_status_t status;
};
typedef struct dp_exchange dp_exchange_t;

void errorExit(char* msg);
void copyData(int iDest, int iSrc);

#endif /* UTILS_H_ */
