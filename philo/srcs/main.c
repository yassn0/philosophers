/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:02 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/24 10:13:08 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	see_death(t_data_philo *data, int *i)
{
	unsigned long	time_since_last_meal;

	while (*i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		time_since_last_meal = get_ms() - data->philos[*i].last_meal;
		pthread_mutex_unlock(&data->meal_mutex);
		if (time_since_last_meal > (unsigned long)data->time_to_die)
		{
			printf("%lu %d died\n", get_ms() - data->start_time - 1,
				data->philos[*i].id + 1);
			pthread_mutex_lock(&data->stop_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->stop_mutex);
			return (1);
		}
		*i += 1;
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

void	*monitoring(void *arg)
{
	t_data_philo	*data;
	int				i;

	data = (t_data_philo *)arg;
	while (1)
	{
		i = 0;
		if (see_death(data, &i))
			return (NULL);
		if (data->nb_meals >= 0)
		{
			if (nb_meals_max(data))
				return (NULL);
		}
		pthread_mutex_lock(&data->stop_mutex);
		if (data->stop == 1)
		{
			pthread_mutex_unlock(&data->stop_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->stop_mutex);
		usleep(1000);
	}
	return (NULL);
}

void	philosophers(t_data_philo *data)
{
	int			i;
	pthread_t	monitor_thread;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		if (pthread_create(&(data->tab_th[i]), NULL, &routine,
				&(data->philos[i])) != 0)
			free_return(data);
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, &monitoring, data) != 0)
		free_return(data);
	join_destroy(data, monitor_thread);
	free_all(data);
}

int	main(int ac, char **av)
{
	t_data_philo	*data;

	if (ac != 5 && ac != 6)
	{
		printf("Wrong numbers of arguments\n");
		exit(1);
	}
	if (check_arg(ac, av))
		return (1);
	data = init_data(ac, av);
	if (!data)
	{
		free_all(data);
		return (1);
	}
	philosophers(data);
	return (0);
}
