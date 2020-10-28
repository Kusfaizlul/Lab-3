#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<signal.h>

int main (void)
{
	void sigint_handler(int sig);
	void sigstp_handler(int stp);
	void sigquit_handler(int qit);

	char s[200];

	if(signal(SIGINT,sigint_handler) == SIG_ERR)
	{
		perror("signal");
		exit(1);
	}
	else if(signal(SIGTSTP,sigstp_handler) == SIG_ERR)
		{
			perror("signal");
			exit(1);
		}
		else if(signal(SIGQUIT,sigquit_handler) == SIG_ERR)
			{
				perror("signal");
				exit(1);
			}

	printf("Enter a string:\n");

	if(fgets(s,200,stdin)==NULL)
		perror("gets");
	else
		printf("you entered:%s\n",s);

	return 0;
}

void sigint_handler(int sig)
{
	printf(" - This is a special signal gandler for SIGINT (Terminate Handler) \n");
}

void sigstp_handler(int stp){
	printf(" - This is a special signal handler for SIGTSTP (Stop Handler) \n");}

void sigquit_handler(int qit){
	printf(" - This is a special signal handler for SIGQUIT (Quit Handler) \n");}
