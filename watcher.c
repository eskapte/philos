#include "philo.h"

void	*die_watcher(void *arg)
{
	t_data			*data;
	unsigned int	i;

	i = 0;
	data = (t_data *)arg;
	while (!data->die && i < data->n_of_philos)
	{
		if (get_time(NULL) - data->philos[i].last_eat > data->time_to_die)
		{
			pthread_mutex_lock(data->print_mutex);
			printf("%ld %d died\n", get_time(data->start),
				data->philos[i].number);
			data->die = 1;
		}
		i++;
		if (i == data->n_of_philos)
			i = 0;
	}
	return (NULL);
}
