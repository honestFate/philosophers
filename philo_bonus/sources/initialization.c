/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:26:19 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/18 15:41:15 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	process_create(t_philos_info *philos)
{
	int		i;

	philos->pid = (pid_t *)malloc(philos->number_of_philosophers
			* sizeof(pid_t));
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		philos->pid[i] = fork();
		if (philos->pid[i] < 0)
		{
			while (i >= 0)
				kill(philos->pid[i--], SIGKILL);
			free(philos->pid);
			return (ERROR);
		}
		else if (philos->pid[i] == 0)
			start_routine(philos, i);
		i++;
	}
	return (OK);
}

void	initialization_philos(t_philos_info *philos)
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
		cummon_info_init(philos, philos->philo[i]);
		i++;
	}
}

void	cummon_info_init(t_philos_info *philos, t_philo *philo)
{
	philo->c_info.time_to_die = philos->time_to_die;
	philo->c_info.time_to_eat = philos->time_to_eat;
	philo->c_info.time_to_sleep = philos->time_to_sleep;
	philo->c_info.is_endless = philos->is_endless;
	philo->c_info.time = get_timestamp();
	philo->c_info.sem_forks = philos->sem_forks;
	philo->c_info.sem_print = philos->sem_print;
	philo->c_info.sem_meals = philos->sem_meals;
}

int	create_sems(t_philos_info *philos)
{
	philos->sem_forks = NULL;
	philos->sem_print = NULL;
	philos->sem_meals = NULL;
	if (philos->is_endless)
	{
		sem_unlink(SEM_MEAL);
		philos->sem_meals = sem_open(SEM_MEAL, O_CREAT, 0644, 0);
	}
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_PRINT);
	philos->sem_forks = sem_open(SEM_FORK, O_CREAT, 0644,
			philos->number_of_philosophers);
	philos->sem_print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (!philos->sem_forks || !philos->sem_print
		|| (philos->is_endless && !philos->sem_meals))
	{
		sem_close(philos->sem_forks);
		sem_close(philos->sem_print);
		sem_close(philos->sem_meals);
		sem_unlink(SEM_FORK);
		sem_unlink(SEM_PRINT);
		sem_unlink(SEM_MEAL);
		return (ERROR);
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
	if (create_sems(philos))
	{
		free(philos);
		return (NULL);
	}
	initialization_philos(philos);
	if (process_create(philos))
	{
		free_all(philos, 0, 1);
		return (NULL);
	}
	return (philos);
}
