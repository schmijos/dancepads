#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include "utils.h"

#define SOCKET_PATH "/tmp/dancepad_socket"

void uds_listen(dp_exchange_t* p) {
	struct sockaddr_un strAddr;
	socklen_t lenAddr;
	int fdSock;
	int fdConn;

	if ((fdSock = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
		errorExit("socket");

	unlink(SOCKET_PATH); /* Sicherstellung, daß SOCKET_PATH nicht existiert */
	strAddr.sun_family = AF_UNIX; /* Unix Domain */
	strcpy(strAddr.sun_path, SOCKET_PATH);

	lenAddr = sizeof(strAddr.sun_family) + strlen(strAddr.sun_path);
	if (bind(fdSock, (struct sockaddr*) &strAddr, lenAddr) != 0)
		errorExit("bind");

	if (listen(fdSock, 5) != 0)
		errorExit("listen");

	printf("uds server initialized with socket %d\n", fdSock);
	while ((fdConn = accept(fdSock, (struct sockaddr*) &strAddr, &lenAddr)) >= 0) {
		// Read Pad Number
		// p->padnr
		char padNr[1024];
		if (read(fdConn, padNr, 8) < 0) {
			errorExit("read");
		}

		printf("Read: %s\n", padNr);

		// Write dp_status_t of Pad identified before
		// p->status
		char* padStatus = "42";
		if (write(fdConn, padStatus, 3) < 0) {
			errorExit("write");
		}

		printf("Wrote: %s\n", padStatus);
		
		// Read Command (dp_command_t)
		// p->command
		char padCmd[2];
		if (read(fdConn, padCmd, 2) < 0) {
			errorExit("read");
		}
		
		printf("uds got %s for Pad %s\n", padCmd, padNr);
		close(fdConn);
	}
	close(fdSock);
}
