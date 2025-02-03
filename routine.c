/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:44:08 by jebitrus          #+#    #+#             */
/*   Updated: 2024/07/16 23:44:14 by jebitrus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	philo_sleep(t_philo *philo)
{
	print(philo, "is sleeping");
	custom_sleep(philo->sleep_len);
}

void	philo_think(t_philo *philo)
{
	print(philo, "is thinking");
}

void	optional_counter(t_philo *philo)
{
	if (philo->eat_count > -1)
		philo->eat_count --;
	if (philo->eat_count == 0)
	{
		pthread_mutex_lock(philo->mtx_eat_philos);
		*philo->eat_philo_count -= 1;
		pthread_mutex_unlock(philo->mtx_eat_philos);
	}
}

void	check_ready(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->mtx_ready);
		if (*philo->ready == 1)
		{
			pthread_mutex_unlock(philo->mtx_ready);
			return ;
		}
		pthread_mutex_unlock(philo->mtx_ready);
		usleep (100);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	check_ready(philo);
	philo_think(philo);
	if (philo->ph_num == 1)
	{
		routine_for_one (philo);
		return ((void *)0);
	}
	if (philo->id % 2 == 0)
		usleep (100);
	while (is_alive(philo))
	{
		philo_eat(philo);
		optional_counter(philo);
		philo_sleep(philo);
		philo_think(philo);
		custom_sleep(1);
	}
	return ((void *)0);
}
