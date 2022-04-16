/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_at_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:10:18 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 18:14:41 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	free_all(t_philos_info *philos)
{
	int	i;

	free(philos->philo[0]->c_info);
	free(philos->thread);
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos->forks[i]);
		free(philos->philo[i]);
		i++;
	}
	free(philos->philo);
	free(philos->forks);
	free(philos);
	return (0);
}
