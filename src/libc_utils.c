/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:22:37 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/16 10:41:08 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
