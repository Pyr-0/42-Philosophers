/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initium.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:23:52 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/08 18:58:36 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

t_phil	*new_phil(int i)
{
	t_phil	*new;

	new = malloc(sizeof(t_phil));
	if (new == NULL)
		return (NULL);
	(*new).phil_id = i + 1;
	(*new).times_eaten = 0;
	(*new).fork.value = true;
	if (pthread_mutex_init(&new->fork.mtx, NULL) != 0)
		printf("Mutex was not created");
	return (new);
}

void	init_philos(void)
{
	int	i;

	i = -1;
	all()->philos = malloc(sizeof(t_phil *) * (all()->p_count + 1));
	if (all()->philos == NULL)
		return ;
	while (++i < all()->p_count)
	{
		all()->philos[i] = new_phil(i);
		if (all()->philos[i] == NULL)
			return ;
	}
	all()->philos[all()->p_count] = NULL;
	i = 0;
	while (all()->philos[i] != NULL)
	{
		if (pthread_create(&all()->philos[i]->thread_id,
				NULL, routine, all()->philos[i]) != 0)
			printf("Thread was not created");
		i++;
	}		
	join_threads();
}

bool	init_data(int argc, char **argv)
{
	if (ft_atoi(argv[1], &(all()->p_count)) == false)
		return (false);
	pthread_mutex_init(&all()->lock_state, NULL);
	pthread_mutex_init(&all()->print_state, NULL);
	all()->start_time = get_time(0);
	if (all()->p_count > 200)
	{
		printf("Error invalid amount of philos\n");
		exit (1);
	}
	if (!ft_atoi(argv[2], &(all()->t_to_die)))
		return (false);
	if (!ft_atoi(argv[3], &(all()->t_to_eat)))
		return (false);
	if (!ft_atoi(argv[4], &(all()->t_to_sleep)))
		return (false);
	if (argc == 6)
	{
		if (!ft_atoi(argv[5], &(all()->meal_limit)))
			return (false);
	}
	else
		all()->meal_limit = -1 ;
	return (true);
}
