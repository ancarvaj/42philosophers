/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:57 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/14 21:09:38 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_time_ready(t_philo_info *info)
{
	pthread_mutex_lock(&info->control->time_ready);
	if (*(info->time_ready))
	{

		pthread_mutex_unlock(&info->control->time_ready);
		return (1);
	}
	pthread_mutex_unlock(&info->control->time_ready);
	return (0);
}

void	ft_ready(t_philo_info *info)
{
	pthread_mutex_lock(&info->control->time_ready);
	*(info->time_ready) = *(info->time_ready) - 1;
	pthread_mutex_unlock(&info->control->time_ready);
}

int	ft_dead(t_philo_info *info)
{
	pthread_mutex_lock(&info->control->dead);
	if (*(info->dead))
	{

		pthread_mutex_unlock(&info->control->dead);
		return (1);
	}
	pthread_mutex_unlock(&info->control->dead);
	return (0);
}

int	ft_have_eaten(t_philo_info *info)
{
	pthread_mutex_lock(&info->control->have_eaten);
	if (!*(info->philo_have_eaten))
	{
		pthread_mutex_unlock(&info->control->have_eaten);
		return (1);
	}
	pthread_mutex_unlock(&info->control->have_eaten);
	return (0);
}

int	ft_check_fork(t_philo_info *info)
{
	ft_set_time(&info->time);
	pthread_mutex_lock(&info->fork);
	if (info->fork_took)
	{
		pthread_mutex_unlock(&info->fork);
		return (1);
	}
	pthread_mutex_unlock(&info->fork);
	return (0);
}

int	ft_check_n_fork(t_philo_info *info)
{
	ft_set_time(&info->time);
	pthread_mutex_lock(info->n_fork);
	if (*(info->n_fork_took))
	{
		pthread_mutex_unlock(info->n_fork);
		return (1);
	}
	pthread_mutex_unlock(info->n_fork);
	return (0);
}

void	ft_set_dead(t_philo_info *info)
{
	ft_set_time(&info->time);
	pthread_mutex_lock(&info->control->dead);
	*(info->dead) = 1;
	pthread_mutex_unlock(&info->control->dead);

}

int	ft_check_dead(t_philo_info *info, time_t last_meal)
{
	if (ft_dead(info))
		return (1);
	if (info->time.current_time - 5 - last_meal > (time_t)info->rules.time_to_die)
	{
		ft_set_dead(info);
		//ft_set_time(&info->time);
		printf("%ld %ld died\n", info->time.current_time, info->philo_id);
		return (1);
	}
	return (0);
}

int	ft_wait_fork(t_philo_info *info, time_t last_meal)
{
	while (ft_check_fork(info))
	{
		usleep(1000);
		if (ft_check_dead(info, last_meal))
			return (1);
	}
	pthread_mutex_lock(&info->fork);
	info->fork_took = 1;
	pthread_mutex_unlock(&info->fork);
	printf("%ld %ld has taken a fork\n", info->time.current_time, info->philo_id);
	return (0);
}

int	ft_wait_n_fork(t_philo_info *info, time_t last_meal)
{
	while (ft_check_n_fork(info))
	{
		usleep(1000);
		if (ft_check_dead(info, last_meal))
			return (1);
	}
	pthread_mutex_lock(info->n_fork);
	*(info->n_fork_took) = 1;
	pthread_mutex_unlock(info->n_fork);
	printf("%ld %ld has taken a fork\n", info->time.current_time, info->philo_id);
	return (0);
}

int	ft_take_fork(t_philo_info *info, time_t last_meal)
{
	if (ft_wait_fork(info, last_meal))
		return (1);
	if (ft_wait_n_fork(info, last_meal))
		return (1);
	return (0);
}

void	*ft_unlock_fork(t_philo_info *info)
{

	ft_set_time(&info->time);
	pthread_mutex_lock(&info->fork);
	info->fork_took = 0;
	pthread_mutex_unlock(&info->fork);
	pthread_mutex_lock(info->n_fork);
	*(info->n_fork_took) = 0;
	pthread_mutex_unlock(info->n_fork);
	return (NULL);
}

int	ft_eat(t_philo_info *info, time_t *last_meal)
{
	size_t	eat_time;


	if (ft_dead(info))
		return (1);
	ft_set_time(&info->time);
	printf("%ld %ld is eating\n", info->time.current_time, info->philo_id);
	eat_time = 0;
	*(last_meal) = info->time.current_time;
	while (eat_time <= info->rules.time_to_eat)
	{
		usleep(5000 * 0.92);
		eat_time = eat_time + 5;
	}
	info->rules.n_times_must_eat = info->rules.n_times_must_eat - 1;
	if (info->rules.n_times_must_eat == 0)
		return (1);
	ft_unlock_fork(info);	
	return (0);
}

int	ft_sleep(t_philo_info *info, time_t last_meal)
{
	size_t slept_time;

	if (ft_dead(info))
		return (1);
	ft_set_time(&info->time);
	printf("%ld %ld is sleeping\n", info->time.current_time, info->philo_id);
	slept_time = 0;
	while (slept_time <= info->rules.time_to_sleep)
	{
		ft_set_time(&info->time);
		usleep(5000 * 0.92);
		if (ft_check_dead(info, last_meal))
			return (1);
		slept_time = slept_time + 5;
	}
	if (ft_check_dead(info, last_meal))
		return (1);
	ft_set_time(&info->time);
	printf("%ld %ld is thinking\n", info->time.current_time, info->philo_id);
	return (0);
}

void	*ft_philo_routine(void	*p)
{
	t_philo_info	*info;
	time_t		last_meal;

	info = (t_philo_info *)p;
	ft_ready(info);
	while (ft_check_time_ready(info))
		usleep(250);
	info->time.start_time = ft_get_time();
	last_meal = 0;
	ft_set_time(&info->time);
	if (info->philo_id % 2)
		usleep(60000);
	while (!ft_dead(info))
	{
		if (ft_take_fork(info, last_meal))
			return (ft_unlock_fork(info));
		if (ft_eat(info, &last_meal))
			return (ft_unlock_fork(info));
		if (ft_have_eaten(info))
			return (NULL);
		if (ft_sleep(info, last_meal))
			return (NULL);
	}
	return (NULL);
}
