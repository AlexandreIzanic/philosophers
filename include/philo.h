/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[31m"
# define RESET "\033[0m"

/* message macros */
# define MSG_THINK "is thinking"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_TAKEN_FORK "has taken a fork"
# define MSG_DIED "died"

# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal_time;
	pthread_mutex_t	meal_mutex;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				nb_meals;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				stop_flag;
	pthread_mutex_t	stop_flag_mutex;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_table;

/* parsing.c */
int				ft_atoi(const char *str);
int				validate_args(int argc, char *argv[]);

/* init.c */
void			init_args(t_table *table, char *argv[], int argc);
int				init_table(t_table *table);
int				init_philos(t_table *table);

/* cleanup.c */
void			cleanup(t_table *table);
void			join_threads(pthread_t *threads, int nb_philo);

/* simulation.c */
void			*philo_routine(void *arg);
int				run_simulation(t_table *table);
void			handle_single_philo(t_table *table);

/* actions.c */
void			pick_up_forks(t_philo *philo);
void			put_down_forks(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);

/* monitor.c */
void			*monitor_routine(void *arg);

/* time.c */
long			get_time_ms(void);
void			ft_usleep(long ms, t_table *table);

/* state.c */
int				is_stopped(t_table *table);
void			set_stop(t_table *table);

/* print.c */
void			print_status(t_philo *philo, const char *message);
void			print_death(t_philo *philo);

#endif
