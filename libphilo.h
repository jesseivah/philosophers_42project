/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jebitrus <jebitrus@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 23:40:48 by jebitrus          #+#    #+#             */
/*   Updated: 2024/07/16 23:40:53 by jebitrus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# define PHILO_MAX 200
# define INT_MAX 2147483647

typedef struct s_philo
{
	pthread_t			thread;
	int					ph_num;
	int					id;
	int					eat_len;
	int					sleep_len;
	int					life_len;
	int					eat_count;
	long long			start_time;
	long long			last_eat_time;
	int					*ready;
	int					*status;
	int					*eat_philo_count;
	int					*ptr_lfork;
	int					*ptr_rfork;
	pthread_mutex_t		*ptr_mtx_lfork;
	pthread_mutex_t		*ptr_mtx_rfork;
	pthread_mutex_t		*mtx_print;
	pthread_mutex_t		*mtx_eat_philos;
	pthread_mutex_t		mtx_status;
	pthread_mutex_t		mtx_last_eat;
	pthread_mutex_t		*mtx_ready;
}	t_philo;

typedef struct s_env
{
	int					ph_num;
	int					eat_len;
	int					sleep_len;
	int					life_len;
	int					eat_count;
	int					eat_philo_count;
	int					dead;
	int					ready;
	int					*forks;
	int					*status;
	t_philo				*ph;
	pthread_mutex_t		*mtx_forks;
	pthread_mutex_t		mtx_ready;
	pthread_mutex_t		mtx_eat_philos;
	pthread_mutex_t		mtx_print;
	pthread_mutex_t		mtx_dead;
	pthread_t			monitor;
}	t_env;

/* main.c */
int			clean_allocs(t_env *env, int l, int ret);

/* input_check.c */

int			bad_input(char **argv);
long		ft_atol(const char *nptr);

/* init_struct.c */

void		setup_env(t_env *env, int argc, char **argv);
void		init_struct(t_env *env);

/* init_dining.c */

int			init_dining(t_env *env);
void		*routine(void *arg);
void		print(t_philo *philo, char *msg);
void		return_fork(t_philo *philo, char d);

/* mtx_actions.c */

int			init_mtx(t_env *env);
int			destroy_all(t_env *env, int type);

/* monitor.c */

void		*checker(void *arg);

/* print_error.c */

void		print_error(char *str);

/* utils.c */

long long	get_milli_time(void);
int			custom_sleep(long long millilen);
int			is_alive(t_philo *philo);
void		print(t_philo *philo, char *msg);

/* eat_routine.c */

void		philo_eat(t_philo *philo);
int			routine_for_one(t_philo *philo);

/* routine.c */

void		*routine(void *arg);

/* debug.c */

void		print_forks(t_env *env);
void		print_status(t_env *env);

#endif
