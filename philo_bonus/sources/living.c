/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/18 15:21:43 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	status_print(t_philo *philo, char *status, long int time)
{
	sem_wait(philo->c_info.sem_print);
	printf("%05ld %d %s\n", time - philo->c_info.time, philo->id, status);
	sem_post(philo->c_info.sem_print);
}

void	philo_sleep(t_philo *philo)
{
	status_print(philo, "is sleeping", get_timestamp());
	custom_usleep(philo->c_info.time_to_sleep - 1);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->c_info.sem_forks);
	status_print(philo, "has taken a fork", get_timestamp());
	sem_wait(philo->c_info.sem_forks);
	status_print(philo, "has taken a fork", get_timestamp());
	philo->last_meal = get_timestamp();
	status_print(philo, "is eating", get_timestamp());
	custom_usleep(philo->c_info.time_to_eat - 1);
	philo->meal_count++;
	if (philo->meal_count == philo->c_info.is_endless)
		sem_post(philo->c_info.sem_meals);
	sem_post(philo->c_info.sem_forks);
	sem_post(philo->c_info.sem_forks);
}

void	start_routine(t_philos_info *philos, int id)
{
	pthread_t	death_checker_thread;
	t_philo		philo;

	philo = *(philos->philo[id]);
	free(philos->pid);
	free_all(philos, 0, 0);
	philo.last_meal = get_timestamp();
	if (pthread_create(&death_checker_thread, NULL, death_checker, &philo)
		|| pthread_detach(death_checker_thread))
		exit(1);
	status_print(&philo, "is thinking", get_timestamp());
	if (philo.id % 2 == 0)
		custom_usleep(philo.c_info.time_to_eat - 1);
	while (1)
	{
		philo_eat(&philo);
		philo_sleep(&philo);
		status_print(&philo, "is thinking", get_timestamp());
	}
}
