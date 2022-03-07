/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:48:02 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/07 22:38:24 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

bool	eat_limit(t_phil *philo)
{
	if (all()->meal_limit == -1)
		return (false);
	if (all()->meal_limit <= philo->times_eaten)
	{
		pthread_mutex_unlock(&philo->fork.mutex);
		pthread_mutex_unlock(&all()->philos[philo->phil_id % all()->p_count]->fork.mutex);
		return (true);
	}
	return (false);
}
