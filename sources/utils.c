/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:40 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/03 06:51:50 by ndillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	error(const char *err_msg)
{
	printf("%s", err_msg);
	return (1);
}

void	custom_usleep(int ms)
{
	int	i;

	i = 0;
	while (i < ms)
	{
		usleep(1000);
		i += 1;
	}
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

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] < '0' || args[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long int	get_timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}