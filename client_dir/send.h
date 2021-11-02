#ifndef SEND_H
# define SEND_H

# include "data.h"
# include "utils.h"

# include <signal.h>
# include <sys/types.h>

void	send_bit(pid_t pid, char c);
void	send_sym(t_data *data, char c);
int		send(t_data *data, char *msg);

#endif