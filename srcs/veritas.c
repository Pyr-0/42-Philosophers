/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veritas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:23:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/25 19:18:54 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

bool	take_fork(t_phil *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo->value = true;
	if (philo->value == true)
		printf("%lu %d has taken a fork\n",
			get_time(all()->start_time), philo->phil_id);
	pthread_mutex_lock(&all()->philos[philo->phil_id % all()->p_count]->fork);
	printf("%lu %d has taken a fork2\n",
		get_time(all()->start_time), philo->phil_id);
	printf("%lu %d is eating\n",get_time(all()->start_time), philo->phil_id);
	philo->times_eaten++;
	return (false);
}

/*
bool	drop_fork(t_phil *fork, t_phil *phil)
{
	fork->value = false;  
	pthread_mutex_unlock(&fork->fork);
	if (fork->value == false)
		printf("%lu %d has taken a fork\n",
				get_time(all()->start_time), phil->phil_id);
	return (false);
}
 */
bool	input_check(char **argv)
{
	int	i;
	int j;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '0')
			(false);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] <= '9' && argv[i][j] >= '0')
				j++;
			else
				return (false);
		}
		i++;
	}
	return (true);
}
