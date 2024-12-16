/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:23:15 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:46:42 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	printf("%ld %ld has taken a fork\n",
		info->time.current_time, info->philo_id);
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
	printf("%ld %ld has taken a fork\n",
		info->time.current_time, info->philo_id);
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
