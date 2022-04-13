#include "../philosophers.h"

void	*philo_check(void *data)
{
	int	i;
	int	check;
	t_philos_info	*philo;

	philo = (t_philos_info *)data;
	custom_usleep(1);
	while (!philo->philo[i]->c_info->death)
	{
		i = 0;
		check = 0;
		while (i < philo->number_of_philosophers)
		{
			if (philo->philo[i]->last_meal &&
				get_timestamp() - philo->philo[i]->last_meal > philo->time_to_die)
			{
				philo->philo[i]->c_info->death = 1;
				printf("%ld %d dead\n", get_timestamp() - philo->philo[i]->c_info->time, i + 1);
				return (NULL);
			}
			if (philo->philo[i]->meal_count >= philo->is_endless)
				check++;
			i++;
		}
		if (check == philo->number_of_philosophers && philo->is_endless)
		{
			philo->philo[i]->c_info->death = 1;
			return (NULL);
		}
		custom_usleep(1);
	}
}
