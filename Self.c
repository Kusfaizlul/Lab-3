#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

int main (void){

	void sigint_handler(int sig);

	int ppfds[2],temp,prime,flag = 0;
	pipe(ppfds);
	pid_t pid = fork();

	if(signal(SIGINT, sigint_handler) == SIG_ERR){
			perror("signal");
			exit(1);
		}

	if (pid == 0){ //child process
		int numb;
		printf(" +++++ Child Process  +++++\n"); 
		printf("\n Please enter an integer number : ");
		scanf("%d",&numb);
		write(ppfds[1],&numb,sizeof(numb));
		}
	else if (pid > 0){ //parents process

			wait(NULL);
			printf("\n +++++ Parent Process +++++\n");
			read(ppfds[0],&temp,sizeof(temp));
			prime = temp / 2;

			for (int i = 2 ; i <= prime; i++){
				if( prime % i == 0){
					flag = 1;
					break;
				}
			}
			if (flag == 0){
				printf ("\n %d Is a Prime Number !!\n\n",temp);
			}
			else {
				printf ("\n %d Is not a Prime Number !!\n\n",temp);
			}

			return 0;
	}
		else { //invalid process
			printf("\n Invalid Pid Vallue : %d",getpid());
			exit(1);
	}
}

void sigint_handler(int sig){
	printf(" - Aip Berani Nak Teminate !!! ");
}
