#include "philo.h"

int	ft_init_fork(pthread_mutex_t *fork, size_t nb_of_philos)
{
	size_t	i;

	i = 0;
	while (i < nb_of_philos)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	return (0);
}
