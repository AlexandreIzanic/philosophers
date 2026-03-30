#include "philo.h"

void    init_philos(t_table *table)
{
    int i;

    table->philos = malloc(sizeof(t_philo) * table->nb_philo);
    if (!table->philos)
        return ;
    for (i = 0; i < table->nb_philo; i++)
    {
        table->philos[i].id = i + 1;
        table->philos[i].nb_meals_eaten = 0;
        table->philos[i].time_to_eat = table->time_to_eat;
        // Initialize left and right forks here
    }
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    (void)philo;
    
    // Implement philosopher's routine here
    // For example: think, pick up forks, eat, put down forks, sleep
    while (1)
    {
        msg_eat(philo);
    }
    return NULL;
}

int create_philo_threads(t_table *table)
{
    int i;
    pthread_t *threads;

    threads = malloc(sizeof(pthread_t) * table->nb_philo);
    if (!threads)
        return (1);
    for (i = 0; i < table->nb_philo; i++)
    {
        if (pthread_create(&threads[i], NULL, philo_routine, &table->philos[i]) != 0)
        {
            free(threads);
            return (1);
        }
    }
    // wait for all threads to finish
    while (i--)
        pthread_join(threads[i], NULL);
    free(threads);
    return (0);
}

int validate_args(t_table *table)
{
    if (table->nb_philo <= 0 || table->time_to_die <= 0 || 
        table->time_to_eat <= 0 || table->time_to_sleep <= 0)
        return (-1);
    return (0);
}

int	main(int argc, char *argv[])
{
	t_table table;
	if (argc < 5 || argc > 6)
	{
		printf(RED "Error\nargs nb" RESET);
		return (1);
	}
	init_args(&table, argv, argc);	
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
	return(0);
} 
