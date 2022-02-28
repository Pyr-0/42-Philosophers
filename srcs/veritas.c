/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veritas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:23:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/28 16:35:19 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

bool	take_fork(t_phil *philo)
{
	pthread_mutex_lock(&philo->fork.mutex);
	philo->fork.value = true;
	printf("%lu %d has taken a fork\n",
				get_time(all()->start_time), philo->phil_id);
	pthread_mutex_lock(&all()->philos[philo->phil_id % all()->p_count]->fork.mutex);
	all()->philos[philo->phil_id % all()->p_count]->fork.value = true;
	printf("%lu %d has taken a fork2\n",
	get_time(all()->start_time), philo->phil_id);
	printf("%lu %d is eating\n", get_time(all()->start_time), philo->phil_id);
	philo->times_eaten++;
	return (false);
}

/* 
bool	drop_fork(t_phil *philo)
{
	philo->value = true;
	while(philo->value == true)
	{
		if (all()->meal_limit != 0)
			{
				if (all()->meal_limit <= philo->times_eaten)
				{
					philo->state = DONE;
					pthread_mutex_unlock(&philo->fork);
					pthread_mutex_unlock(&all()->philos[philo->phil_id % all()->p_count]->fork);
					break ;
				}
			}
			//usleep(all()->t_to_eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&all()->philos[philo->phil_id % all()->p_count]->fork);
		printf("%lu %d is sleeping\n",get_time(all()->start_time),  philo->phil_id);
		usleep(all()->t_to_sleep * 1000);
		printf("%lu %d is thinking\n",get_time(all()->start_time), philo->phil_id);
	}
	return (false);
} */


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
