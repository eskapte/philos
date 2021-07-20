#include "philo.h"

short	check_data(t_data *data, char *argv[], int argc)
{
	data->n_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
	{
		data->count_eats = ft_atoi(argv[5]);
		if (data->count_eats < 1 || data->count_eats > 300)
			return (-1);
	}
	else
		data->count_eats = -1;
	if (data->n_of_philos < 1 || data->time_to_die < 60 || data->time_to_eat
		< 60 || data->time_to_sleep < 60)
		return (-1);
	if (data->n_of_philos > 200 || data->time_to_die > 600000
		|| data->time_to_eat > 60000 || data->time_to_sleep > 60000)
		return (-1);
	return (1);
}

void	philos_init(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->n_of_philos);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->n_of_philos);
	data->die = 0;
	while (i < (int)data->n_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].time_eats = 0;
		if (data->n_of_philos > 1)
		{
			if (i == 0)
				data->philos[i].right = &data->forks[data->n_of_philos - 1];
			else
				data->philos[i].right = &data->forks[i - 1];
		}
		else
			data->philos[i].right = NULL;
		data->philos[i].left = &data->forks[i];
		data->philos[i].number = i + 1;
		data->philos[i].data = (void *)data;
		i++;
	}
}

void	simulation(t_data *data)
{
	unsigned int	i;

	philos_init(data);
	data->start = (struct timeval *)malloc(sizeof(struct timeval));
	data->start_tz = (struct timezone *)malloc(sizeof(struct timezone));
	if (!data->start || !data->start_tz)
	{
		all_free(data);
		return ;
	}
	gettimeofday(data->start, data->start_tz);
	i = 0;
	while (i < data->n_of_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, actions,
			(void *) &data->philos[i]);
		pthread_detach(data->philos[i].thread);
		i++;
	}
	ft_usleep(30);
	pthread_create(&data->watcher, NULL, die_watcher, (void *)data);
}

int	main(int argc, char *argv[])
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (0);
	data.correct = check_data(&data, argv, argc);
	if (data.correct == -1)
		return (0);
	data.die = 0;
	data.finished = 0;
	data.print_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data.print_mutex, NULL);
	simulation(&data);
	pthread_join(data.watcher, NULL);
	pthread_detach(data.watcher);
	all_free(&data);
	return (0);
}
