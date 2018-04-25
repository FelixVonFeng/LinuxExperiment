#include <stdio.h>
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int prio;
	pid = fork();
	if(pid==0)
	{
		printf("child:pid = %d\n",getpid());
		prio = getpriority(PRIO_PROCESS,getpid());
		printf("sys init prio = %d\n",prio);
		nice(18);
		prio = getpriority(PRIO_PROCESS,getpid());
		printf("after nice(),prio = %d\n",prio);
		while(1);
		return 0;
	}
	wait(NULL);
	return 0;
}

