/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 18:15:17 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	error(const char *err_msg)
{
	while (*err_msg)
		write(2, err_msg++, 1);
	write(2, "\n", 1);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	t_philos_info	*philos;

	if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	philos = initialization(argc, argv);
	if (!philos)
		return (error("INITIALIZATION ERR"));
	philo_start_checker(philos);
	free_all(philos);
	return (0);
}
