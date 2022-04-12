/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/12 20:09:00 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_sleep(t_philo *philo)
{
	int	i;

	i = 0;
	if (!philo->c_info->death)
		return ;
	status_print(philo, "sleep\n");
	while (++i < philo->c_info->time_to_sleep)
		custom_usleep(1);
}

void	status_print(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->c_info->print);
	if (!philo->c_info->death)
		printf("%ld %d %s", get_timestamp(), philo->id, status);
	pthread_mutex_unlock(philo->c_info->print);
}

void	philo_eat(t_philo *philo)
{
	write(1, "lock\n", 5);
	pthread_mutex_lock(philo->c_info->forks_availability);
	write(1, "eat\n", 4);
	pthread_mutex_lock(philo->c_info->forks[philo->left_fork]);
	pthread_mutex_lock(philo->c_info->forks[philo->right_fork]);
	pthread_mutex_unlock(philo->c_info->forks_availability);
	pthread_mutex_lock(philo->c_info->meal);
	if (philo->c_info->death)
		return ;
	philo->last_meal = get_timestamp();
	philo->meal_count++;
	pthread_mutex_unlock(philo->c_info->meal);
	status_print(philo, "taken a forks");
	pthread_mutex_unlock(philo->c_info->forks_availability);
	pthread_mutex_lock(philo->c_info->meal);
	status_print(philo, "start eating");
	custom_usleep(philo->c_info->time_to_sleep);
	status_print(philo, "end eating");
	pthread_mutex_unlock(philo->c_info->forks[philo->left_fork]);
	pthread_mutex_unlock(philo->c_info->forks[philo->right_fork]);	
	status_print(philo, "put a forks");
	write(1, "end\n", 4);
}

void	*start_routine(void *arg)
{
	int	i;
	t_philo *philo;

	philo = arg;
	i = 1;
	printf("philo %d active\n", philo->id);
	philo->last_meal = get_timestamp();
	if (philo->id % 2 == 0)
		custom_usleep(philo->c_info->time_to_eat);
	while (1)
	{
		status_print(philo, "thinking\n");
		philo_eat(philo);
		write(1, "1\n", 2);
		philo_sleep(philo);
	}
	return NULL;
}