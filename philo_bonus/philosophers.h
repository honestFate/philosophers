/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:47:39 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/17 05:30:44 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <signal.h>
# include <semaphore.h>
# include <limits.h>
# define ERROR 1
# define OK 0

typedef struct s_cummon_info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		time;
	sem_t 			*semaphore;
	pid_t			*pid;
}	t_c_info;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	long int	last_meal;
	pthread_t	checker;
	t_c_info	*c_info;
}	t_philo;

typedef struct s_philos_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_endless;
	pid_t			*pid;
	t_philo			**philo;
}	t_philos_info;

void			custom_usleep(int ms);
int				ft_atoi(const char *str);
int				error(const char *err_msg);
int				arg_parser(char **args);
int				ft_minmax_int(char	*str);
long int		get_timestamp(void);
t_c_info	*cummon_info_init(t_philos_info *philos, sem_t *semaphore);
int				thread_start(t_philos_info *philos);
int				initialization_forks(t_philos_info *philos);
void			initialization_philos(t_philos_info *philos, t_c_info *c_info);
t_philos_info	*initialization(int argc, char **argv, sem_t *semaphore);
void			start_routine(t_philo *philo);
int				is_all_alive(t_philos_info	*philo);
void			*philo_check(void *philo);
void			*checker(void *);
void			status_print(t_philo *philo, char *status, long int time);
int				free_all(t_philos_info *philos);

#endif