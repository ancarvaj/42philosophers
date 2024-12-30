/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:49:59 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/30 14:58:24 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_ready_time(t_time_info *info)
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

int	ft_have_eaten_time(t_time_info *info)
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

int	ft_dead_time(t_time_info *info)
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

void	*time_routine(void *p)
{
	t_time_info	*info;

	info = p;
	while (ft_check_ready_time(info))
	{
		usleep(250);
	}
	info->start_time = ft_get_time();
	ft_set_check_time(info);
	while (!ft_dead_time(info) && !ft_have_eaten_time(info))
	{
		ft_set_check_time(info);
		usleep(50);
	}
	return (NULL);
}

void	ft_init_time_info(t_time_info *time, t_simulation *sim)
{
	time->control = &sim->control;
	time->dead = &sim->dead;
	time->philo_have_eaten = &sim->philo_have_eaten;
	time->time_ready = &sim->time_ready;
}
