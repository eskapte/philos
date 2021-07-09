#include "philo.h"

void 	ft_usleep(unsigned int milliseconds)
{
	usleep(milliseconds * 1000);
}

void absa(void)
{
	int 			cnt = 10;
	t_philo			philos[cnt];
	pthread_mutex_t	forks[cnt];
	int 			i;

	i = 0;
	while (i < cnt)
	{
		pthread_mutex_init(&forks[i], NULL);
		if (i == 0)
			philos[i].right = &forks[cnt - 1];
		else
			philos[i].right = &forks[i - 1];
		philos[i].left = &forks[i];
		philos[i].number = i;
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < cnt)
		{
			pthread_create(&philos[i].thread, NULL, eat, (void *) &philos[i]);
			i++;
		}
		i = 0;
		while (i < cnt)
		{
			pthread_join(philos[i].thread, (void **)NULL);
			i++;
		}
		pthread_detach(philos[i].thread);
	}
}

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
	if (data->n_of_philos > 60000 || data->time_to_die > 600000
		|| data->time_to_eat > 60000 || data->time_to_sleep > 60000)
		return (-1);
	return (1);
}

void	simulation(t_data *data)
{
	t_philo			*philos;
	pthread_mutex_t *forks;
	int 			i;

	i = 0;
	philos = (t_philo *)malloc(sizeof(t_philo) * data->n_of_philos);
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *
			data->n_of_philos);
	while (i < data->n_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		if (i == 0)
			philos[i].right = &forks[data->n_of_philos - 1];
		else
			philos[i].right = &forks[i - 1];
		philos[i].left = &forks[i];
		philos[i].number = i + 1;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data			data;

	if (argc < 5 || argc > 6)
		return (0);
	data.status = check_data(&data, argv, argc);
	if (data.status == -1)
		return (0);
	simulation(&data);
}
