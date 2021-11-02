#include "data.h"

t_data *data_ctl(t_data *set)
{
	static t_data *data;

	if (data == 0)
	{
		data = set;
	}
	return data;
}
