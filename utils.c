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

void    one_philo(t_table *table)
{
    printf(RED "Philosopher 1 has taken a fork\n" RESET);
    usleep(table->time_to_die * 1000);
    printf(RED "Philosopher 1 has died in %d ms\n" RESET, table->time_to_die);
}

int ft_atoi(const char *str)
{
    long result = 0;
    int sign = 1;
    const char *p = str;

    while (*p == ' ' || (*p >= '\t' && *p <= '\r'))
        p++;
    if (*p == '+' || *p == '-') {
        if (*p == '-')
            sign = -1;
        p++;
    }
    while (*p >= '0' && *p <= '9') {
        result = result * 10 + (*p - '0');
        if (sign == 1 && result > INT_MAX)
            return INT_MAX;
        if (sign == -1 && -result < INT_MIN)
            return INT_MIN;
        p++;
    }
    return (int)(sign * result);
}
