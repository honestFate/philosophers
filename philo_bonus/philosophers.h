/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:47:39 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/18 15:41:45 by ndillon          ###   ########.fr       */
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
# define SEM_FORK "sem_fork_name"
# define SEM_MEAL "sem_meal_name"
# define SEM_PRINT "sem_print_name"

typedef struct s_cummon_info
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_endless;
	long int		time;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_meals;
}	t_c_info;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	long int	last_meal;
	t_c_info	c_info;
}	t_philo;

typedef struct s_philos_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_endless;
	pid_t			*pid;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	sem_t			*sem_meals;
	t_philo			**philo;
}	t_philos_info;

void			custom_usleep(int ms);
int				ft_atoi(const char *str);
int				error(const char *err_msg);
int				arg_parser(char **args);
int				ft_minmax_int(char	*str);
long int		get_timestamp(void);
t_philos_info	*initialization(int argc, char **argv);
void			cummon_info_init(t_philos_info *philos, t_philo *philo);
int				process_create(t_philos_info *philos);
void			initialization_philos(t_philos_info *philos);
void			start_routine(t_philos_info *philos, int id);
void			*death_checker(void *philo);
int				create_sems(t_philos_info *philos);
int				meal_checker(t_philos_info *philos);
void			status_print(t_philo *philo, char *status, long int time);
int				free_all(t_philos_info *philos, int need_kill,
					int need_sem_unlink);

#endif