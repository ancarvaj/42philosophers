/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:05:02 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 13:11:36 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_rules(char **argv, t_rules *rules, size_t *nb_of_philos)
{
	*nb_of_philos = ft_atoi(argv[1]);
	if (*nb_of_philos > 200)
		return (ft_message_error(argv[1], PHILO_AMOUNT, 1));
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		rules->n_times_must_eat = ft_atoi(argv[5]);
		if (rules->n_times_must_eat == 0)
			return (1);
	}
	else
		rules->n_times_must_eat = -1;
	return (0);
}

int	ft_init_info(t_philo_info *info, size_t nb_of_philos, t_simulation *sim)
{
	size_t	i;

	i = -1;
	while (++i < nb_of_philos)
	{
		info[i].philo_id = i + 1;
		info[i].rules = sim->rules;
		info[i].philo_have_eaten = &sim->philo_have_eaten;
		info[i].dead = &sim->dead;
		info[i].time_ready = &sim->time_ready;
		pthread_mutex_init(&info[i].fork, NULL);
		info[i].control = &sim->control;
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
	return (0);
}

int	ft_init_philo(pthread_t *philo, t_philo_info *info, size_t nb_of_philo)
{
	size_t	i;

	i = 0;
	while (i < nb_of_philo)
	{
		pthread_create(&philo[i], NULL, ft_philo_routine, (void *)&info[i]);
		i++;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
	return (0);
}

void	ft_init_mutex(t_mutex_control *control)
{
	pthread_mutex_init(&control->time_ready, NULL);
	pthread_mutex_init(&control->dead, NULL);
	pthread_mutex_init(&control->have_eaten, NULL);
	pthread_mutex_init(&control->current_time, NULL);
}

int	ft_init_sim(t_simulation *sim, char **av)
{
	memset(sim->philo_thread, 0, sizeof(sim->philo_thread));
	memset(sim->info, 0, sizeof(sim->info));
	if (ft_init_rules(av, &sim->rules, &sim->nb_of_philos))
		return (1);
	sim->philo_have_eaten = sim->nb_of_philos;
	sim->dead = 0;
	sim->time_ready = sim->nb_of_philos;
	ft_init_mutex(&sim->control);
	if (ft_init_info(sim->info, sim->nb_of_philos, sim))
		return (1);
	if (ft_init_philo(sim->philo_thread, sim->info, sim->nb_of_philos))
		return (1);
	return (0);
}
