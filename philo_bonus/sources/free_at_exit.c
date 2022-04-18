/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_at_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:10:18 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/18 15:19:38 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	free_all(t_philos_info *philos, int need_kill, int need_sem_unlink)
{
	int	i;

	i = 0;
	if (need_kill)
	{
		while (i < philos->number_of_philosophers)
			kill(philos->pid[i++], SIGKILL);
		free(philos->pid);
	}
	if (need_sem_unlink)
	{
		sem_close(philos->sem_forks);
		sem_close(philos->sem_print);
		sem_close(philos->sem_meals);
		sem_unlink(SEM_FORK);
		sem_unlink(SEM_PRINT);
		sem_unlink(SEM_MEAL);
	}
	i = 0;
	while (i < philos->number_of_philosophers)
		free(philos->philo[i++]);
	free(philos->philo);
	free(philos);
	return (0);
}
