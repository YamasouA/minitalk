#include "minitalk.h"

void send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0) {
		if (c & (1 << i)){
			kill(pid, SIGUSR2);
			//printf("1");
		}
		else{
			kill(pid, SIGUSR1);
			//printf("0");
		}
		usleep(30);
		i--;
	}
}

void send_text(pid_t pid, char *text)
{
	size_t	len;
	size_t	i;
	char	c;

	len = ft_strlen(text);
	i = 0;
	while (i < len)
	{
		c = text[i];
		send_char(pid, c);
		i++;
	}
	send_char(pid, EOT);
}


int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: ./client [server process-id] [message]\n", STDERR_FILENO);
		return 1;
	}
	pid_t pid;
	pid = (pid_t)atol(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1) {
		printf("Not work this pid\n", STDERR_FILENO);
		return 1;
	}
	send_text(pid, argv[2]);
	return 0;
}

