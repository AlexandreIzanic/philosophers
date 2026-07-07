/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	is_stopped(t_table *table)
{
	int	value;

	pthread_mutex_lock(&table->stop_flag_mutex);
	value = table->stop_flag;
	pthread_mutex_unlock(&table->stop_flag_mutex);
	return (value);
}

void	set_stop(t_table *table)
{
	pthread_mutex_lock(&table->stop_flag_mutex);
	table->stop_flag = 1;
	pthread_mutex_unlock(&table->stop_flag_mutex);
}
