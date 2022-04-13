/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/13 20:23:50 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int main(int argc, char **argv)
{
	int				i;
	t_philos_info	*philos;
	pthread_t		checker;
	char	**man;

	man = malloc(sizeof(1));
    if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	philos = initialization(argc, argv);
	if (!philos)
		return (error("THREADS ERR"));
	i = 0;
	pthread_create(&checker, NULL, philo_check, philos);
	pthread_join(checker, NULL);
	while (i < philos->number_of_philosophers)
	{
		pthread_join(philos->thread[i], NULL);
		i++;
	}
	free_all(philos);
}
