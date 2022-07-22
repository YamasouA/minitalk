#include "minitalk.h"

void	put_error(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR2) == -1)
				put_error("kill fail");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				put_error("kill fail");
		}
		usleep(50);
		i--;
	}
}

void	send_text(pid_t pid, char *text)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(text);
	i = 0;
	while (i < len)
	{
		send_char(pid, text[i]);
		i++;
	}
	send_char(pid, EOT);
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc != 3)
		put_error("argument should have 3");
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
		put_error("pid is bad");
	send_text(pid, argv[2]);
}
