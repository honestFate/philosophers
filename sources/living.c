/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/29 18:05:35 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*start_routine(void *arg)
{
	int	i;
	t_philo *philo;

	philo = arg;
	i = 0;
	while (i)
	{
		printf("start eating %d", philo->id);
		custom_usleep(philo->time_to_eat);
		printf("end eating");
		if (philo->is_endless == i)
			printf("LETS CELEBRATE AND SUCK SOME DICK");
		i++;
	}
}