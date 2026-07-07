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

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}

int	is_stopped(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->stop_mutex);
	value = table->stop;
	pthread_mutex_unlock(&table->stop_mutex);
	return (value);
}

void	set_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	ft_usleep(long ms, t_table *table)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		if (is_stopped(table))
			break ;
		usleep(200);
	}
}

void	custom_print_timestamp(t_philo *philo, const char *message)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (!is_stopped(table))
		printf("%ld Philosopher %d %s\n",
			get_time_ms() - table->start_time, philo->id, message);
	pthread_mutex_unlock(&table->print_mutex);
}
