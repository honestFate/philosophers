/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:07:25 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/18 15:41:03 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*death_checker(void *data)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data;
	custom_usleep(1);
	i = 0;
	while (1)
	{
		if (philo->last_meal && get_timestamp()
			- philo->last_meal > philo->c_info.time_to_die)
		{
			sem_wait(philo->c_info.sem_print);
			printf("%05ld %d died\n",
				get_timestamp() - philo->c_info.time, i + 1);
			exit(0);
		}
		usleep(500);
	}
}

int	meal_checker(t_philos_info *philos)
{
	int	i;
	int	pid;

	pid = fork();
	if (pid < 0)
		return (pid);
	if (pid == 0)
	{
		free(philos->pid);
		free_all(philos, 0, 0);
		i = 0;
		while (i < philos->number_of_philosophers)
		{
			sem_wait(philos->sem_meals);
			i++;
		}
	}
	return (pid);
}
