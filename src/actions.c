/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
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
		print_status(philo, MSG_TAKEN_FORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, MSG_TAKEN_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, MSG_TAKEN_FORK);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, MSG_TAKEN_FORK);
	}
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	print_status(philo, MSG_THINK);
	think_time = philo->table->time_to_die - philo->table->time_to_eat
		- philo->table->time_to_sleep;
	if (think_time < 0)
		think_time = 0;
	ft_usleep(think_time / 2, philo->table);
}

void	philo_eat(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, MSG_EAT);
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->nb_meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	put_down_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, MSG_SLEEP);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}
