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
# define GREEN "\033[32m"
# define RESET "\033[0m"
# define ORANGE "\033[33m"
# define PURPLE "\033[35m"

/* message macros */
# define MSG_FINISHED "has finished eating"
# define MSG_THINK "is thinking"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_TAKEN_FORK "has taken a fork"
# define MSG_DIED "has died"

# include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				nb_meals_eaten;
	int				max_meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_dead;
	int				last_meal_time;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	int				time_to_die;
	int				nb_meals;
	int				time_to_eat;
	int				time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_table;

int				ft_atoi(const char *str);
void			init_args(t_table *table, char *argv[], int argc);
int				validate_args(t_table *table);
int				join_threads(pthread_t *threads, int nb_philo);
void			one_philo(t_table *table);
void			pick_up_forks(t_philo *philo);
void			put_down_forks(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
struct timeval	start_time(void);
void			custom_print_timestamp(t_philo *philo, const char *message);

#endif
