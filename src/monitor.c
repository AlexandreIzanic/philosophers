/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@42.fr>                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by user               #+#    #+#            */
/*   Updated: 2026/07/07 10:53:52 by aizanic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/*
** Affiche la mort d'un philosophe puis lève le flag stop, le tout sous
** print_mutex pour qu'aucun autre thread ne puisse afficher après "has died".
*/
void	print_death(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&table->print_mutex);
	if (!is_stopped(table))
		printf("%ld %d %s\n",
			get_time_ms() - table->start_time, philo->id, MSG_DIED);
	pthread_mutex_lock(&table->stop_mutex);
	table->stop = 1;
	pthread_mutex_unlock(&table->stop_mutex);
	pthread_mutex_unlock(&table->print_mutex);
}

/* Un philosophe est mort s'il n'a pas mangé depuis plus de time_to_die ms. */
static int	philo_is_dead(t_table *table, int i)
{
	long	since_last_meal;
	int		full;

	pthread_mutex_lock(&table->philos[i].meal_mutex);
	since_last_meal = get_time_ms() - table->philos[i].last_meal_time;
	full = (table->nb_meals >= 0
			&& table->philos[i].nb_meals_eaten >= table->nb_meals);
	pthread_mutex_unlock(&table->philos[i].meal_mutex);
	if (full)
		return (0);
	return (since_last_meal > table->time_to_die);
}

/* Vrai si nb_meals est defini et que tous ont atteint leur quota. */
static int	all_ate_enough(t_table *table)
{
	int	i;
	int	full;

	if (table->nb_meals < 0)
		return (0);
	i = 0;
	full = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].nb_meals_eaten >= table->nb_meals)
			full++;
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (full == table->nb_philo);
}

/*
** Thread surveillant : boucle tant que la simulation tourne, verifie la mort
** de chaque philosophe et la fin par quota de repas, puis stoppe tout.
*/
void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!is_stopped(table))
	{
		i = 0;
		while (i < table->nb_philo)
		{
			if (philo_is_dead(table, i))
			{
				print_death(&table->philos[i]);
				return (NULL);
			}
			i++;
		}
		if (all_ate_enough(table))
		{
			set_stop(table);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
