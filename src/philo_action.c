/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:18:11 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:50:05 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_take_fork(t_philo_info *info, time_t last_meal)
{
	if (ft_wait_fork(info, last_meal))
		return (1);
	if (ft_wait_n_fork(info, last_meal))
		return (1);
	return (0);
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
		usleep(5000 * 0.95);
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
	size_t	slept_time;

	if (ft_dead(info))
		return (1);
	ft_set_time(&info->time);
	printf("%ld %ld is sleeping\n", info->time.current_time, info->philo_id);
	slept_time = 0;
	while (slept_time <= info->rules.time_to_sleep)
	{
		ft_set_time(&info->time);
		usleep(5000 * 0.95);
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
