#include "minitalk.h"

void send_char(pid_t pid, char c)
{
	int	i;

	for (i = 15; i >= 0; --i) {
		if (c & (1 << i)){
			kill(pid, SIGUSR2);
			printf("1");
		}
		else{
			kill(pid, SIGUSR1);
			printf("0");
		}
		usleep(1000);
	}
	printf("\n");
}

void send_text(pid_t pid, char *text)
{
	size_t	len;
	char	c;

	len = ft_strlen(text);
	for (size_t i = 0; i < len; ++i)
	{
		c = text[i];
		printf("%c, %d\n", c, c);
		send_char(pid, c);
	}
	//send_char(pid, EOT);
}


int main(int argc, char *argv[])
{
	pid_t pid;
	pid = (pid_t)atol(argv[1]);
	if (kill(pid, SIGUSR1) == -1)
		printf("Hello\n");
	send_text(pid, argv[2]);
}
