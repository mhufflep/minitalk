#include "send.h"

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

void send_sym(t_data *data, char c)
{
	int j;
	long long tmp;

	j = 7;
	while (j >= 0)
	{
		tmp = data->received;
		send_bit(data->pid, (c >> j) & 1);
		while (tmp == data->received)
		{
			usleep(100);
		}
		j--;
	}
}

int send(t_data *data, char *msg)
{
	int	i;

	i = 0;
	data->received = 0;
	data->total = ft_strlen(msg) * 8;
	data->total += 8;
	while (msg[i] != '\0')
	{
		send_sym(data, msg[i]);
		i++;
	}
	send_sym(data, '\0');
	ft_putendl_fd(" bits sent!", 1);
	return (0);
}