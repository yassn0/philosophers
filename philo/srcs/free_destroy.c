/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:50:01 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/24 10:10:35 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	join_destroy(t_data_philo *data, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->tab_th[i], NULL);
		i++;
	}
	i = 0;
	pthread_join(monitor_thread, NULL);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->meal2_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}

void	free_all(t_data_philo *data)
{
	int	i;

	i = 0;
	if (data->tab_th)
		free(data->tab_th);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data)
		free(data);
}
