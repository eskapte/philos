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
	if (data->n_of_philos < 10 || data->time_to_die < 10 || data->time_to_eat
		< 10 || data->time_to_sleep < 10)
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
	while (i < (int)data->n_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		if (i == 0)
			data->philos[i].right = &data->forks[data->n_of_philos - 1];
		else
			data->philos[i].right = &data->forks[i - 1];
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
	gettimeofday(data->start, NULL);
	while (1)
	{
		i = 0;
		while (i < data->n_of_philos)
		{
			pthread_create(&data->philos[i].thread, NULL, actions,
				  (void *) &data->philos[i]);
			i++;
		}
		i = 0;
		while (i < data->n_of_philos)
			pthread_join(data->philos[i++].thread, (void **) NULL);
	}
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
	pthread_mutex_init(data.print_mutex, NULL);
	simulation(&data);
}
