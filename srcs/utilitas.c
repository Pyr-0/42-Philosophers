/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:44:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/22 13:34:04 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

unsigned long	get_time(int begin_time)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000) - begin_time);
}

static	int	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\v'
		|| c == '\n' || c == '\r' || c == '\t')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;
	int		counter;

	sign = 1;
	result = 0;
	counter = 0;
	while (ft_isspace (str[counter]))
		counter ++;
	if (str[counter] == '+')
		counter++;
	else if (str[counter] == '-')
	{
		sign = -1;
		counter++;
	}
	while (ft_isdigit(str[counter]))
	{
		result = result * 10 + (str[counter] - '0');
		counter++;
	}
	return (result * sign);
}
