/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:48:02 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/07 13:52:05 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

void	eat_limit(t_phil *philo)
{
	while (all()->meal_limit != 0)
	{
		if (all()->meal_limit <= philo->times_eaten)
		{
			philo->state = DONE;
			pthread_mutex_unlock(&philo->fork.mutex);
			pthread_mutex_unlock(&all()->philos[philo->phil_id % all()->p_count]->fork.mutex);
			break ;
		}
	}
}

/* void	rigor_mortis(t_phil *philo)
{
	pthread_mutex_lock(&all()->lock_state);
	if (get_time(0) - all()->start_last_meal > all()->t_to_die)
	{
		all()->dead = true;
		protect_print(philo->phil_id, "is dead.");
	}
	pthread_mutex_unlock(&all()->lock_state);
}
*/