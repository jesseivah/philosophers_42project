/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:45:06 by jebitrus          #+#    #+#             */
/*   Updated: 2024/07/16 23:45:12 by jebitrus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

long long	get_milli_time(void)
{
	struct timeval	time;
	long long		militime;

	if (gettimeofday(&time, NULL) == -1)
	{
		print_error("gettimeofday() error.");
		return (0);
	}
	militime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (militime);
}

int	custom_sleep(long long millilen)
{
	long long	start;

	start = get_milli_time();
	while ((get_milli_time() - start) < millilen)
	{
		usleep(500);
	}
	return (0);
}

int	is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_status);
	if (*philo->status == 0)
	{
		pthread_mutex_unlock(&philo->mtx_status);
		return (1);
	}
	pthread_mutex_unlock(&philo->mtx_status);
	return (0);
}

void	print(t_philo *philo, char *msg)
{
	long long	currtime;

	currtime = 0;
	if (is_alive(philo))
	{
		currtime = get_milli_time();
		printf("%lld %d %s\n", currtime - philo->start_time, philo->id, msg);
	}
}
