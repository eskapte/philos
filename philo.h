#ifndef PHILO_PHILO_H
#define PHILO_PHILO_H

// memset, printf, malloc, free, write,
//usleep, gettimeofday, pthread_create,
//pthread_detach, pthread_join, pthread_mutex_init,
//pthread_mutex_destroy, pthread_mutex_lock,
//pthread_mutex_unlock

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>

typedef struct 		s_philo
{
	pthread_t 		thread;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	int 			number;
	int 			status;
	int 			time_eats;
}					t_philo;

typedef struct		s_data
{
	unsigned int	n_of_philos;
	unsigned int 	time_to_die;
	unsigned int 	time_to_eat;
	unsigned int 	time_to_sleep;
	int				count_eats;
	int				status;
}					t_data;

int	ft_atoi(const char *nptr);

#endif
