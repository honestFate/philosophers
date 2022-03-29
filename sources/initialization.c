/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:26:19 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/29 18:00:34 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	initialization_forks(t_philos_info *philos)
{
	int	i;

	i = 0;
	philos->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	while (i < philos->number_of_philosophers)
	{
		pthread_mutex_init(&philos->forks[i], NULL);
		i++;
	}
}

void	initialization_philos(t_philos_info *philos)
{
	int	i;

	i = 0;
	philos->philo = (t_philo **)malloc(sizeof(t_philo *));
	while (i < philos->number_of_philosophers)
	{
		philos->philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philos->philo[i]->id = i + 1;
		if (i == 0)
			philos->philo[i]->left_fork = philos->number_of_philosophers - 1;
		else
			philos->philo[i]->left_fork = i - 1;
		if (philos->number_of_philosophers > 1)
			philos->philo[i]->right_fork = i;
		else
			philos->philo[i] = NULL;
		philos->philo[i]->time_to_die = philos->time_to_die;
		philos->philo[i]->time_to_eat = philos->time_to_eat;
		philos->philo[i]->time_to_sleep = philos->time_to_sleep;
		philos->philo[i]->is_endless = philos->is_endless;
		philos->philo[i]->forks = philos->forks;
		i++;
	}
}

t_philos_info	*initialization(int argc, char **argv)
{
	int				i;
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
	initialization_forks(philos);
	initialization_philos(philos);
	philos->tread = (pthread_t *)malloc(sizeof(pthread_t));
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		pthread_create(&philos->tread[i], NULL, start_routine, philos->philo[i]);
		i++;
	}
	return (philos);
}
