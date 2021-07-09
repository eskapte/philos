#include "philo.h"

void	eating(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	long			del_time;
	struct timeval	cur_time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	data = (t_data *)philo->data;
	gettimeofday(&cur_time, NULL);
	del_time = (cur_time.tv_usec - data->start->tv_usec) * 1000;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d взял вилку\n", del_time, philo->number);
	del_time = (cur_time.tv_usec - data->start->tv_usec) * 1000;
	printf("%ld %d ест\n", del_time, philo->number);
	pthread_mutex_unlock(data->print_mutex);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	sleeping(void *arg)
{
	t_philo			*philo;
	t_data			*data;
	long			del_time;
	struct timeval	cur_time;

	philo = (t_philo *)arg;
	data = (t_data *)philo->data;
	gettimeofday(&cur_time, NULL);
	del_time = (cur_time.tv_usec - data->start->tv_usec) * 1000;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d спит\n", del_time, philo->number);
	pthread_mutex_unlock(data->print_mutex);
	ft_usleep(data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	t_data			*data;
	long			del_time;
	struct timeval	cur_time;

	data = (t_data *)philo->data;
	gettimeofday(&cur_time, NULL);
	del_time = (cur_time.tv_usec - data->start->tv_usec) * 1000;
	pthread_mutex_lock(data->print_mutex);
	printf("%ld %d думает\n", del_time, philo->number);
	pthread_mutex_unlock(data->print_mutex);
}

void	*actions(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	eating(philo);
	sleeping(philo);
	thinking(philo);
}
