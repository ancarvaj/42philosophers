/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:18:11 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/20 21:12:33 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_fork(t_philo_info *info)
{
	if (ft_wait_fork(info))
		return (1);
	if (ft_wait_n_fork(info))
		return (1);
	return (0);
}

int	get_ms(time_t time_should_be,t_philo_info *info)
{
	time_t	current_time;

	pthread_mutex_lock(&info->control->current_time);
	current_time = *(info->time.current_time);
	pthread_mutex_unlock(&info->control->current_time);
	while (current_time <= time_should_be)
	{
		usleep(100);
		if (ft_dead(info))
			return (1);
		pthread_mutex_lock(&info->control->current_time);
		current_time = *(info->time.current_time);
		pthread_mutex_unlock(&info->control->current_time);
		
	}
	if (ft_check_dead(info))
		return (1);
	return (0);
}

int	ft_eat(t_philo_info *info)
{
	size_t	eat_time;
	time_t	last_time;

	pthread_mutex_lock(&info->control->current_time);
	info->time.last_meal = *(info->time.current_time);//mutex
	pthread_mutex_unlock(&info->control->current_time);
	if (ft_print_message(info, "is eating"))
		return (1);
	last_time = info->time.last_meal;
	eat_time = 0;
	while (eat_time <= info->rules.time_to_eat)
	{
		last_time += 1;
		if (get_ms(last_time ,info))
			return (1);
		//usleep(1000);
		//if (ft_dead(info))
		//	return (1);
		eat_time += 1;
	}
	ft_unlock_fork(info);
	info->rules.n_times_must_eat = info->rules.n_times_must_eat - 1;
	if (info->rules.n_times_must_eat == 0)
	{
		*(info->philo_have_eaten) = *(info->philo_have_eaten) - 1;
		return (1);
	}
	return (0);
}

int	ft_sleep(t_philo_info *info)
{
	size_t	slept_time;
	time_t	last_time;

	pthread_mutex_lock(&info->control->current_time);
	last_time = *(info->time.current_time);
	pthread_mutex_unlock(&info->control->current_time);
	if (ft_print_message(info, "is sleeping"))
		return (1);
	slept_time = 0;
	while (slept_time <= info->rules.time_to_sleep)
	{
		last_time += 1;
		if (get_ms(last_time ,info))
			return (1);
		//usleep(1000);
		//if (ft_check_dead(info))
		//	return (1);
		slept_time += 1;
	}
	if (ft_print_message(info, "is thinking"))
		return (1);
	return (0);
}
