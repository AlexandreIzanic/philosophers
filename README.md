[guide](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)
[create threads](https://www.youtube.com/watch?v=uA8X5zNOGw8&list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM)
[wiki threads](https://en.wikipedia.org/wiki/Thread_(computing))
[multithreading wiki](https://en.wikipedia.org/wiki/Multithreading_(computer_architecture))
[introduction to threads](https://www.youtube.com/watch?v=LOfGJcVnvAk)

threads == work on multiple things concurently

concurrent programming


task synchronisation

## usage
./philo [nb_philo] [time_to_die] [time_to_eat] [time_to_sleep] [optional_nb_meal]


## mutex example 

    pthread_mutex_t my_mutex;

    pthrea_mutex_init(&my_mutex);

    void    func()
    {
        pthread_mutex_lock(&my_mutex)
        ...
        pthread_mutex_unlock(&my_mutex)
    }