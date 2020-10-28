#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main (void)
{
	int pipefds[2];
	char buffer[5];

	if(pipe(pipefds) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	char *pin = "4128\0";

	printf(" Writing a PIN to pipe... \n");
	write(pipefds[1], pin, sizeof(pin));
	printf(" Done. \n\n");

	printf(" Reading a number from Pipe...\n");
	read(pipefds[0], buffer , sizeof(buffer));
	printf(" Done.\n\n");

	printf(" Number from pipe : %s\n", buffer);

	return EXIT_SUCCESS;

}

