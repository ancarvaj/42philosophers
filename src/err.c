/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:10 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:39:39 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_message_error(const char *custom,
		const char *err, unsigned int status)
{
	if (custom)
	{
		write(STDERR_FILENO, "\n[ ", 3);
		write(STDERR_FILENO, custom, ft_strlen(custom));
		write(STDERR_FILENO, " ]", 2);
	}
	if (err)
		write(STDERR_FILENO, err, ft_strlen(err));
	return (status & 0xff);
}

int	ft_check_args(const char **av)
{
	int	i;
	int	j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		if (av[i][0] == '-' || av[i][0] == '+')
			return (ft_message_error(av[i], NEGATIVE, 1));
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (ft_message_error(av[i], NOT_NUMBER, 1));
		}
		if (ft_atoi(av[i]) < 1)
			return (ft_message_error(av[i], ZERO_LARGE, 1));
	}
	return (0);
}
