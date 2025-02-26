/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:04:51 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 14:16:53 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_threads(t_data_philo *data)
{
	data->tab_th = malloc(data->nb_philo * sizeof(pthread_t));
	if (!(data->tab_th))
		return (1);
	memset(data->tab_th, 0, sizeof(data->nb_philo * sizeof(pthread_t)));
	return (0);
}

int	init_mutex(t_data_philo *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->nb_philo * sizeof(pthread_mutex_t));
	if (!(data->forks))
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->meal2_mutex, NULL);
	return (0);
}

int	init_philos(t_data_philo *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_id_philo) * data->nb_philo);
	if (!data->philos)
		return (1);
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		i++;
	}
	return (0);
}

t_data_philo	*init_data(int ac, char **av)
{
	t_data_philo	*data;

	data = malloc(sizeof(t_data_philo));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data_philo));
	data->start_time = get_ms();
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	if (init_threads(data) == 1)
		return (NULL);
	if (init_mutex(data) == 1)
		return (NULL);
	if (init_philos(data) == 1)
		return (NULL);
	data->stop = 0;
	return (data);
}

void	init_forks(t_data_philo *data, int i)
{
	pthread_mutex_t	*tmp;

	data->philos[i].left_fork = &data->forks[i];
	data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	if (data->philos[i].left_fork > data->philos[i].right_fork)
	{
		tmp = data->philos[i].left_fork;
		data->philos[i].left_fork = data->philos[i].right_fork;
		data->philos[i].right_fork = tmp;
	}
}
