/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:57 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/20 22:05:20 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_set_check_time(t_time_info *info)
{
	pthread_mutex_lock(&info->control->current_time);
	info->current_time = ft_set_time(info->start_time);
	pthread_mutex_unlock(&info->control->current_time);
	return (1);
}

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

int	ft_have_eaten(t_philo_info *info)
{
	pthread_mutex_lock(&info->control->have_eaten);
	if (*(info->philo_have_eaten) == 0)
	{
		pthread_mutex_unlock(&info->control->have_eaten);
		return (1);
	}
	pthread_mutex_unlock(&info->control->have_eaten);
	return (0);
}


void	*ft_philo_routine(void	*p)
{
	t_philo_info	*info;

	info = (t_philo_info *)p;
	ft_ready(info);
	while (ft_check_time_ready(info))
		usleep(250);
	if (info->philo_id % 2)
		usleep(50000);
	info->time.last_meal = 0;
	while (!ft_dead(info))
	{
		if (ft_take_fork(info))
			return (ft_unlock_fork(info));
		if (ft_eat(info))
			return (ft_unlock_fork(info));
		if (ft_have_eaten(info))
		{
			return (ft_unlock_fork(info));
		}
		if (ft_sleep(info))
			return (ft_unlock_fork(info));
	}
	return (NULL);
}
