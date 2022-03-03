/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initium.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satori <satori@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:23:52 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/02 12:24:01 by satori           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

void	join_threads()
{
	int i;

	i = 0;
	while (i < all()->p_count)
	{
		if (pthread_join(all()->philos[i]->thread_id, NULL) != 0)
			printf("error\n");
		//usleep(3000);
		printf("%lu Philosopher %d has finished\n",get_time(all()->start_time), i);
		i++;
	}
}

void	free_all()
{
	int i;

	if (all()->philos == NULL)
		return ;
	i = -1;
	while (all()->philos[++i] != NULL)
		free(all()->philos[i]);
	free (all()->philos);
}

t_phil	*new_phil(int i)
{
	t_phil	*new;
	
	new = malloc(sizeof(t_phil));
	if (new == NULL)
		return (NULL);
	(*new).phil_id = i + 1;
	(*new).state = READY;
	(*new).times_eaten = 0;
	if (pthread_mutex_init(&new->fork.mutex, NULL) != 0)
		printf("Mutex was not created"); // program must end 
	if (pthread_create(&new->thread_id, NULL, &routine, new) != 0)
		printf("Thread was not created");// progrma must end 
	return (new);
}

void	init_philos()
{
	int	i;

	i = -1;
	all()->philos = malloc(sizeof(t_phil) * (all()->p_count + 1));
	if(all()->philos == NULL)
		return ;
	while (++i < all()->p_count)
	{
		all()->philos[i] = new_phil(i);
		if(all()->philos[i] == NULL)
			return ;
	}
	all()->philos[all()->p_count] = NULL;
	join_threads();
}


bool	init_data(int argc, char **argv)
{
	if (ft_atoi(argv[1], &(all()->p_count)) == false)
		return (false);
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
		all()->meal_limit = 0; 
	return (true);
}
