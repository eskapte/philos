#include "philo.h"

void	*ft_eat(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	printf("philo %d is eating\n", philo->number);
	usleep(2000000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (NULL);
}

void	*ft_sleep(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->right);
	pthread_mutex_lock(philo->left);
	printf("philo %d is sleeping\n", philo->number);
	usleep(2000000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (NULL);
}
