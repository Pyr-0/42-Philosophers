/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojas-e <mrojas-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:11:09 by mrojas-e          #+#    #+#             */
/*   Updated: 2022/02/21 17:33:23 by mrojas-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// In the following code we see how threads share memory, and how 
// the actions done in one of the Threads will be reflected in the other
/* int	x = 2;
void	*routine()
{
	x++;
	//printf("Test from threads\n");
	//printf("End threads\n");
	sleep(2);
	printf("Value of x : %d\n", x);
}
void	*routine2()
{
	//printf("Test from threads\n");
	//printf("End threads\n");
	sleep(2);
	printf("Value of x : %d\n", x);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine2, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	return (0);
}
 */

// Here we will se how Race Conditions work

/* int	mails = 0 ;

void	*routine()
{
	int i;
	while(i < 100000000) // without a proper handling this 
	{                    // can generate conflict in the Critical-section
		i++;
		mails++;
		// read the values of mails
		//increment
		//write mails
	}
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	printf("Num of Mails : %d\n", mails);
	return (0);
}
 */

/* MUTEX (Mutual exclusion)

this is like a "lock" that is check if its locked or unlocked
and lets threads modify values only one at a time, making 
the other thread wait until the lock is Unlocked again.*/

/* int	mails = 0 ;
pthread_mutex_t	mutex;

void	*routine()
{
	int i;
	while(i < 1000000)
	{
		pthread_mutex_lock(&mutex); //THIS LOCKS
		i++;
		mails++;
		pthread_mutex_unlock(&mutex);// THIS UNLOCKS 
	}
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;
	pthread_mutex_init(&mutex, NULL);// MUTEX must be initialized

	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	pthread_mutex_destroy(&mutex);//... and MUTEX must be destroyed 
	printf("Num of Mails : %d\n", mails);
	return (0);
}
 */
//Here we can create multiple threads just with a loop:

int	mails = 0 ;
pthread_mutex_t	mutex;


/*static	int	checking_arg(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("Invalid arguments\n");
			return (1);
		}
	}
	return (0);
}

static	int	checking_arguments(char **argv, int argc)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (checking_arg(argv[i]))
			return (1);
	}
	return (0);
}*/

void	*routine()
{
	int i;

	i = 0;
	while(i < 1000000)
	{
		pthread_mutex_lock(&mutex); //THIS LOCKS
		i++;
		mails++;
		pthread_mutex_unlock(&mutex);// THIS UNLOCKS
	//find out how void return looks like
	}
	return (NULL);
}

/* void	to_be(t_phil *)
{
	int i;
	
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (1);
		i++;
	}
	return (NULL);
} */
/*
void	not_to_be()
{
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		printf("Philosopher %d has finished\n", i);
		i++;
	}
} */

int	main(int argc, char **argv)
{
	//t_phil	philo;
	pthread_t	th[4];
	int i;

	(void)argc;
	(void)argv;
	pthread_mutex_init(&mutex, NULL);// MUTEX must be initialized
	i = 0;
	//CREATE THE THREADS 
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (1);
		printf("Philosopher %d has started\n", i);
		i++;
	}
	i = 0;
	//END THE THREADS
	while (i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (2);
		printf("Philosopher %d has finished\n", i);
		i++;
	}
	usleep(3000);
	pthread_mutex_destroy(&mutex);//...and MUTEX must be destroyed
	printf("Num of Mails : %d\n", mails);
	return (0);
}

