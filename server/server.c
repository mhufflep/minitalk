#include "server.h"

void	receiver(int signum, siginfo_t *info, void *unused)
{
	(void)unused;

	static char symbol = 0;
	static int shift = 0;

	if (signum == SIGUSR1)
	{
		symbol |= 1 << (7 - shift);
	}

 	if (++shift == 8)
	{
		write(1, &symbol, 1);
		symbol = 0;	
		shift = 0;
	}

	if (kill(info->si_pid, SIGUSR1))
	{
		ft_putendl_fd("Cannot send signal back", 2);
	}
}

int main()
{
	struct sigaction act;

	ft_putstr_fd("pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);

	sigemptyset(&act.sa_mask);
	
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receiver;

	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);

	if (sigaction(SIGUSR1, &act, 0))
		ft_putendl_fd("Error: sigaction failed", 2);
	if (sigaction(SIGUSR2, &act, 0))
		ft_putendl_fd("Error: sigaction failed", 2);

	while (1)
		usleep(50);

    return (0);
}