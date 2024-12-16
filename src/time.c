/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:23:04 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/14 18:36:44 by ancarvaj         ###   ########.fr       */
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

time_t	ft_current_time(time_t start_time, time_t current_time)
{
	return (current_time - start_time);
}

time_t	ft_get_time()
{
	struct timeval tv;
	time_t	time;
	gettimeofday(&tv, NULL);
	time = ft_timevaltoms(tv);
	return (time);
}

void	ft_set_time(t_time *time)
{
	time->current_time = ft_current_time(time->start_time, ft_get_time());
}
