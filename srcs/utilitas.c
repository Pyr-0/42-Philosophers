/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitas.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:44:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/08 19:32:56 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

unsigned long	get_time(unsigned long begin_time)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000) - begin_time);
}

t_data	*all(void)
{
	static t_data	all;

	return (&all);
}

bool	eat_limit(t_phil *philo)
{
	pthread_mutex_t	*temp;

	temp = &all()->philos[philo->phil_id % all()->p_count]->fork.mtx;
	if (all()->meal_limit == -1)
		return (false);
	if (all()->meal_limit <= philo->times_eaten)
	{
		pthread_mutex_unlock(&philo->fork.mtx);
		pthread_mutex_unlock(temp);
		return (true);
	}
	return (false);
}

void	join_threads(void)
{
	int	i;

	i = 0;
	while (i < all()->p_count)
	{
		if (pthread_join(all()->philos[i]->thread_id, NULL) != 0)
			printf("Join error\n");
		i++;
	}
}

void	free_all(void)
{
	int	i;

	if (all()->philos == NULL)
		return ;
	i = -1;
	while (all()->philos[++i] != NULL)
		free(all()->philos[i]);
	free (all()->philos);
}
