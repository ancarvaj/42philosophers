/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:21:10 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:41:46 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_simulation	sim;

	if (ac != 5 && ac != 6)
		return (ft_message_error(NULL, INVALID_ARG, 1));
	if (ft_check_args((const char **)av + 1))
		return (1);
	if (ft_init_sim(&sim, av))
		return (1);
	return (0);
}
