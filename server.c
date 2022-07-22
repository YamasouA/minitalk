#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include "minitalk.h"

volatile sig_atomic_t	g_flag;

static void	ft_get_signal(int sig)
{
	g_flag = sig;
}

int	main(void)
{
	t_bit_data	receive_data;
	char		c;

	g_flag = 0;
	receive_data.bit_char = 0;
	ft_putstr_fd("PID: ", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	signal(SIGUSR1, ft_get_signal);
	signal(SIGUSR2, ft_get_signal);
	while (1)
	{
		pause();
		receive_data.bit_char += g_flag - SIGUSR1;
		receive_data.cnt++;
		if (receive_data.cnt == 8)
		{
			write(STDOUT_FILENO, &receive_data.bit_char, 1);
			receive_data.bit_char = 0;
			receive_data.cnt = 0;
		}
		else
			receive_data.bit_char = receive_data.bit_char << 1;
	}
}
