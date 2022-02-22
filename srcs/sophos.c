/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:25:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/22 12:58:03 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sophos.h"

bool	input_check(char **argv)
{
	int	i;
	int j;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '0')
			(false);
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

t_data	*all(void)
{
	static t_data all;

	return (&all);
}

void	*routine(void *args)
{
	t_phil *philo;

	philo = (t_phil *)args;

	//pthread_mutex_lock(&philo->fork);
	while(all()->p_count)
	{
		printf("Philo %d is eating\n", philo->phil_id);
		printf("Philo %d is sleeping\n", philo->phil_id);
	}
	//pthread_mutex_unlock(&philo->fork);
	return (NULL);
}
//MAX INT CHECK PLEASE! 
int main(int argc, char **argv)
{
	if (input_check(argv) && (argc == 5 || argc == 6))
		init_data(argc, argv);
	else
		printf("Invalid Input!\n");
	return (0);
}