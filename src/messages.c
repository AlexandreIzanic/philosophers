/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	custom_print_timestamp(philo, MSG_TAKEN_FORK);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	custom_print_timestamp(philo, MSG_THINK);
	usleep(1000);
}

void	philo_eat(t_philo *philo)
{
	int	ms;

	ms = philo->time_to_eat * 1000;
	pick_up_forks(philo);
	custom_print_timestamp(philo, MSG_EAT);
	usleep(ms);
	philo->nb_meals_eaten++;
	put_down_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	custom_print_timestamp(philo, MSG_SLEEP);
	usleep(philo->time_to_sleep * 1000);
}
