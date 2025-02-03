/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:43:48 by jebitrus          #+#    #+#             */
/*   Updated: 2024/07/16 23:43:53 by jebitrus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len ++;
	return (len);
}

void	print_error(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 0)
	{
		write (2, str, len);
		write (2, "\n", 1);
	}
	else
		write (2, "Error\n", 6);
}
