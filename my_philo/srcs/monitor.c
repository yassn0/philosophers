#include "../include/philosophers.h"

int	philo_died(t_id_philo *philo)
{
	time_t	time;

	time = get_ms();
	if ((time - philo->last_meal) > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->dead_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		print_state(philo, "is dead");
		return (1);
	}
	return (0);
}

int	nb_meals_max(t_data_philo *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (i < data->nb_philo)
	{
		if (data->philos[i].meals_eaten < data->nb_meals)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			return (0);
		}
		i++;
	}
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_mutex_unlock(&data->meal_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data_philo	*data;
	int				i;

	data = (t_data_philo *)arg;
	while (!simulation_ended(data))
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (philo_died(&data->philos[i]))
			{
				pthread_mutex_unlock(&data->meal_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->meal_mutex);
		}
		if (data->nb_meals >= 0)
		{
			if (nb_meals_max(data))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	check_meals_completed(t_data_philo *data)
{
	int	i;
	int	all_meals_eaten;

	i = -1;
	all_meals_eaten = 1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->nb_meals)
			all_meals_eaten = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		if (!all_meals_eaten)
			break ;
	}
	if (all_meals_eaten)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
		return (1);
	}
	return (0);
}

int	simulation_ended(t_data_philo *data)
{
	int	stopped;
	int	dead;

	pthread_mutex_lock(&data->stop_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	pthread_mutex_lock(&data->dead_lock);
	dead = data->dead_flag;
	pthread_mutex_unlock(&data->dead_lock);
	if (dead == 1 || stopped == 1)
		return (1);
	return (0);
}
