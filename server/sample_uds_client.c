/*
 * udsclient.c
 *
 *  Created on: 26.03.2013
 *      Author: schmijos
 *      Source: http://www.netzmafia.de/skripten/server/ThomasSocket2.pdf
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include "utils.h"

#define SOCKET_PATH "/tmp/dancepad_socket"
#define FD_STDIN 0
#define FD_STDOUT 1

int main(int argc, char *argv[]) {
	struct sockaddr_un strAddr;
	socklen_t lenAddr;
	int fdSock;

	if ((fdSock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		errorExit("socket");

	strAddr.sun_family = AF_UNIX; /* Unix domain */
	strcpy(strAddr.sun_path, SOCKET_PATH);
	lenAddr = sizeof(strAddr.sun_family) + strlen(strAddr.sun_path);

	printf("Found Socket %d\n", fdSock);
	if (connect(fdSock, (struct sockaddr*) &strAddr, lenAddr) != 0)
		errorExit("connect");

	printf("Choose Pad by Number:\n");
	copyData(fdSock, FD_STDIN);

	printf("Pad Status: ");
	copyData(FD_STDOUT, fdSock);

	printf("\nSend Command to Pad:\n");
	copyData(fdSock, FD_STDIN);

	close(fdSock);
	printf("Connection closed.\n");
	return 0;
}
