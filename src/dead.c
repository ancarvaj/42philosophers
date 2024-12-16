/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:26:03 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:47:39 by ancarvaj         ###   ########.fr       */
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
	ft_set_time(&info->time);
	pthread_mutex_lock(&info->control->dead);
	*(info->dead) = 1;
	pthread_mutex_unlock(&info->control->dead);
}

int	ft_check_dead(t_philo_info *info, time_t last_meal)
{
	if (ft_dead(info))
		return (1);
	if (info->time.current_time - 5 - last_meal
		> (time_t)info->rules.time_to_die)
	{
		ft_set_dead(info);
		printf("%ld %ld died\n", info->time.current_time, info->philo_id);
		return (1);
	}
	return (0);
}
