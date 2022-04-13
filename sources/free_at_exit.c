#include "../philosophers.h"

void    free_all(t_philos_info *philos)
{
    int i;

    free(philos->philo[0]->c_info);
    free(philos->thread);
    i = 0;
    while (i < philos->number_of_philosophers)
    {
        pthread_mutex_destroy(philos->forks[i]);
        free(philos->philo[i]);
    }
}