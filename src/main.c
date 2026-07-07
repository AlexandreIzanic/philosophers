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
		table->philos[i].last_meal_time = table->start_time;
		table->philos[i].table = table;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % table->nb_philo];
		pthread_mutex_init(&table->philos[i].meal_mutex, NULL);
		i++;
	}
}

void	init_table(t_table *table)
{
	int	i;

	table->stop = 0;
	table->start_time = get_time_ms();
	pthread_mutex_init(&table->stop_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
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

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->stop_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}

static int	philo_is_full(t_philo *philo)
{
	int	full;

	if (philo->max_meals <= 0)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	full = (philo->nb_meals_eaten >= philo->max_meals);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (full);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat / 2 + 1, philo->table);
	while (!is_stopped(philo->table))
	{
		if (philo_is_full(philo))
			break ;
		philo_eat(philo);
		if (is_stopped(philo->table))
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

int	create_philo_threads(t_table *table)
{
	int			i;
	pthread_t	*threads;
	pthread_t	monitor;

	if (table->nb_philo == 1)
		return (one_philo(table), 0);
	threads = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!threads)
		return (1);
	i = -1;
	while (++i < table->nb_philo)
		if (pthread_create(&threads[i], NULL, philo_routine,
				&table->philos[i]) != 0)
			return (free(threads), 1);
	if (pthread_create(&monitor, NULL, monitor_routine, table) != 0)
		return (free(threads), 1);
	join_threads(threads, table->nb_philo);
	pthread_join(monitor, NULL);
	free(threads);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (printf(RED "Error\nargs nb" RESET), 1);
	init_args(&table, argv, argc);
	if (validate_args(&table) != 0)
		return (printf(RED "Error\ninvalid args" RESET), 1);
	init_table(&table);
	init_philos(&table);
	if (create_philo_threads(&table) != 0)
		return (printf(RED "Error\nthread creation" RESET), cleanup(&table), 1);
	cleanup(&table);
	return (0);
}
