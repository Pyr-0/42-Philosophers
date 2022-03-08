/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:26:52 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/03/08 19:48:34 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOPHOS_H
# define SOPHOS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_fork{
	bool			value;
	pthread_mutex_t	mtx;
}	t_fork;

typedef struct s_phil{
	pthread_t		thread_id;
	int				phil_id;
	int				state;
	int				times_eaten;
	struct s_fork	fork;
	unsigned long	start_timep;
	unsigned long	last_meal;
}	t_phil;

typedef struct s_data{
	pthread_mutex_t	lock_state;
	pthread_mutex_t	print_state;
	int				p_count;
	int				thread_count;
	bool			dead;
	int				t_to_eat;
	int				t_to_die;
	int				t_to_sleep;
	int				meal_limit;
	unsigned long	start_time;
	t_phil			**philos;
}	t_data;

t_data			*all(void);
bool			ft_atoi(const char *str, int *res);
bool			init_data(int argc, char **argv);
bool			take_fork(t_fork *fork);
bool			check_if_dead(void);
bool			take_forks(t_phil *philo);
bool			input_check(char **argv);
bool			eat_limit(t_phil *philo);
int				initium(int argc, char **argv, t_data *data);
void			*routine(void *args);
void			init_philos(void);
void			free_all(void);
void			drop_fork(t_fork *fork);
void			drop_forks(t_phil *philo);
void			join_threads(void);
void			protect_print(t_phil *philo, const char *message);
void			wait_until(t_phil *philo, unsigned long time);
void			rigor_mortis(t_phil *philo);
unsigned long	get_time(unsigned long begin_time);

#endif
