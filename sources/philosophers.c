/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philisophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/29 19:16:37 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main(int argc, char **argv)
{
	int				i;
	t_philos_info	*philos;

    if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	philos = initialization(argc, argv);
	if (!philos)
		return (error("THREADS ZALUPA"));
	while (i < philos->number_of_philosophers)
	{
		pthread_join(philos->tread[i], NULL);
		i++;
	}
    return (0);
}
