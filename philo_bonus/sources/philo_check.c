/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:07:25 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 18:15:41 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_all_alive(t_philos_info	*philo)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (i < philo->number_of_philosophers)
	{
		if (philo->philo[i]->last_meal && get_timestamp()
			- philo->philo[i]->last_meal > philo->time_to_die)
		{
			philo->philo[i]->c_info->death = 1;
			printf("%05ld %d died\n",
				get_timestamp() - philo->philo[i]->c_info->time, i + 1);
			return (1);
		}
		if (philo->philo[i]->meal_count >= philo->is_endless)
			check++;
		i++;
	}
	if (check == philo->number_of_philosophers && philo->is_endless)
	{
		philo->philo[0]->c_info->death = 1;
		return (1);
	}
	return (0);
}

void	*philo_check(void *data)
{
	int				i;
	t_philos_info	*philo;

	philo = (t_philos_info *)data;
	custom_usleep(1);
	i = 0;
	while (1)
	{
		if (is_all_alive(philo))
			return (NULL);
		usleep(100);
	}
}

int	philo_start_checker(t_philos_info *philos)
{
	int			i;
	pthread_t	checker;

	i = 0;
	if (pthread_create(&checker, NULL, philo_check, philos))
		return (error("THREADS ERR"));
	if (pthread_join(checker, NULL))
		return (error("JOIN ERR"));
	while (i < philos->number_of_philosophers)
	{
		if (pthread_join(philos->thread[i], NULL))
			return (error("JOIN ERR"));
		i++;
	}
	return (OK);
}
