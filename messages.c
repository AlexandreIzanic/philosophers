#include "philo.h"

void    msg_eat(t_philo *philo)
{
    int ms;

    ms = philo->time_to_eat * 1000; 
    usleep(ms);
    printf(GREEN "Philosopher %d is eating in %d ms\n" RESET, philo->id, ms / 1000);
}
void    msg_sleep(t_philo *philo)
{
    printf(GREEN "Philosopher %d is sleeping\n" RESET, philo->id);
}

void    msg_think(t_philo *philo)
{
    printf(GREEN "Philosopher %d is thinking\n" RESET, philo->id);
}

void    msg_fork(t_philo *philo)
{
    printf(GREEN "Philosopher %d has taken a fork\n" RESET, philo->id);
}

void   msg_die(t_philo *philo)
{
    printf(RED "Philosopher %d has died\n" RESET, philo->id);
}

