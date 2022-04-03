/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:47:39 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/03 07:33:21 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_cummon_info
{
	int		death;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		is_endless;
	pthread_mutex_t	*print;
	pthread_mutex_t	*meal;
	pthread_mutex_t	*forks_availability;
	pthread_mutex_t	**forks;
}	t_c_info;

typedef struct s_philo
{
	int 		id;
	int			left_fork;
	int			right_fork;
	int			eat_count;
	t_c_info	*c_info;
}	t_philo;

typedef struct s_philos_info
{
	int 		number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			is_endless;
	t_philo		**philo;
	pthread_t	*tread;
	pthread_mutex_t	**forks;
}	t_philos_info;

void			custom_usleep(int ms);
int				ft_atoi(const char *str);
int				error(const char *err_msg);
int				arg_parser(char **args);
void			initialization_forks(t_philos_info *philos);
void			initialization_philos(t_philos_info *philos);
t_philos_info	*initialization(int argc, char **argv);
void			*start_routine(void *arg);
long int		get_timestamp(void);

#endif