#include "philo.h"

void	eating(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	if (philo->right)
	{
		pthread_mutex_lock(philo->right);
		printf("%ld %d has taken a fork\n", get_time(data->start),
			   philo->number);
	}
	if (philo->left)
	{
		pthread_mutex_lock(philo->left);
		printf("%ld %d has taken a fork\n", get_time(data->start),
			   philo->number);
	}
	pthread_mutex_lock(data->print_mutex);
	if (philo->right && philo->left)
	{
		printf("%ld %d is eating\n", get_time(data->start), philo->number);
		philo->last_eat = get_time(NULL);
		philo->time_eats++;
	}
	pthread_mutex_unlock(data->print_mutex);
	ft_usleep(data->time_to_eat);
	if (philo->right)
		pthread_mutex_unlock(philo->right);
	if (philo->left)
		pthread_mutex_unlock(philo->left);
}

void	sleeping(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d is sleeping\n", get_time(data->start), philo->number);
	pthread_mutex_unlock(data->print_mutex);
	ft_usleep(data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	t_data			*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d is thinking\n", get_time(data->start), philo->number);
	pthread_mutex_unlock(data->print_mutex);
}

void	*actions(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	philo->last_eat = get_time(NULL);
	while (get_time(NULL) - philo->last_eat < data->time_to_die
		&& !data->die)
	{
		if (data->count_eats >= 0 && philo->time_eats >= data->count_eats)
		{
			pthread_detach(philo->thread);
			data->finished++;
			if (data->finished >= data->n_of_philos)
				pthread_mutex_unlock(data->die_mutex);
			return (NULL);
		}
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	data->die = 1;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d died\n", get_time(data->start), philo->number);
	pthread_mutex_unlock(data->die_mutex);
	return (NULL);
}
