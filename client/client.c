#include "client.h"

int	atoui(char *s, unsigned int *num)
{
	int	res;

	res = 0;
	while (*s == ' ')
		s++;
	if (*s == '\0')
		return (1);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (2);
		if (res * 10 + (*s - '0') < 0)
			return (3);
		res = res * 10 + (*s - '0');
		s++;
	}
	*num = res;
	return (0);
}

int send(pid_t pid, char *msg)
{
	int	i;
	int j;
	char c;

	i = 0; 	
	while (msg[i])
	{
		c = msg[i];
		j = 8;
		ft_putstr_fd("Sending: ", 1);
		ft_putchar_fd(msg[i], 1);
		ft_putstr_fd(" ", 1);
		while (j)
		{
			if (c & 256)
			{
				ft_putnbr_fd(c & 1, 1);
				if (kill(pid, SIGUSR1))
					ft_putendl_fd("kill error", 2);
			}
			else
			{
				ft_putnbr_fd(c & 1, 1);
				if (kill(pid, SIGUSR2))
					ft_putendl_fd("kill error", 2);
			}
			j--;
			c >>= 1;
		}
		ft_putstr_fd("\n", 1);
		//usleep(100);
		i++;
	}
	return (0);
}

void	receiver(int signum)
{
	(void)signum;
	ft_putendl_fd("Signal received", 1);
}

int main(int argc, char **argv)
{
	struct sigaction act;
	unsigned int pid;

	pid = 0;
    if (argc != 3)
	{
		ft_putendl_fd("Hint: <pid> <message>", 2);
        return (1);
	}
    
	if (atoui(argv[1], &pid))
	{
		ft_putendl_fd("Error: invalid pid", 2);
        return (1);
	}

	act.sa_handler = receiver;
	if (sigaction(SIGUSR2, &act, 0))
	{
		ft_putendl_fd("Error: sigaction failed", 2);
		return (1);
	}

	send(pid, argv[2]);

	//receive signal back from server
	while (1)
		pause();

    return (0);
}