/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:45:27 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 15:38:55 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_status(t_id_philo *philo, char *status)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->stop_mutex);
	if (!philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->stop_mutex);
		pthread_mutex_lock(&philo->data->print_mutex);
		time = get_ms() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id + 1, status);
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->stop_mutex);
}

void	precise_usleep(time_t milliseconds, t_data_philo *data)
{
	time_t start;
	time_t elapsed;

	start = get_ms();
	while ((elapsed = get_ms() - start) < milliseconds)
	{
		if (elapsed >= milliseconds)
			break ;
		usleep(500);
		if (simulation_ended(data))
			break ;
	}
}
