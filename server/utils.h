#ifndef UTILS_H_
#define UTILS_H_

#define PAD_COUNT 10

union dp_command {
	unsigned int is_cmd:1;
	struct {
		unsigned int   :1;
		unsigned int r :5;
		unsigned int g :5;
		unsigned int b :5;
	} rgb;
	unsigned char bytes[2];
};
typedef union dp_command dp_command_t;

union dp_status {
	unsigned int is_pressed:1;
	struct {
		unsigned int       :1;
		unsigned int value :7;
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
