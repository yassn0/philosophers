/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:45:27 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 11:45:39 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_state(t_id_philo *philo, char *state)
{
	time_t	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_ms() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id + 1, state);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	precise_usleep(time_t milliseconds)
{
	time_t	start;

	start = get_ms();
	while ((get_ms() - start) < milliseconds)
		usleep(500);
}