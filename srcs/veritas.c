/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veritas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:23:12 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/07 21:58:31 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

void	protect_print(t_phil *philo, const char *message)
{
	pthread_mutex_lock(&all()->print_state);
	pthread_mutex_lock(&all()->lock_state);
	if (all()->dead == false )
		printf("%lu %d %s\n", get_time(all()->start_time),
				philo->phil_id, message);
	pthread_mutex_unlock(&all()->lock_state);
	pthread_mutex_unlock(&all()->print_state);
}

static void	rigor_mortis(t_phil *philo)
{
	if (all()->dead == false)
		{
			pthread_mutex_lock(&all()->lock_state);
			all()->dead = true;
			pthread_mutex_unlock(&all()->lock_state);
			printf("%lu %d %s\n",
				get_time(all()->start_time), philo->phil_id, "is dead");
		}
}

void	wait_until(t_phil *philo, unsigned long time)
{
	unsigned long	current_time;

	while (1)
	{
		current_time = get_time(0);
		if (current_time >= philo->last_meal + (unsigned long)all()->t_to_die)
		{
			pthread_mutex_lock(&all()->print_state);
			pthread_mutex_lock(&all()->lock_state);
			rigor_mortis(philo);
			pthread_mutex_unlock(&all()->print_state);
			break;
		}
		if (time <= current_time)
			break ;
		usleep(50);
	}
}

bool	check_if_dead(void)
{
	bool	temp;
	
	pthread_mutex_lock(&all()->lock_state);
	temp = all()->dead;
	pthread_mutex_unlock(&all()->lock_state);
	return (temp);
}

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
