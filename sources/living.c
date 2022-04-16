/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 18:14:49 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	status_print(t_philo *philo, char *status, long int time)
{
	if (!philo->c_info->death)
		printf("%05ld %d %s\n", time - philo->c_info->time, philo->id, status);
}

void	philo_sleep(t_philo *philo)
{
	if (philo->c_info->death)
		return ;
	status_print(philo, "is sleeping", get_timestamp());
	custom_usleep(philo->c_info->time_to_sleep - 1);
}

void	philo_eat(t_philo *philo)
{
	if (philo->c_info->death)
		return ;
	pthread_mutex_lock(&philo->c_info->forks[philo->left_fork]);
	status_print(philo, "has taken a fork", get_timestamp());
	pthread_mutex_lock(&philo->c_info->forks[philo->right_fork]);
	status_print(philo, "has taken a fork", get_timestamp());
	philo->last_meal = get_timestamp();
	status_print(philo, "is eating", get_timestamp());
	custom_usleep(philo->c_info->time_to_eat - 1);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->c_info->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->c_info->forks[philo->right_fork]);
}

void	*start_routine(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = arg;
	i = 1;
	philo->last_meal = get_timestamp();
	status_print(philo, "is thinking", get_timestamp());
	if (philo->left_fork == philo->right_fork)
		return (NULL);
	if (philo->id % 2 == 0)
		custom_usleep(philo->c_info->time_to_eat - 1);
	while (!philo->c_info->death)
	{
		philo_eat(philo);
		philo_sleep(philo);
		status_print(philo, "is thinking", get_timestamp());
	}
	return (NULL);
}
