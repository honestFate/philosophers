/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:40 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/16 17:06:04 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	custom_usleep(int ms)
{
	long int	time;

	time = get_timestamp();
	while (time + ms >= get_timestamp())
		usleep(100);
}

int	ft_atoi(const char *str)
{
	long	nmb;
	int		sign;

	nmb = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		++str;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	else if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		nmb += *str - 48;
		nmb *= 10;
		++str;
	}
	nmb /= 10;
	return (nmb * sign);
}

int	arg_parser(char **args)
{
	int	i;
	int	j;
	int	zero_flag;

	i = 1;
	while (args[i])
	{
		if (ft_minmax_int(args[i]))
			return (ERROR);
		j = 0;
		zero_flag = 0;
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return (ERROR);
			if (args[i][j] != '0')
				zero_flag = 1;
			j++;
		}
		if (!zero_flag)
			return (ERROR);
		i++;
	}
	return (OK);
}

long int	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_minmax_int(char	*str)
{
	int			sign;
	long int	nmb;

	nmb = 0;
	sign = 0;
	while (*str == '\t' || *str == '\n'
		|| *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		++str;
	if (*str == '-')
	{
		sign = 1;
		++str;
	}
	else if (*str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		nmb += *str - 48;
		if ((nmb > INT_MAX && !sign) || (-nmb < INT_MIN && sign))
			return (ERROR);
		nmb *= 10;
		++str;
	}
	return (OK);
}
