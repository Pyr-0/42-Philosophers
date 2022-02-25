/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:25:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/25 18:51:23 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"


void	*routine(void *args)
{
	t_phil	*philo;

	philo = (t_phil *) args;
	while (philo->state != DONE && philo->state != DEAD)
	{
		if (!(philo->phil_id % 2))// this works only w 2 philos, its a workaround 
			usleep(100);
		take_fork(philo);
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
	return (NULL);
}

//CHECK 0 & 1 phils case PLEASE!
int main(int argc, char **argv)
{
	if (input_check(argv) && (argc == 5 || argc == 6))
	{
		if (init_data(argc, argv))
			init_philos();
		else
		printf("Invalid Input!\n");
	}
	else
		printf("Invalid Input!\n");
	free_all(); // ??
	return (0);
}
