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

long	usec_to_ms(long microseconds);
long	sec_to_ms(long seconds);
long	get_timestamp(void);

struct timeval	start_time(void)
{
	static struct timeval	start;

	if (start.tv_sec == 0 && start.tv_usec == 0)
		gettimeofday(&start, NULL);
	return (start);
}

long	usec_to_ms(long microseconds)
{
	return (microseconds / 1000);
}

long	sec_to_ms(long seconds)
{
	return (seconds * 1000);
}

long	get_timestamp(void)
{
	struct timeval	start;
	struct timeval	curr;
	long			elapsed_ms;

	start = start_time();
	gettimeofday(&curr, NULL);
	elapsed_ms = sec_to_ms(curr.tv_sec - start.tv_sec)
		+ usec_to_ms(curr.tv_usec - start.tv_usec);
	return (elapsed_ms);
}

void	custom_print_timestamp(t_philo *philo, const char *message)
{
	long	timestamp;

	timestamp = get_timestamp();
	printf("%ld Philosopher %d %s\n", timestamp, philo->id, message);
}
