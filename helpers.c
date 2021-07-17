#include "philo.h"

int	ft_atoi(const char *nptr)
{
	long long			res;
	int					min;

	min = 0;
	res = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' && nptr++)
		min = 1;
	if (*nptr == '+' && !min)
		nptr++;
	while (*nptr != '\0' && (*nptr >= 48 && *nptr <= 57))
	{
		res = res * 10 + (*nptr - 48);
		nptr++;
	}
	if (min)
		res = -res;
	if (res > 2147483647)
		return (min - 1);
	if (res < -2147483648)
		return (min - 1);
	return (res);
}

void	all_free(t_data *data)
{
	all_detach(data);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->start && data->start_tz)
	{
		free(data->start);
		free(data->start_tz);
	}
	pthread_mutex_destroy(data->print_mutex);
	pthread_mutex_destroy(data->die_mutex);
	if (data->print_mutex)
		free(data->print_mutex);
	if (data->die_mutex)
		free(data->die_mutex);
}
