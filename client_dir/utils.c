#include "client.h"

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