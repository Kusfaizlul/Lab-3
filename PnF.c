#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PIN_LENGTH 4		//const veriable
#define PIN_WAIT_INTERVAL 2

void getPIN(char pin[PIN_LENGTH+ 1])
{
	srand(getpid() + getppid()); //GETPPID = ID PARENTS  GETPID = RANDOM GENERATE

	pin[0] = 49 + rand() % 7;

	for(int i = 1; i < PIN_LENGTH + 1; i++)
	{
		pin[i] = 48 + rand() % 7;
	}

	pin[PIN_LENGTH] = '\0';  //null operator
}

int main (void) 
{
	while(1){
		int pipefds[2];
		char pin [PIN_LENGTH + 1];
		char buffer [PIN_LENGTH + 1];

		pipe(pipefds);

		pid_t pid = fork();

		if(pid == 0){
			getPIN(pin); //Generate random PIN
			close(pipefds[0]); //Close Read Fd
			write(pipefds[1],pin, PIN_LENGTH + 1); //Wirte PIN to pipe

			printf("Generating PIN in child and sending to parent . . .\n");

			sleep(PIN_WAIT_INTERVAL); // Delaying PIN GENERATOR

			exit(EXIT_SUCCESS);
		}

		if(pid > 0){ //Parent Processs
			wait(NULL); //Waiting for child

			close(pipefds[1]); //Close write Fd
			read(pipefds[0],buffer,PIN_LENGTH + 1); //Read PIN from  pipe
			close(pipefds[0]); //close read Fd
			printf("Parent received PIN '%s' from child.\n\n", buffer);
		}
	}
	return EXIT_SUCCESS;
}
