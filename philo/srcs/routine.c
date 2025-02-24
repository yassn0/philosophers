/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:21:40 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/24 11:27:40 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	take_left_forks(t_id_philo *philo)
{
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(philo->left_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo))
		printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
			philo->id + 1);
	else
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	take_right_forks(t_id_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo))
		printf("%lu %d has taken a fork\n", get_ms() - philo->data->start_time,
			philo->id + 1);
	else
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	eat(t_id_philo *philo)
{
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_ms();
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo))
		printf("%lu %d is eating\n", get_ms() - philo->data->start_time,
			philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	sleep_and_think(t_id_philo *philo)
{
	if (check_death(philo))
		return (1);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_death(philo))
		printf("%lu %d is sleeping\n", get_ms() - philo->data->start_time,
			philo->id + 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (check_death(philo))
		return (1);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lu %d is thinking\n", get_ms() - philo->data->start_time, philo->id
		+ 1);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

void	*routine(void *arg)
{
	t_id_philo	*philo;

	philo = (t_id_philo *)arg;
	if (case_one(philo) == 1)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		// if (take_left_forks(philo))
		// 	return (NULL);
		// if (take_right_forks(philo))
		// 	return (NULL);
		if (take_left_forks(philo))
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (sleep_and_think(philo))
			return (NULL);
	}
	return (NULL);
}
