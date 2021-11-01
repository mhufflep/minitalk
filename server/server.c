#include "server.h"

//◦ signal
//◦ sigemptyset
//◦ sigaddset
//◦ sigaction

#define BUF_SIZE 1

void	receiver(int signum, siginfo_t *info, void *unused)
{
	(void)unused;
	(void)info;

	static char buf[BUF_SIZE] = {0};
	static int power = 0;
	static int i = 0;

	if (signum == SIGUSR1)
	{
		buf[0] |= 1 << (7 - power);
	}

	if (++power == 8)
	{
		i++;

		if (buf[i - 1] == '\0' || i == BUF_SIZE)
		{
			write(1, buf, ft_strlen(buf));
			ft_memset(buf, 0, BUF_SIZE);
			i = 0;
		}
	
		if (kill(info->si_pid, SIGUSR2))
			ft_putendl_fd("kill error", 2);
		
		power = 0;
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
		;

    return (0);
}