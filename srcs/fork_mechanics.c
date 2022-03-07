/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_mechanics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 13:01:20 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/07 14:49:32 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sophos.h>

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

void	drop_forks(t_phil *philo)
{
	drop_fork(&philo->fork);
	drop_fork(&all()->philos[philo->phil_id % all()->p_count]->fork);
}

void	take_forks(t_phil *philo)
{
	take_fork(&philo->fork);
	protect_print(philo, "Has taken a fork");
	take_fork(&all()->philos[(philo->phil_id) % all()->p_count]->fork);
	protect_print(philo, "Has taken a fork");
	/*protect_print(philo, "Is eating");
	philo->times_eaten++;
	philo_sleeps(all()->t_to_sleep);
	//usleep(200000);
	get_time(all()->start_last_meal);*/
}
