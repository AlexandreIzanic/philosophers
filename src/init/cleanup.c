/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	join_threads(pthread_t *threads, int nb_philo)
{
	int	i;

	i = nb_philo;
	while (i--)
		pthread_join(threads[i], NULL);
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		if (table->philos)
			pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->stop_flag_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}
