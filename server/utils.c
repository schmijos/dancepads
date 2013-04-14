#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* ------------------------------------------------------------------------------ */
/* Ausgabe einer Meldung msg, gefolgt von der Fehlermeldung, die dem in errno */
/* gespeicherten Fehlercode entspricht */
/* anschließende Beendigung des Programms */
void errorExit(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

/* ------------------------------------------------------------------------------ */
/* Kopieren von Bytefolgen von einem Quell-File-Deskriptor zu einem Ziel-File- */
/* Deskriptor */
/* Das Kopieren endet, wenn keine Bytes mehr vom Ziel-Deskriptor gelesen werden */
#define BUFFLEN 1024
void copyData(int iDest, int iSrc) {
	char acBuff[BUFFLEN];
	int iCount;
	while ((iCount = read(iSrc, acBuff, sizeof(acBuff))) > 0) {
		if (write(iDest, acBuff, iCount) != iCount)
			errorExit("write");
	}
	if (iCount < 0)
		errorExit("read");
	return;
}
