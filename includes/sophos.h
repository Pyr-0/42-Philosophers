/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:26:52 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/22 11:56:21 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_phil{
	pthread_mutex_t	fork;
	pthread_t		thread_id;
	int				phil_id;
}	t_phil;

typedef struct s_data{
	pthread_mutex_t init;
	int				p_count;
	int				thread_count;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				start_time;
	int				has_eaten;
	t_phil			**philos;
}	t_data;


t_data			*all(void);
int				initium(int argc, char **argv, t_data *data);
int				ft_atoi(const char *str);
unsigned long	get_time(ssize_t begin_time);
void			*routine();
void			init_philos();
void			init_data(int argc, char **argv);
void				free_all();


#endif