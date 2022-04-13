/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndillon <ndillon@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:27:40 by ndillon           #+#    #+#             */
/*   Updated: 2022/04/13 17:58:22 by ndillon          ###   ########.fr       */
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

int	nbr_len(int n)
{
	int	len;

	len = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		++len;
	}
	return (len);
}

char	*putnbr_str(char *str, int n)
{
	int			end;
	int			len;
	long long	x;

	x = n;
	if (!x)
	{
		*str = '0';
		return (str);
	}
	len = nbr_len(x);
	end = len;
	while (len--)
	{
		str[len] = x % 10 + '0';
		x /= 10;
	}
	return (str + end);
}

void	putstr_str(char *str, char *text)
{
	while (*text)
	{
		*str = *text;
		++str;
		++text;
	}
	*str = '\n';
	str++;
	*str = '\0';
}

void	putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
	}
}