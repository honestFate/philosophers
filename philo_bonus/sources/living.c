/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/17 05:19:23 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	status_print(t_philo *philo, char *status, long int time)
{
	printf("%05ld %d %s\n", time - philo->c_info->time, philo->id, status);
}

void	philo_sleep(t_philo *philo)
{
	status_print(philo, "is sleeping", get_timestamp());
	custom_usleep(philo->c_info->time_to_sleep - 1);
}

void	philo_eat(t_philo *philo)
{
	sem_wait(philo->c_info->semaphore);
	status_print(philo, "has taken a fork", get_timestamp());
	sem_wait(philo->c_info->semaphore);
	status_print(philo, "has taken a fork", get_timestamp());
	philo->last_meal = get_timestamp();
	status_print(philo, "is eating", get_timestamp());
	custom_usleep(philo->c_info->time_to_eat - 1);
	philo->meal_count++;
	sem_post(philo->c_info->semaphore);
	sem_post(philo->c_info->semaphore);
}

void	start_routine(t_philo *philo)
{
	philo->last_meal = get_timestamp();
	pthread_create(&philo->checker, NULL, checker, philo);
	status_print(philo, "is thinking", get_timestamp());
	if (philo->id % 2 == 0)
		custom_usleep(philo->c_info->time_to_eat - 1);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		status_print(philo, "is thinking", get_timestamp());
	}
}
