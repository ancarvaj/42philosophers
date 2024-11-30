#include "philo.h"

int	ft_init_fork(t_fork *fork, size_t nb_of_philos)
{
	size_t	i;

	i = 1;
	while (i <= nb_of_philos)
	{
		fork->fork_id = i;
		pthread_mutex_init(&fork->fork[i - 1], NULL);
		i++;
	}
	return (0);
}

int	ft_init_philo(t_philo *philo, size_t nb_of_philos)
{
	size_t	i;

	i = 1;
	while (i <= nb_of_philos)
	{
		philo->philo_id = i;
		philo->dead = false;
		philo->philo_ate = false;
		philo->own_fork = i;
		if (i < nb_of_philos)
			philo->side_fork = i + 1;
		else
			philo->side_fork = 1;
		i++;
	}
	return (0);
}

int	ft_init_rules(char **argv, t_rules *rules)
{
	rules->nb_of_philos = ft_atoi(argv[1]);
	if (rules->nb_of_philos > 250 || rules->nb_of_philos == 1)
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
	t_table_info *info;
	int	time = 0;
	info = (t_table_info *)p;

	while (1)
	{
		usleep(10000);
		time++;
		if (time == 10)
		{
			printf("muerto\n");
			info->number_of_philo_has_eaten--;
			return (NULL);
		}
	}
}

int	ft_init_philo_thread(pthread_t *philo, size_t nb_of_philos, void *philo_info)
{
	size_t	i;
	
	i = 0;
	while (i < nb_of_philos)
	{
		if (pthread_create(&philo[i], NULL, ft_philo_routine, philo_info))
			return (1);
		i++;
	}
	i = 0;
	while (i < nb_of_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_table_info	info;
	pthread_t	time_thread;
	pthread_t	philo_thread[250];

	if (ac != 5 && ac != 6)
		return (1);
	if (ft_check_args(av + 1))
		return (1);
	if (ft_init_rules(av, &info.rules))
		return (1);
	ft_init_philo(info.philo, info.rules.nb_of_philos);
	info.number_of_philo_has_eaten = info.rules.nb_of_philos;
	info.time.philo_has_eaten = &info.number_of_philo_has_eaten;
	pthread_create(&time_thread, NULL, ft_time_routine, &info.time);
	ft_init_fork(info.fork, info.rules.nb_of_philos);
	ft_init_philo_thread(philo_thread, info.rules.nb_of_philos, &info);
	pthread_join(time_thread, NULL);
	return (0);
}
//organizar files
