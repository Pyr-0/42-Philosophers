/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initium.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:23:52 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/22 13:56:36 by mrojas-e         ###   ########.fr       */
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

void	free_all()
{
	int i;

	if(all()->philos == NULL)
		return ;
	i = -1;
	while(all()->philos[++i] != NULL)
		free(all()->philos[i]);
	free(all()->philos);
}

t_phil	*new_phil(int i)
{
	t_phil	*new;
	
	new = malloc(sizeof(t_phil));
	if(new == NULL)
		return (NULL);
	new->phil_id = i + 1;
	if (pthread_mutex_init(&new->fork, NULL) != 0)
		printf("Mutex was not created");
	if (pthread_create(&new->thread_id, NULL, &routine, new))
		all()->thread_count++; // what this!?
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


void	init_data(int argc, char **argv)
{
	all()->p_count = ft_atoi(argv[1]);	
	printf("Philos are :%d\n",all()->p_count);
	if (all()->p_count > 200)
	{
		printf("Error invalid amount of philos\n");
		exit (1);
	}
	all()->time_to_die = ft_atoi(argv[2]);
	all()->time_to_eat = ft_atoi(argv[3]);
	all()->time_to_sleep = ft_atoi(argv[4]);
	printf("Die is :%d\n",all()->time_to_die);//
	printf("Eat is :%d\n",all()->time_to_eat);//
	printf("Sleep is :%d\n",all()->time_to_sleep);//
	if (argc == 6)
		all()->times_eaten = ft_atoi(argv[5]);
	else
		all()->times_eaten = 0; // how to handle !!?
	
	printf("Times eaten is : %d\n",all()->times_eaten);//
	init_philos();
}

void	free_data(void)
{
	int	i;

	i = -1;
	while (++i < all()->threads_num)
	{
		if (pthread_mutex_destroy(&all()->philos[i]->lock_fork) != 0)
			printf("Couldn't destroy Mutex");
	}
	if (pthread_mutex_destroy(&all()->print) != 0)
		printf("Couldn't destroy Mutex");
	if (pthread_mutex_destroy(&all()->init_lock) != 0)
		printf("Couldn't destroy Mutex");
	i = -1;
	while (++i < all()->threads_num)
	{
		free(all()->philos[i]);
		all()->philos[i] = NULL;
	}
	free(all()->philos);
	all()->philos = NULL;
}