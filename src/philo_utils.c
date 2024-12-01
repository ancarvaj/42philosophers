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

int	ft_calculate_dead()
{
	while (1)
	{
		return (0);
	}
	return (0);
}

int	ft_sleep(t_philo_info *info)
{
	while (1)
	{
		return (0);
	}
	return (0);
}
int	ft_get_fork(t_philo_info *info, time_t last_meal)
{
	while (1)
	{
		if (pthread_mutex_lock(own_fork) && pthread_mutex_lock(side_fork))
			return (0);
		if (ft_calculate_dead(time))
			return (1);
		usleep(10);
	}
	return (0);
}

void	*ft_philo_routine(void	*p)
{
	t_philo_info	*info;
	time_t		last_meal;
	info = (t_philo_info *)p;
	*(info->ready) = *(info->ready) - 1;
	while (1)
		if (*(info->ready) == 0)
			break;
	last_meal = *(info->current_time);
	if (info->philo_id % 2 == 0)
		usleep(50);
	while (!*(info->dead) && *(info->philo_has_eaten))
	{
		if (ft_get_fork(info))//coger tenedores + comer
			return (NULL);
		if (ft_eat(info)) // comer + soltar tenedores
			return (NULL);
		if (ft_sleep(fork))//dormir + pensar
			return (NULL);
	}
	return (NULL);
}

int	ft_init_info(t_philo_info *info, size_t nb_of_philos, t_simulation *sim)
{
	size_t	i;

	i = 0;

	while (i < nb_of_philos)
	{
		info[i].ready = &sim->ready;
		info[i].dead = &sim->dead;
		info[i].philo_has_eaten = &sim->philo_has_eaten;
		info[i].rules = sim->rules;
		info[i].fork = sim->fork;
		info[i].current_time = &sim->time.current_time;
		info[i].philo_id = i + 1;
		info[i].philo_ate = false;
		if (i + 1 == nb_of_philos)
			info[i].side_fork = 0;
		else
			info[i].side_fork = i;
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
		pthread_create(&philo[i], NULL, ft_philo_routine, (void *)&info[i]);
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
