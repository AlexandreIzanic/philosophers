/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	init_args(t_table *table, char *argv[], int argc)
{
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->nb_meals = ft_atoi(argv[5]);
	else
		table->nb_meals = 0;
}

void	one_philo(t_table *table)
{
	t_philo	*philo;

	philo = &table->philos[0];
	custom_print_timestamp(philo, MSG_TAKEN_FORK);
	ft_usleep(table->time_to_die, table);
	print_death(philo);
}

int	validate_args(t_table *table)
{
	if (table->nb_philo <= 0 || table->time_to_die <= 0
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (-1);
	return (0);
}

int	join_threads(pthread_t *threads, int nb_philo)
{
	int	i;

	i = nb_philo;
	while (i--)
		pthread_join(threads[i], NULL);
	return (0);
}

int	ft_atoi(const char *str)
{
	long			result;
	int				sign;
	const char		*p;

	result = 0;
	sign = 1;
	p = str;
	while (*p == ' ' || (*p >= '\t' && *p <= '\r'))
		p++;
	if (*p == '+' || *p == '-')
	{
		if (*p == '-')
			sign = -1;
		p++;
	}
	while (*p >= '0' && *p <= '9')
	{
		result = result * 10 + (*p - '0');
		if (sign == 1 && result > INT_MAX)
			return (INT_MAX);
		if (sign == -1 && result > (long)INT_MAX + 1)
			return (INT_MIN);
		p++;
	}
	return ((int)(sign * result));
}
