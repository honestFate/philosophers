/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/13 20:09:21 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_sleep(t_philo *philo)
{
	status_print(philo, "sleep", get_timestamp());
	custom_usleep(philo->c_info->time_to_sleep - 1);
}

void	status_print(t_philo *philo, char *status, long int time)
{
	if (!philo->c_info->death)
		printf("%05ld %d %s\n", time - philo->c_info->time, philo->id, status);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->c_info->forks[philo->left_fork]);
	pthread_mutex_lock(philo->c_info->forks[philo->right_fork]);
	philo->last_meal = get_timestamp();
	philo->meal_count++;
	status_print(philo, "has taken a fork", get_timestamp());
	status_print(philo, "is eating", get_timestamp());
	custom_usleep(philo->c_info->time_to_eat - 1);
	pthread_mutex_unlock(philo->c_info->forks[philo->left_fork]);
	pthread_mutex_unlock(philo->c_info->forks[philo->right_fork]);
}

void	*start_routine(void *arg)
{
	int	i;
	t_philo *philo;

	philo = arg;
	i = 1;
	philo->last_meal = get_timestamp();
	if (philo->id % 2 == 0)
		custom_usleep(philo->c_info->time_to_eat - 2);
	while (!philo->c_info->death)
	{
		philo_eat(philo);
		philo_sleep(philo);
		status_print(philo, "thinking", get_timestamp());
	}
	return (NULL);
}
