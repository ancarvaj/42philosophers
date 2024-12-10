/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:23:04 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/10 16:11:29 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ft_stoms(time_t sec)
{
	return (sec * 1000);
}

time_t	ft_ustoms(suseconds_t usec)
{
	return (usec / 1000);
}

time_t	ft_timevaltoms(struct timeval tv)
{
	return (ft_stoms(tv.tv_sec) + ft_ustoms(tv.tv_usec));
}

time_t	ft_get_time(time_t start_time, time_t current_time)
{
	return (current_time - start_time);
}

void	*ft_time_routine(void *p)
{
	t_time	*time = p;
	struct timeval tv;

	while (1)
	{
		usleep(100);
		if (*(time->ready) == 0)
			break;
	}
	if (gettimeofday(&tv, NULL))
		return (NULL);
	time->start_time = ft_timevaltoms(tv);
	while (*(time->dead) == false)
	{
		if (*(time->philo_has_eaten) <= 0)
		{
			return (NULL);
		}
		if (gettimeofday(&tv, NULL))
			return (NULL);
		time->current_time = ft_get_time(time->start_time, ft_timevaltoms(tv));
	}
	return (NULL);
}	

