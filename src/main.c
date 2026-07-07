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

void	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philos)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals_eaten = 0;
		table->philos[i].max_meals = table->nb_meals;
		table->philos[i].time_to_eat = table->time_to_eat;
		table->philos[i].time_to_sleep = table->time_to_sleep;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		i++;
	}
}

void	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->forks)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->nb_meals_eaten < philo->max_meals || philo->max_meals == 0)
	{
		philo_eat(philo);
		philo_think(philo);
		philo_sleep(philo);
	}
	custom_print_timestamp(philo, MSG_FINISHED);
	return (NULL);
}

int	create_philo_threads(t_table *table)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	if (table->nb_philo == 1)
	{
		one_philo(table);
		return (0);
	}
	threads = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!threads)
		return (1);
	while (i < table->nb_philo)
	{
		if (pthread_create(&threads[i], NULL, philo_routine,
				&table->philos[i]) != 0)
		{
			free(threads);
			return (1);
		}
		i++;
	}
	join_threads(threads, table->nb_philo);
	free(threads);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		printf(RED "Error\nargs nb" RESET);
		return (1);
	}
	start_time();
	init_args(&table, argv, argc);
	init_forks(&table);
	init_philos(&table);
	if (validate_args(&table) != 0)
	{
		printf(RED "Error\ninvalid args" RESET);
		return (1);
	}
	if (create_philo_threads(&table) != 0)
	{
		printf(RED "Error\nthread creation" RESET);
		return (1);
	}
	return (0);
}
