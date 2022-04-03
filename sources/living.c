/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/03 07:43:11 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_sleep(t_philo *philo)
{
	int	i;

	i = 0;
	if (!philo->c_info->death)
		return ;
	while (i < philo->c_info->time_to_sleep)
	{
		custom_usleep(1);
		i++;
	}
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
	if (!philo->c_info->death)
		return ;
	pthread_mutex_lock(philo->c_info->forks_availability);
	pthread_mutex_lock(philo->c_info->forks[philo->left_fork]);
	status_print(philo, "taken a fork");
	pthread_mutex_lock(philo->c_info->forks[philo->right_fork]);
	status_print(philo, "taken a fork");
	pthread_mutex_unlock(philo->c_info->forks_availability);
	pthread_mutex_lock(philo->c_info->meal);
	status_print(philo, "start eating");
	custom_usleep(philo->c_info->time_to_sleep);
	status_print(philo, "end eating");
	pthread_mutex_unlock(philo->c_info->meal);
	pthread_mutex_unlock(philo->c_info->forks[philo->left_fork]);
	status_print(philo, "put a fork");
	pthread_mutex_unlock(philo->c_info->forks[philo->right_fork]);	
	status_print(philo, "put a fork");
}

void	*start_routine(void *arg)
{
	int	i;
	t_philo *philo;

	philo = arg;
	i = 1;
	printf("philo %d\n", philo->id);
	while (i)
	{
		printf("start eating %d\n", philo->id);
		printf("end eating\n");
		if (philo->c_info->is_endless == i)
			printf("LETS CELEBRATE AND SUCK SOME DICK\n");
		i++;
		usleep(10000000);
	}
	return NULL;
}