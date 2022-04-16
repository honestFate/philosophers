/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:47:39 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 18:12:56 by ndillon          ###   ########.fr       */
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
# include <limits.h>
# define ERROR 1
# define OK 0

typedef struct s_cummon_info
{
	int				death;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		time;
	pthread_mutex_t	*forks;
}	t_c_info;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			meal_count;
	long int	last_meal;
	t_c_info	*c_info;
}	t_philo;

typedef struct s_philos_info
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_endless;
	t_philo			**philo;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
}	t_philos_info;

void			custom_usleep(int ms);
int				ft_atoi(const char *str);
int				error(const char *err_msg);
int				arg_parser(char **args);
int				ft_minmax_int(char	*str);
long int		get_timestamp(void);
t_c_info		*cummon_info_init(t_philos_info *philos);
int				thread_start(t_philos_info *philos);
int				initialization_forks(t_philos_info *philos);
void			initialization_philos(t_philos_info *philos, t_c_info *c_info);
t_philos_info	*initialization(int argc, char **argv);
void			*start_routine(void *arg);
int				is_all_alive(t_philos_info	*philo);
void			*philo_check(void *philo);
int				philo_start_checker(t_philos_info *philos);
void			status_print(t_philo *philo, char *status, long int time);
int				free_all(t_philos_info *philos);

#endif