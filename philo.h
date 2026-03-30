/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#             */
/*   Updated: 2026/03/29 00:00:00 by user              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[31m" 
# define GREEN "\033[32m" 
# define RESET "\033[0m" 
# define ORANGE "\033[33m"
# define PURPLE "\033[35m"

#include <stdio.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
    int             id;
    int             nb_meals_eaten;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    int             time_to_eat;
    int             time_to_sleep;
}   t_philo;

typedef struct s_table
{
    int     nb_philo;
    int     time_to_die;
    int     nb_meals;

    int    time_to_eat;
    int    time_to_sleep;
    t_philo *philos;
    pthread_mutex_t *forks;
}   t_table;

int ft_atoi(const char *str);
void init_args(t_table *table, char *argv[], int argc);

// messages
void    one_philo(t_table *table);
void    pick_up_forks(t_philo *philo);
void    put_down_forks(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void philo_think(t_philo *philo);
void msg_fork(t_philo *philo);
void msg_die(t_philo *philo);
int validate_args(t_table *table);
#endif /* PHILO_H */
