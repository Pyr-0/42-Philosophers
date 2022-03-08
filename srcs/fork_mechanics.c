/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mechanics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:01:20 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/08 17:16:19 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sophos.h>

bool	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mtx);
	if (fork->value == false)
	{
		pthread_mutex_unlock(&fork->mtx);
		return (false);
	}
	fork->value = false;
	pthread_mutex_unlock(&fork->mtx);
	return (true);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mtx);
	fork->value = true;
	pthread_mutex_unlock(&fork->mtx);
}

void	drop_forks(t_phil *philo)
{
	drop_fork(&philo->fork);
	drop_fork(&all()->philos[philo->phil_id % all()->p_count]->fork);
}

bool	take_forks(t_phil *philo)
{
	while (!take_fork(&philo->fork))
	{
		wait_until(philo, 50);
		if (check_if_dead())
			return (false);
	}
	protect_print(philo, "Has taken a fork");
	while (!take_fork(&all()->philos[(philo->phil_id) % all()->p_count]->fork))
	{
		wait_until(philo, 50);
		if (check_if_dead())
			return (false);
	}
	protect_print(philo, "Has taken a fork");
	return (true);
}
