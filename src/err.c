/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:10 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/10 14:22:20 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_message_error(const char *err, unsigned int exit_status)
{
	write(STDERR_FILENO, err, ft_strlen(err));
	return (exit_status & 0xff);
}

int	ft_check_args(char **av)
{
	int	i;
	int	j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		if (av[i][0] == '+' || av[i][0] == '-')
			return (2);//error_message before return 
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		}
	}
	return (0);
}
