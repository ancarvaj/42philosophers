#include "philo.h"

int	ft_init_rules(char **argv, t_rules *rules, size_t *nb_of_philos)
{
	*nb_of_philos = ft_atoi(argv[1]);
	if (*nb_of_philos > 250 || *nb_of_philos == 1)
		return (1);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		rules->n_times_must_eat = ft_atoi(argv[5]);
	else
		rules->n_times_must_eat = -1;
	return (0);
}

void	*ft_philo_routine(void	*p)
{
	t_philo_info *info;
	int	time = 0;
	info = (t_philo_info *)p;
	*(info->ready) = *(info->ready) - 1;
	while (1)
	{
		usleep(100);
		if (*(info->ready) == 0)
			break;
	}
	while (1)
	{
		usleep(100000);
		printf("hello from philo : %ld\n", info->philo_id);
		time++;
		if (time == 10)
		{
			printf("philo : %ld muerto\n", info->philo_id);
			*(info->philo_has_eaten) = *(info->philo_has_eaten) - 1;
			return (NULL);
		}
	}
}

int	ft_init_info(t_philo_info *philo, size_t nb_of_philos, t_simulation *sim)
{
	size_t	i;

	i = 0;
	philo->fork = sim->fork;
	while (i < nb_of_philos)
	{
		philo[i].ready = &sim->ready;
		philo[i].philo_has_eaten = &sim->philo_has_eaten;
		philo[i].current_time = &sim->time.current_time;
		philo[i].rules = sim->rules;
		philo[i].philo_id = i + 1;
		philo[i].dead = false;
		philo[i].philo_ate = false;
		philo[i].own_fork = i + 1;
		if (i + 1 == nb_of_philos)
			philo[i].side_fork = 1;
		else
			philo[i].side_fork = i + 2;
		i++;
	}
	return (0);
}

int	ft_init_philo(pthread_t *philo, t_philo_info *info, size_t nb_of_philo)
{
	size_t	i;

	i = 0;
	while (i < nb_of_philo)
	{
		pthread_create(&philo[i], NULL, ft_philo_routine, (void *)&(info[i]));
		i++;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}
