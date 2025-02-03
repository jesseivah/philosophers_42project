/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:40:17 by jebitrus          #+#    #+#             */
/*   Updated: 2024/07/16 23:40:23 by jebitrus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

long	ft_atol(const char *nptr)
{
	int		i;
	long	n;
	int		sign;

	i = 0;
	sign = 1;
	n = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i ++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + (nptr[i] - 48);
		i ++;
	}
	return (sign * n);
}

static int	not_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i ++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i ++;
	}
	return (0);
}

int	not_in_range(char *str, int i)
{
	long	ret;

	ret = ft_atol(str);
	if (ret <= 0 || ret > INT_MAX)
	{
		print_error("Philos and times should be > 0 < INT_MAX");
		return (1);
	}
	else if (i == 1 && ret > PHILO_MAX)
	{
		print_error("Maximum number of 200 Philosophers.");
		return (3);
	}
	else
		return (0);
}

int	bad_input(char **argv)
{
	int	i;
	int	val;

	i = 1;
	val = 0;
	while (argv[i])
	{
		if (not_int(argv[i]))
		{
			print_error("Values should be positive integers.");
			return (1);
		}
		val = not_in_range(argv[i], i);
		if (val > 0)
			return (1);
		i ++;
	}
	return (0);
}
