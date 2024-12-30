/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:26:03 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/30 14:56:03 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	ft_set_dead(t_philo_info *info)
{
	pthread_mutex_lock(&info->control->dead);
	*(info->dead) = 1;
	pthread_mutex_unlock(&info->control->dead);
}

int	ft_check_dead(t_philo_info *info)
{
	if (ft_dead(info))
		return (1);
	pthread_mutex_lock(&info->control->current_time);
	if (*(info->time.current_time) - info->time.last_meal
		> (time_t)info->rules.time_to_die)
	{
		pthread_mutex_unlock(&info->control->current_time);
		pthread_mutex_lock(&info->control->dead);
		if (*(info->dead))
		{
			pthread_mutex_unlock(&info->control->dead);
			return (1);
		}
		*(info->dead) = 1;
		pthread_mutex_lock(&info->control->current_time);
		printf("%ld %ld %s\n", *(info->time.current_time),
			info->philo_id, "died");
		pthread_mutex_unlock(&info->control->current_time);
		pthread_mutex_unlock(&info->control->dead);
		return (1);
	}
	pthread_mutex_unlock(&info->control->current_time);
	return (0);
}
