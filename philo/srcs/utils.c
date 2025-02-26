/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:01:13 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 15:55:51 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	somme;

	i = 0;
	somme = 0;
	sign = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		somme = (somme * 10) + (str[i] - 48);
		i++;
	}
	if ((sign) == -1)
		return ((int)-somme);
	return ((int)somme);
}

unsigned long	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*case_one(t_id_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
		philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(philo->left_fork);
	usleep(philo->data->time_to_die * 1000);
	return (NULL);
}

void	monitor_and_destroy(t_data_philo *data, pthread_t monitor_thread)
{
	if (pthread_create(&monitor_thread, NULL, &monitor_routine, data) != 0)
		return (free_and_quit(data));
	join_destroy(data, monitor_thread);
	free_all(data);
}

void	free_and_quit(t_data_philo *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->stop_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	free_all(data);
	return ;
}
