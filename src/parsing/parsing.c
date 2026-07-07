/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_atoi(const char *str, int *err)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	*err = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (*err = 1, 0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (*err = 1, 0);
		nb = nb * 10 + (str[i] - '0');
		if (nb > INT_MAX)
			return (*err = 1, 0);
		i++;
	}
	return ((int)nb);
}

int	validate_args(int argc, char *argv[])
{
	int	i;
	int	err;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i], &err) < 1 || err)
			return (-1);
		i++;
	}
	return (0);
}
