/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:41:03 by jebitrus          #+#    #+#             */
/*   Updated: 2024/07/16 23:41:10 by jebitrus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	clean_allocs(t_env *env, int l, int ret)
{
	free (env->ph);
	env->ph = NULL;
	if (l == 2)
		return (ret);
	free (env->forks);
	env->forks = NULL;
	if (l == 3)
		return (ret);
	free (env->mtx_forks);
	env->mtx_forks = NULL;
	if (l == 4)
		return (ret);
	free (env->status);
	env->status = NULL;
	return (ret);
}

int	allocate_memory(t_env *env)
{
	env->ph = malloc (sizeof(t_philo) * env->ph_num);
	if (!env->ph)
		return (1);
	memset(env->ph, '\0', env->ph_num * sizeof(t_philo));
	env->forks = malloc (sizeof(int) * env->ph_num);
	if (!env->forks)
		return (clean_allocs(env, 2, 2));
	memset(env->forks, '0', env->ph_num * sizeof(int));
	env->mtx_forks = malloc (sizeof(pthread_mutex_t) * env->ph_num);
	if (!env->mtx_forks)
		return (clean_allocs(env, 3, 3));
	env->status = malloc(sizeof(int) * env->ph_num);
	if (!env->status)
		return (clean_allocs(env, 4, 4));
	memset(env->status, '\0', env->ph_num * sizeof(int));
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (argc != 5 && argc != 6)
	{
		print_error("Usage(ms): #philo die eat sleep [eat_count]");
		return (5);
	}
	if (bad_input(argv))
		return (1);
	setup_env(&env, argc, argv);
	if (allocate_memory(&env) != 0)
	{
		print_error("malloc failed.");
		return (2);
	}
	init_struct(&env);
	if (init_mtx(&env) != 0)
		return (clean_allocs(&env, 0, 3));
	if (init_dining(&env) != 0)
		return (clean_allocs(&env, 0, 4));
	clean_allocs(&env, 0, 0);
	return (0);
}
