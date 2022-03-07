/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veritas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:23:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/07 15:36:49 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

void	protect_print(t_phil *philo, const char *message)
{
	pthread_mutex_lock(&all()->print_state);
	pthread_mutex_lock(&all()->lock_state);
	if (all()->dead == false)
		printf("%lu %d %s\n", get_time(all()->start_time),
				philo->phil_id, message);
	pthread_mutex_unlock(&all()->lock_state);
	pthread_mutex_unlock(&all()->print_state);
	
}

void	wait_until(t_phil *philo, unsigned long time)
{
	unsigned long	current_time;

	while (1)
	{
		current_time = get_time(0);
		if(current_time >= philo->last_meal + (unsigned long)all()->t_to_die)
		{
			pthread_mutex_lock(&all()->print_state);
			pthread_mutex_lock(&all()->lock_state);
			if (all()->dead == false)
			{
				all()->dead = true;
				pthread_mutex_unlock(&all()->lock_state);
				printf("%lu %d %s\n",
					get_time(all()->start_time), philo->phil_id, "is dead");
			}
			pthread_mutex_unlock(&all()->print_state);
			break;
		}
		if (time <= current_time)
			break ;
		//rigor_mortis(philo);
		usleep(50);
	}
}

/* void	has_philo_died(t_phil *philo)
{
	all()->start_last_meal = get_time(0);
	pthread_mutex_lock(&all()->lock_state);
	if (get_time(all()->start_last_meal) >= philo->times_eaten + all()->t_to_die)
	{
		all()->dead = true;
	}
	pthread_mutex_unlock(&all()->lock_state); 
} */

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
