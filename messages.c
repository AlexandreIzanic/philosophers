#include "philo.h"

void    pick_up_forks(t_philo *philo)
{
    msg_fork(philo);
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
}

void    put_down_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    printf(GREEN "Philosopher %d has put down the forks\n" RESET, philo->id);
}

void    philo_think(t_philo *philo)
{
    usleep(1000); // Simulate thinking time
    printf(ORANGE "Philosopher %d is thinking\n" RESET, philo->id);
}

void    philo_eat(t_philo *philo)
{
    int ms;

    ms = philo->time_to_eat * 1000; 
    pick_up_forks(philo);
    usleep(ms);
    printf(GREEN "Philosopher %d is eating in %d ms\n" RESET, philo->id, ms / 1000);
    put_down_forks(philo);   
}
void    philo_sleep(t_philo *philo)
{
    usleep(philo->time_to_sleep * 1000);
    printf(PURPLE "Philosopher %d is sleeping in %d ms\n" RESET, philo->id, philo->time_to_sleep);
}


void    msg_fork(t_philo *philo)
{
    printf(GREEN "Philosopher %d has taken a fork\n" RESET, philo->id);
}

void   msg_die(t_philo *philo)
{
    printf(RED "Philosopher %d has died\n" RESET, philo->id);
}

