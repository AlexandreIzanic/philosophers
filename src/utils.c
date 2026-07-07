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

void	one_philo(t_table *table)
{
	t_philo	*philo;

	philo = &table->philos[0];
	custom_print_timestamp(philo, MSG_TAKEN_FORK);
	ft_usleep(table->time_to_die, table);
	print_death(philo);
}

/* Vrai si str est un entier positif valide (+ optionnel, <= INT_MAX). */
static int	is_positive_number(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		nb = nb * 10 + (str[i] - '0');
		if (nb > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_positive_number(argv[i]))
			return (-1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1
		|| ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
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
