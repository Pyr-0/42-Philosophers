/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veritas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:23:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/03 05:35:02 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

bool	take_forks(t_phil *philo)
{
	take_fork(&all()->philos->fork.mutex);
	pthread_mutex_lock(&all()->philos[philo->phil_id % all()->p_count]->fork.mutex);
	all()->philos[philo->phil_id % all()->p_count]->fork.value = false;
	printf("%lu %d has taken a fork2\n",
	get_time(all()->start_time), philo->phil_id);
	printf("%lu %d is eating\n", get_time(all()->start_time), philo->phil_id);
	philo->times_eaten++;
	return (false);
}

/* bool	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->value = false;
	printf("%lu %d has taken a fork2\n",
			get_time(all()->start_time), philo->phil_id);
}
 */
bool	drop_fork(t_phil *philo)
{
	philo->fork.value = true;
	pthread_mutex_unlock(&philo->fork.mutex);
	all()->philos[philo->phil_id % all()->p_count]->fork.value = true;
	pthread_mutex_unlock(&all()->philos[philo->phil_id % all()->p_count]->fork.mutex);
	return (false);
}

bool	input_check(char **argv)
{
	int	i;
	int j;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '0')
			return (false);
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
