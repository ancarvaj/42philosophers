/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:57 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:43:18 by ancarvaj         ###   ########.fr       */
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

void	*ft_philo_routine(void	*p)
{
	t_philo_info	*info;
	time_t			last_meal;

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
