#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}
