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

int	ft_calculate_dead(t_philo_info *info, time_t last_meal)
{
	if (*(info->dead) == true)
	{
		printf("%ld %ld is dead\n", *(info->current_time), info->philo_id);
		return (1);
	}
	if (*(info->current_time) - last_meal > (time_t)info->rules.time_to_die)
	{
		printf("%ld %ld is dead\n", *(info->current_time), info->philo_id);
		*(info->dead) = true;
		return (1);
	}
	return (0);
}

int	ft_sleep(t_philo_info *info, time_t last_meal)
{
	size_t	time_slept;


	printf("%ld %ld is sleeping\n", *(info->current_time), info->philo_id);
	time_slept = 0;
	while (1)
	{
		if (info->rules.time_to_sleep - time_slept >= 5)
			usleep(5 * 1000);
		else
		{
			usleep((info->rules.time_to_sleep - time_slept) * 1000);
			printf("%ld %ld is thinking\n", *(info->current_time), info->philo_id);
		}
		if (ft_calculate_dead(info, last_meal))
			return (1);
		time_slept = time_slept + 5;
		if (info->rules.time_to_sleep - time_slept == 0)
		{
			printf("%ld %ld is thinking\n", *(info->current_time), info->philo_id);
			return (0);
		}
		usleep(500);
	}
	return (0);
}

int	ft_eat(t_philo_info *info, time_t *last_meal)
{
	printf("%ld %ld is eating\n", *(info->current_time), info->philo_id);
	usleep(info->rules.time_to_eat * 1000);
	*last_meal = *(info->current_time);
	if (pthread_mutex_unlock(&info->fork[info->own_fork]))
		return (1);
	if (pthread_mutex_unlock(&info->fork[info->side_fork]))
		return (1);
	return (0);
}

int	ft_get_fork(t_philo_info *info, time_t last_meal)
{
	bool	own_mine;
	bool	side_mine;

	own_mine = false;
	side_mine = false;
	while (1)
	{
		if (!pthread_mutex_lock(&info->fork[info->own_fork]))
		{

			printf("%ld %ld has taken a fork\n", *(info->current_time), info->philo_id);
			own_mine = true;
		}
		if (!pthread_mutex_lock(&info->fork[info->side_fork]))
		{
			printf("%ld %ld has taken a fork\n", *(info->current_time), info->philo_id);
			side_mine = true;
		}
		if (own_mine && side_mine)
			return (0);
		usleep(500);
		if (ft_calculate_dead(info, last_meal))
			return (1);
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
	while (1)
		if (*(info->ready) == 0)
			break;
	last_meal = *(info->current_time);
	if (info->philo_id % 2 == 0)
		usleep(50);
	while (*(info->philo_has_eaten))
	{
		if (ft_get_fork(info, last_meal))//coger tenedores + no muere
			return (NULL);
		if (ft_eat(info, &last_meal)) // comer + soltar tenedores + restart philo_has_eatene si come
			return (NULL);
		//printf("l_m %ld\n", last_meal);
		if (ft_sleep(info, last_meal))//dormir + pensar + no muere
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
		info[i].own_fork = i;
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
