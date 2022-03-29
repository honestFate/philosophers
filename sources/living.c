/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:36:11 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/29 21:47:15 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*start_routine(void *arg)
{
	int	i;
	t_philo *philo;

	philo = arg;
	i = 1;
	printf("philo %d\n", philo->id);
	usleep(10000);
	while (i)
	{
		printf("start eating %d\n", philo->id);
		printf("end eating\n");
		if (philo->is_endless == i)
			printf("LETS CELEBRATE AND SUCK SOME DICK\n");
		i++;
		usleep(10000000);
	}
	return NULL;
}