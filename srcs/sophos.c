/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:25:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/07 22:55:41 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

void	*routine(void *args)
{
	t_phil	*philo;

	philo = (t_phil *) args;
	philo->last_meal = get_time(0);
	if (philo->phil_id % 2 == 1)
		wait_until(philo, get_time(0) + 10);
	while (check_if_dead() == false && eat_limit(philo) == false)
	{
		protect_print(philo, "is thinking");
		take_forks(philo);
		protect_print(philo, "is eating");
		philo->times_eaten++;
		philo->last_meal = get_time(0);
		wait_until(philo, get_time(0) + all()->t_to_eat);
		drop_forks(philo);
		protect_print(philo, "is sleeping");
		wait_until(philo, get_time(0) + all()->t_to_sleep);
	}
	return (NULL);
}

//CHECK 1 phils case PLEASE!
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
	free_all (); // ??

	return (0);
}
