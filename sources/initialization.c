/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:26:19 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 18:21:31 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	initialization_forks(t_philos_info *philos)
{
	int	i;

	i = 0;
	philos->forks = (pthread_mutex_t *)malloc(philos->number_of_philosophers
			* sizeof(pthread_mutex_t));
	while (i < philos->number_of_philosophers)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL))
		{
			free(philos->forks);
			return (ERROR);
		}
		i++;
	}
	return (OK);
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
		if (!i)
			philos->philo[i]->left_fork = philos->number_of_philosophers - 1;
		else
			philos->philo[i]->left_fork = i - 1;
		philos->philo[i]->right_fork = i;
		philos->philo[i]->c_info = c_info;
		i++;
	}
}

t_c_info	*cummon_info_init(t_philos_info *philos)
{
	t_c_info	*c_info;

	c_info = (t_c_info *)malloc(sizeof(t_c_info));
	c_info->time_to_die = philos->time_to_die;
	c_info->time_to_eat = philos->time_to_eat;
	c_info->time_to_sleep = philos->time_to_sleep;
	c_info->forks = philos->forks;
	c_info->death = 0;
	c_info->time = get_timestamp();
	return (c_info);
}

int	thread_start(t_philos_info *philos)
{
	int	i;

	philos->thread = (pthread_t *)malloc(philos->number_of_philosophers
			* sizeof(pthread_t));
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		if (pthread_create(&philos->thread[i], NULL,
				start_routine, philos->philo[i]))
			return (ERROR);
		i++;
	}
	return (OK);
}

t_philos_info	*initialization(int argc, char **argv)
{
	t_philos_info	*philos;

	philos = (t_philos_info *)malloc(sizeof(t_philos_info));
	philos->number_of_philosophers = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->is_endless = ft_atoi(argv[5]);
	else
		philos->is_endless = 0;
	if (initialization_forks(philos))
	{
		free(philos);
		return (NULL);
	}
	initialization_philos(philos, cummon_info_init(philos));
	if (thread_start(philos))
	{
		free_all(philos);
		return (NULL);
	}
	return (philos);
}
