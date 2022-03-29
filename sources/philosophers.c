/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/03/29 21:12:18 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main(int argc, char **argv)
{
	int				i;
	t_philos_info	*philos;
	char	**man;

	man = malloc(sizeof(1));
    if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	philos = initialization(argc, argv);
	if (!philos)
		return (error("THREADS ZALUPA"));
	i = 0;
	while (i < philos->number_of_philosophers)
	{
		pthread_join(philos->tread[i], NULL);
		write(1, "1", 1);
		i++;
	}
}
