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

int	ft_atoi(const char *s)
{
	int	i;
	long int	n;

	if (ft_strlen(s) > 11)
		return (-1);
	i = -1;
	n = 0;
	while (s[++i])
		n = (n * 10) + (s[i] - '0');
	if (n > INT_MAX)
		return (-999);
	return (n);
}
