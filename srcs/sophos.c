/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:25:07 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/21 19:32:41 by mrojas-e         ###   ########.fr       */
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
	int i;
	i = 0;
	while (i != all()->p_count)
	{
		pthread_mutex_lock(&philo->fork);
		i++;
		printf("Hey its Philo No %d!\n", philo->phil_id);
		pthread_mutex_unlock(&philo->fork);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_data data;

	if (input_check(argv) && (argc == 5 || argc == 6))
		init_data(argc, argv, &data);
	else
		printf("Invalid Input!\n");
	return (0);
}