#ifndef DATA_H
# define DATA_H

# define GET_DATA 0

typedef struct s_data
{
	unsigned int pid;

	long long total;
	long long received;

}				t_data;

t_data *data_ctl(t_data *set);

#endif