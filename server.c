#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "minitalk.h"

volatile sig_atomic_t g_flag = 0;

void	ft_get_signal(int sig)
{
	g_flag = sig;
}


int main()
{
	bit_data	i;
	char	c;

	i.bit_str = 0;
	printf("PID: %d\n", getpid());
	signal(SIGUSR1, ft_get_signal);
	signal(SIGUSR2, ft_get_signal);
	while (1)
	{
        	pause();
		i.bit_str += g_flag - SIGUSR1;
		i.cnt++;
		//printf("%d\n", i.cnt);
		if (i.cnt == 16) {
			//printf("%zu\n", i.bit_str);
			c = i.bit_str;
			//printf("%c\n", c);
			write(1, &c, 1);
			i.bit_str = 0;
			i.cnt = 0;
		}
		else
			i.bit_str = i.bit_str << 1;
		//printf("i: %zu\n", i.bit_str);
		//printf("\n");
	}
}
