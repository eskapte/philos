#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	int				number;
	int				time_eats;
	long			last_eat;
	void			*data;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	unsigned int	finished;
	struct timeval	*start;
	struct timezone	*start_tz;
	unsigned int	n_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				count_eats;
	int				correct;
	int				die;
	pthread_mutex_t	*print_mutex;
	pthread_t		watcher;
}					t_data;

int		ft_atoi(const char *nptr);
void	ft_usleep(unsigned int milliseconds);
void	*actions(void *arg);
long	get_time(struct timeval *time);
void	all_free(t_data *data);
void	*die_watcher(void *arg);

#endif
