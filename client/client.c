#include "client.h"

long long g_cur = 0;
long long g_len = 0;

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

void send_bit(pid_t pid, char c)
{
	if (c & 1)
	{
		if (kill(pid, SIGUSR1))
			ft_putendl_fd("kill error", 2);
	}
	else
	{
		if (kill(pid, SIGUSR2))
			ft_putendl_fd("kill error", 2);
	}
	usleep(200);
}

void send_sym(pid_t pid, char c)
{
	int j;

	j = 7;
	while (j >= 0)
	{
		send_bit(pid, (c >> j) & 1);
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

void	receiver(int signum)
{
	if (signum == SIGUSR2) {
		g_cur += 8;
		ft_putchar_fd('\r', 1);
		ft_putnbr_fd(g_cur, 1);
		ft_putchar_fd('/', 1);
		ft_putnbr_fd(g_len, 1);
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
	sigaddset(&act.sa_mask, SIGUSR2);

	act.sa_flags = SA_SIGINFO;
	act.sa_handler = receiver;
	if (sigaction(SIGUSR2, &act, 0))
	{
		ft_putendl_fd("Error: sigaction failed", 2);
		return (1);
	}

	g_len = (ft_strlen(argv[2]) + 1) * 8;
	//long long cur = 0;
	send(pid, argv[2]);

	//receive signal back from server
	while (g_cur != g_len) {
		//usleep(100);
	}
	ft_putendl_fd(" bits sended!", 1);

    return (0);
}