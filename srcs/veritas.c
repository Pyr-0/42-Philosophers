/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veritas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:23:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/04 21:31:01 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"


void	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->value = false;
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_unlock(&fork->mutex);
	fork->value = true;
}

void	take_forks(t_phil *philo)
{
	take_fork(&philo->fork);
	printf("%lu %d has taken a fork\n",
			get_time(all()->start_time), philo->phil_id);
	take_fork(&all()->philos[(philo->phil_id) % all()->p_count]->fork);
	printf("%lu %d has taken a fork2\n",
			get_time(all()->start_time), philo->phil_id);
	printf("%lu %d is eating\n", get_time(all()->start_time), philo->phil_id);
	philo->times_eaten++;
	printf("%d times eaten\n",philo->times_eaten);
}

void	drop_forks(t_phil *philo)
{
	drop_fork(&philo->fork);
	printf("%lu %d has drop a fork\n",
			get_time(all()->start_time), philo->phil_id);
	drop_fork(&all()->philos[philo->phil_id % all()->p_count]->fork);
	printf("%lu %d has drop a fork2\n",
			get_time(all()->start_time), philo->phil_id);
}
// 	philo_sleep_for(philo, 1000);
// 	philo_sleep_until(philo,)

/* void	perform_eating(t_phil *philo)
{
	take_forks(philo);
	philo->times_eaten++;
	if (!is_a_philo_dead())
		printf("%lu %d is eating\n", get_time(all()->start_time), philo->phil_id);
	drop_forks(philo);
} */
/* 
bool	rigor_mortis(char **argv)
{
	if (all()->t_to_die == argv[1])
		exit();
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
