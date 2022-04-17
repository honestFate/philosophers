/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:37 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/17 05:43:06 by ndillon          ###   ########.fr       */
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
	int				status;
	char			*sem_forks_name;
	char			*sem_meal_name;
	sem_t			*forks;
	sem_t			*meals;
	t_philos_info	*philos;
	pthread_t		meal_cheak_thread;
	
	if (argc < 5 || argc > 6 || arg_parser(argv))
		return (error("INVALID ARGUMENTS"));
	sem_forks_name = "/philo_sem_forks";
	sem_meal_name = "/philo_sem_meals";
	forks = sem_open(sem_forks_name, O_CREAT, 0644, 1);
	if (argc == 6)
	meals = sem_open(sem_meal_name, O_CREAT, 0644, 1);
	philos = initialization(argc, argv, forks);
	if (!philos)
	{
		sem_close(forks);
		sem_unlink(sem_forks_name);
		return (error("INITIALIZATION ERR"));
	}
	if (argc == 6)
	{
		pthread_create(&meal_cheak_thread, NULL, meal_checker, philos);
		pthread_detach(&meal_cheak_thread);
	}
	waitpid(-1, &status, WUNTRACED);
	printf("returned status - %d\n", status);
	philo_start_checker(philos);
	free_all(philos);
	sem_close(forks);
	sem_unlink(sem_forks_name);
	return (0);
}
