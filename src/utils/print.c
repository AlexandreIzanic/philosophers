/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void	log_line(t_philo *philo, const char *message)
{
	printf("%ld %d %s\n",
		get_time_ms() - philo->table->start_time, philo->id, message);
}

void	print_status(t_philo *philo, const char *message)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (!is_stopped(table))
		log_line(philo, message);
	pthread_mutex_unlock(&table->print_mutex);
}


void	print_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (!is_stopped(table))
		log_line(philo, MSG_DIED);
	set_stop(table);
	pthread_mutex_unlock(&table->print_mutex);
}
