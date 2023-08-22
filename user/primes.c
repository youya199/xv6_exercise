#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void new_proc(int p[2]){
	int prime;
	int n;
	close(p[1]);
	read(p[0], &prime, 4);
	printf("prime %d\n", prime);//first top number print as prime number

	if(read(p[0], &n, 4)){
		int newp[2];
		pipe(newp);
		if(n%prime)write(newp[1], &n, 4);

		while(read(p[0], &n, 4)){
			if(n%prime)write(newp[1], &n, 4);
		}//now we have added all numbers to newpipe, which are not multiples of prime
		close(p[0]);//now the older pipe is totally shut down,we fork only now to give child process only one new pipe
	
		if (fork() == 0)
		{
			new_proc(newp);
		}else
		{
			close(newp[0]);
			close(newp[1]);
			wait(0);
		}
	}
	exit(0);
}

int main(int argc, char const *argv[])
{
	int p[2];
	pipe(p);
	if (fork() == 0)
	{
		new_proc(p);
	}else
	{
		close(p[0]);
		for(int i = 2; i <= 35; i++)
		{
			write(p[1], &i, 4);
		}
		close(p[1]);
		wait(0);
		exit(0);
	}
	return 0;
}
