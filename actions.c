#include "philo.h"

void	eating(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	data = (t_data *)philo->data;
	philo->last_eat = get_time(NULL);
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d взял вилку\n", get_time(data->start), philo->number);
	printf("%ld %d ест\n", get_time(data->start), philo->number);
	pthread_mutex_unlock(data->print_mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	sleeping(void *arg)
{
	t_philo			*philo;
	t_data			*data;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d спит\n", get_time(data->start), philo->number);
	pthread_mutex_unlock(data->print_mutex);
	ft_usleep(data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	t_data			*data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d думает\n", get_time(data->start), philo->number);
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
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	data->die = 1;
	pthread_mutex_lock(data->print_mutex);
	printf("philo %d is died :(\n", philo->number);
	return (NULL);
}
