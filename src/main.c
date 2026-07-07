/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	print_error(const char *msg)
{
	printf(RED "Error\n%s\n" RESET, msg);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (print_error("args nb"));
	if (validate_args(argc, argv) != 0)
		return (print_error("invalid args"));
	init_args(&table, argv, argc);
	if (init_table(&table) != 0)
		return (print_error("init"));
	if (init_philos(&table) != 0)
	{
		cleanup(&table);
		return (print_error("init"));
	}
	if (run_simulation(&table) != 0)
	{
		cleanup(&table);
		return (print_error("thread creation"));
	}
	cleanup(&table);
	return (0);
}
