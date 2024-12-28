/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:37 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/20 21:13:16 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_fork(int i, t_philo_info *info, size_t nb_of_philos)
{
	pthread_mutex_init(&info[i].fork, NULL);
	info[i].fork_took = 0;
	if (info[i].philo_id == nb_of_philos)
	{
		info[i].n_fork = &info[0].fork;
		info[i].n_fork_took = &info[0].fork_took;
	}
	else
	{
		info[i].n_fork = &info[i + 1].fork;
		info[i].n_fork_took = &info[i + 1].fork_took;
	}
}

int	ft_print_message(t_philo_info *info, const char *message)
{
	if (ft_check_dead(info))
		return (1);
	pthread_mutex_lock(&info->control->dead);
	pthread_mutex_lock(&info->control->current_time);
	if (*(info->dead))
	{
		pthread_mutex_unlock(&info->control->current_time);
		pthread_mutex_unlock(&info->control->dead);
		return (1);
	}
	printf("%ld %ld %s\n", *(info->time.current_time), info->philo_id, message);
	pthread_mutex_unlock(&info->control->current_time);
	pthread_mutex_unlock(&info->control->dead);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	ft_atoi(const char *s)
{
	int			i;
	long int	n;

	if (ft_strlen(s) > 11)
		return (-1);
	i = -1;
	n = 0;
	while (s[++i])
		n = (n * 10) + (s[i] - '0');
	if (n > INT_MAX)
		return (-999);
	if (n == 0)
		return (-666);
	return (n);
}
