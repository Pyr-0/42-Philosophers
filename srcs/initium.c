/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initium.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:23:52 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/22 10:34:12 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"


void	join_threads()
{
	int i;

	i = 0;
	while (i < all()->thread_count)
	{
		if (pthread_join(all()->philos[i]->thread_id, NULL) != 0)
			printf("error\n");
		printf("Philosopher %d has finished\n", i);
		i++;
	}
}

t_phil	*new_phil(int i)
{
	t_phil	*new;
	
	new = malloc(sizeof(t_phil));
	new->phil_id = i + 1;
	if (pthread_mutex_init(&new->fork, NULL) != 0)
		printf("error");
	if (pthread_create(&new->thread_id, NULL, &routine, new))
		all()->thread_count++;
	return (new);
}

void	init_philos()
{
	int	i;

	i = -1;
	all()->philos = malloc(sizeof(t_phil) * (all()->p_count + 1));
	while (++i < all()->p_count)
		all()->philos[i] = new_phil(i);

	join_threads();
}

void	init_data(char **argv)
{
	
	all()->p_count = ft_atoi(argv[1]);
	if (all()->p_count > 200)
	{
		printf("Error\n");
		exit (1);
	}
	all()->time_to_die = ft_atoi(argv[2]);
	all()->time_to_eat = ft_atoi(argv[3]);
	all()->time_to_sleep = ft_atoi(argv[4]);
	/* if (argv == 6)
		all()->has_eaten = ft_atoi(argv[5]);
	else
		all()->has_eaten = 0; */
	init_philos();
}
