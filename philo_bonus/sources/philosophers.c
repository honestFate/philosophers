/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/18 15:41:38 by ndillon          ###   ########.fr       */
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
	int				status;
	int				pid;

	if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	philos = initialization(argc, argv);
	if (!philos)
		return (error("INITIALIZATION ERR"));
	if (argc == 6)
	{
		pid = meal_checker(philos);
		if (pid < 0)
		{
			free_all(philos, 1, 1);
			return (1);
		}
		if (pid == 0)
			return (0);
	}
	waitpid(-1, &status, WUNTRACED);
	if (status)
		error("PROCESS EXIT WITH ERROR");
	free_all(philos, 1, 1);
	return (0);
}
