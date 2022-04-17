/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:26:19 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/17 03:52:30 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

pid_t	*process_create(t_philos_info *philos)
{
	int		i;
	pid_t	*pid;

	pid = (pid_t *)malloc(philos->number_of_philosophers * sizeof(pid_t));
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			while (i >= 0)
				kill(pid[i--], SIGKILL);
			free(pid);
			return (1);
		}
		else if (pid[i] == 0)
			start_routine(philos);
		i++;
	}
	if (pid[0] > 0)
		return (pid);
}

void	initialization_philos(t_philos_info *philos, t_c_info *c_info)
{
	int	i;

	philos->philo = (t_philo **)malloc(philos->number_of_philosophers
			* sizeof(t_philo *));
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		philos->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philos->philo[i]->id = i + 1;
		philos->philo[i]->meal_count = 0;
		philos->philo[i]->last_meal = 0;
		philos->philo[i]->c_info = c_info;
		i++;
	}
}

t_c_info	*cummon_info_init(t_philos_info *philos, sem_t *semaphore)
{
	t_c_info	*c_info;

	c_info = (t_c_info *)malloc(sizeof(t_c_info));
	c_info->time_to_die = philos->time_to_die;
	c_info->time_to_eat = philos->time_to_eat;
	c_info->time_to_sleep = philos->time_to_sleep;
	c_info->time = get_timestamp();
	c_info->semaphore = semaphore;
	return (c_info);
}

t_philos_info	*initialization(int argc, char **argv, sem_t *semaphore)
{
	t_philos_info	*philos;
	pid_t			*pid;

	philos = (t_philos_info *)malloc(sizeof(t_philos_info));
	philos->number_of_philosophers = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->is_endless = ft_atoi(argv[5]);
	else
		philos->is_endless = 0;
	initialization_philos(philos, cummon_info_init(philos, semaphore));
	pid = process_create(philos);
	if (!pid)
	{
		free_all(philos);
		return (NULL);
	}
	return (philos);
}
