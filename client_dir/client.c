#include "client.h"

void receiver(int signum, siginfo_t *info, void *unused)
{
	(void)info;
	(void)unused;
	t_data *data;

	if (signum == SIGUSR1)
	{
		data = data_ctl(0);
		data->received++;

		ft_putchar_fd('\r', 1);
		ft_putnbr_fd(data->received, 1);
		ft_putchar_fd('/', 1);
		ft_putnbr_fd(data->total, 1);
	}
}

int main(int argc, char **argv)
{
	t_data data;
	struct sigaction act;

    if (argc != 3)
	{
		ft_putendl_fd("Hint: <pid> <message>", 2);
        return (1);
	}

	if (atoui(argv[1], &data.pid))
	{
		ft_putendl_fd("Error: invalid pid", 2);
        return (1);
	}

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receiver;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	if (sigaction(SIGUSR1, &act, 0))
	{
		ft_putendl_fd("Error: sigaction failed", 2);
		return (1);
	}

	data_ctl(&data);
	send(&data, argv[2]);
    return (0);
}