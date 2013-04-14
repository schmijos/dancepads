#ifndef UTILS_H_
#define UTILS_H_

#define PAD_COUNT 10

union dp_command {
	int is_cmd:1;
	struct {
		int   :1;
		int r :5;
		int g :5;
		int b :5;
	} rgb;
	char bytes[2];
};
typedef union dp_command dp_command_t;

union dp_status {
	int is_pressed:1;
	struct {
		int       :1;
		int value :7;
	} data;
	char byte;
};
typedef union dp_status dp_status_t;

struct params {
    pthread_mutex_t mutex;
	int command;
	int status;
};
typedef struct params params_t;

void errorExit(char* msg);
void copyData(int iDest, int iSrc);

#endif /* UTILS_H_ */
