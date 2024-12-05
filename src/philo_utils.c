#include "philo.h"

int	ft_init_rules(char **argv, t_rules *rules, size_t *nb_of_philos)
{
	*nb_of_philos = ft_atoi(argv[1]);
	if (*nb_of_philos > 250)// || *nb_of_philos == 1)
		return (1);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		rules->n_times_must_eat = ft_atoi(argv[5]);
		if (rules->n_times_must_eat == 0)
			return (1);
	}
	else
		rules->n_times_must_eat = -1;
	return (0);
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
		info[i].own_fork = i;
		if (*(info[i].philo_has_eaten) > 1)
			info[i].more_than_one = 1;
		else
			info[i].more_than_one = 0;
		if (info[i].philo_id == nb_of_philos)
			info[i].side_fork = 0;
		else
			info[i].side_fork = i + 1;
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

int	ft_calculate_dead(t_philo_info *info, time_t last_meal)
{
	if (*(info->dead) == 1)
	{
		pthread_mutex_unlock(&info->fork[info->own_fork]);
		pthread_mutex_unlock(&info->fork[info->side_fork]);
		return (1);
	}
	else if (*(info->current_time) - last_meal > (time_t)info->rules.time_to_die)
	{
		printf("%ld %ld died\n", *(info->current_time), info->philo_id);
		pthread_mutex_unlock(&info->fork[info->own_fork]);
		pthread_mutex_unlock(&info->fork[info->side_fork]);
		*(info->dead) = 1;
		return (1);
	}
	return (0);
}

int	ft_sleep(t_philo_info *info, time_t last_meal)
{
	size_t	time_slept;


	printf("%ld %ld is sleeping\n", *(info->current_time), info->philo_id);
	time_slept = 0;
	while (info->rules.time_to_sleep - time_slept > 0)
	{
		if (ft_calculate_dead(info, last_meal))
			return (1);
		if (info->rules.time_to_sleep - time_slept >= 5)
			usleep(5 * 1000);
		else
			usleep((info->rules.time_to_sleep - time_slept) * 1000);
				time_slept = time_slept + 5;
	}
	printf("%ld %ld is thinking\n", *(info->current_time), info->philo_id);
	return (0);
}

int	ft_eat(t_philo_info *info, time_t *last_meal)
{
	int	time_ate;

	time_ate = 0;
	printf("%ld %ld is eating\n", *(info->current_time), info->philo_id);
	while (info->rules.time_to_eat - time_ate > 0)
	{
		if (time_ate == 15)
			*last_meal = *(info->current_time);
		if (info->rules.time_to_eat - time_ate >= 5)
			usleep(5 * 1000);
		else
			usleep((info->rules.time_to_eat - time_ate) * 1000);
		time_ate = time_ate + 5;
	}
	pthread_mutex_unlock(&info->fork[info->own_fork]);
	pthread_mutex_unlock(&info->fork[info->side_fork]);
	info->rules.n_times_must_eat--;
	return (0);
}

int	ft_get_fork(t_philo_info *info, time_t last_meal)
{
	int	side_fork;
	int	own_fork;

	side_fork = 0;
	own_fork = 0;
	while (!side_fork || !own_fork)
	{
		if (ft_calculate_dead(info, last_meal))
			return (1);
		if (!own_fork && !pthread_mutex_lock(&info->fork[info->own_fork]))
		{
			printf("%ld %ld has taken a fork\n", *(info->current_time), info->philo_id);
			own_fork = 1;
		}
		if (info->more_than_one && !side_fork && !pthread_mutex_lock(&info->fork[info->side_fork]))
		{
			printf("%ld %ld has taken a fork\n", *(info->current_time), info->philo_id);
			side_fork = 1;
		}
	}
	return (0);
}

//si empieza a comer no muere
//cuando termina de comer vuelve a iniciar el contador de muerte


void	*ft_philo_routine(void	*p)
{
	t_philo_info	*info;
	time_t		last_meal;

	info = (t_philo_info *)p;
	*(info->ready) = *(info->ready) - 1;
	while (*(info->ready) != 0)
		usleep(50);
	last_meal = 0;
	if (info->philo_id % 2)
		usleep(50);
	while (*(info->philo_has_eaten) > 0 && !*(info->dead))
	{
		if (ft_get_fork(info, last_meal))
			return (NULL);
		if (ft_eat(info, &last_meal))
			return (NULL);
		if (ft_sleep(info, last_meal))
			return (NULL);
		if (!info->rules.n_times_must_eat)
			*(info->philo_has_eaten) = *(info->philo_has_eaten) - 1;
	}
	return (NULL);
}
