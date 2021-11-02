#include "client.h"

#define ADD_BIT -1
#define GET_CUR -2

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

int track_len(long long arg) {

	static long long num = 0;
	static long long len = 0;

	if (arg == GET_CUR)
	{
		return num;
	}

	if (arg != ADD_BIT)
	{
		len = arg;
		return 0;
	}

	num++;

	ft_putchar_fd('\r', 1);
	ft_putnbr_fd(num, 1);
	ft_putchar_fd('/', 1);
	ft_putnbr_fd(len, 1);

	return (num == len);
}

void send_bit(pid_t pid, char c)
{
	if (c & 1)
	{
		if (kill(pid, SIGUSR1))
		{
			ft_putendl_fd("Cannot send signal SIGUSR1", 2);
		}
	}
	else
	{
		if (kill(pid, SIGUSR2))
		{
			ft_putendl_fd("Cannot send signal SIGUSR2", 2);
		}
	}
}

void send_sym(pid_t pid, char c)
{
	int j;
	int tmp;

	j = 7;
	while (j >= 0)
	{
		tmp = track_len(GET_CUR);
		send_bit(pid, (c >> j) & 1);
		while (tmp == track_len(GET_CUR))
			usleep(100);
		j--;
	}
}

int send(pid_t pid, char *msg)
{
	int	i;

	i = 0; 	
	while (msg[i] != '\0')
	{
		send_sym(pid, msg[i]);
		i++;
	}
	send_sym(pid, '\0');
	return (0);
}

void	receiver(int signum, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;

	if (signum == SIGUSR1) {
		track_len(ADD_BIT);
	}
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

	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receiver;
	if (sigaction(SIGUSR1, &act, 0))
	{
		ft_putendl_fd("Error: sigaction failed", 2);
		return (1);
	}

	track_len((ft_strlen(argv[2]) + 1) * 8);

	send(pid, argv[2]);

	ft_putendl_fd(" bits sended!", 1);

    return (0);
}