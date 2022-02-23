/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:25:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/23 22:27:28 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"


void	*routine(void *args)
{
	t_phil *philo;

	philo = (t_phil *) args;

	while (philo->state != DONE && philo->state != DEAD)
	{
		/* if (get_time() >= philo->next_event)
			philo_change_state(philo); */
		//usleep(30000);
		//take_fork(&philo->fork, philo->phil_id);
		printf("%lu %d has taken a fork\n",get_time(all()->start_time), philo->phil_id);
		printf("%lu %d is eating\n",get_time(all()->start_time), philo->phil_id);
		philo->times_eaten++;
		if (all()->meal_limit <= philo->times_eaten)
			{
				philo->state = DONE;
				break ;
			}
		usleep(all()->t_to_eat * 1000);
		printf("%lu %d is sleeping\n",get_time(all()->start_time),  philo->phil_id);
		usleep(all()->t_to_sleep * 1000);
		printf("%lu %d is thinking\n",get_time(all()->start_time), philo->phil_id);
		usleep(30000);
	}
		//pthread_mutex_lock(&philo->fork);
		//pthread_mutex_unlock(&philo->fork);
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
	return (0);
}
