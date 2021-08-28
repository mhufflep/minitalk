#include "server.h"

//◦ signal
//◦ sigemptyset
//◦ sigaddset
//◦ sigaction

void	receiver(int signum, siginfo_t *info, void *unused)
{
	static char	c = 0;
	static int	power = 0;

	(void)unused;
	if (signum == SIGUSR1) {
		c |= 1 << (7 - power);
		ft_putnbr_fd(1, 1);

	} else {
		ft_putnbr_fd(0, 1);
	}
		//c += 1 << (7 - power);
	power++;
	//power += 1;
	if (power == 7)
	{
		ft_putstr_fd(" ", 1);
		ft_putchar_fd(c, 1);
		ft_putstr_fd("\n", 1);

		power = 0;
		c = 0;
		if (kill(info->si_pid, SIGUSR2))
			ft_putendl_fd("Error: cannot send signal back", 2);
	}
}

int main()
{
	struct sigaction act;

	ft_putstr_fd("pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putendl_fd("", 1);

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receiver;
	if (sigaction(SIGUSR1, &act, 0))
		ft_putendl_fd("Error: sigaction failed", 2);
	if (sigaction(SIGUSR2, &act, 0))
		ft_putendl_fd("Error: sigaction failed", 2);

	while (1)
		pause();

    return (0);
}