#include "../philosophers.h"

void	philo_check(t_philos_info *philo)
{
	int	i;
	int	check;

	custom_usleep(1);
	while (1)
	{
		write(1, "check\n", 6);
		i = 0;
		check = 0;
		pthread_mutex_lock(philo->philo[0]->c_info->meal);
		pthread_mutex_lock(philo->philo[0]->c_info->print);
		while (i < 5)
		{
			if (get_timestamp() - philo->philo[i]->last_meal >= philo->time_to_die)
			{
				write(1, "dead\n", 5);
				status_print(philo->philo[i], "dead end");
				exit(1);
				return ;
			}
			if (philo->philo[i]->meal_count >= philo->is_endless)
				check++;
			i++;
		}
		if (check == philo->number_of_philosophers)
			return ;
		pthread_mutex_unlock(philo->philo[0]->c_info->meal);
		pthread_mutex_unlock(philo->philo[0]->c_info->print);
		write(1, "check end\n", 10);
		usleep(2000);
	}
}
