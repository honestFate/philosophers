/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_at_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 17:10:18 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/17 06:14:38 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	free_all(t_philos_info *philos)
{
	int	i;

	i = 0;
	while (i < philos->number_of_philosophers)
		kill(philos->pid[i++], SIGKILL);
	free(philos->philo[0]->c_info);
	i = 0;
	while (i < philos->number_of_philosophers)
		free(philos->philo[i++]);
	free(philos->philo);
	free(philos);
	return (0);
}
