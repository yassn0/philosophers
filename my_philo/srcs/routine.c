/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:21:40 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 12:40:44 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	update_last_meal(t_id_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_ms();
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

static void	eat_routine(t_id_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken");
	update_last_meal(philo);
	print_state(philo, "is eating");
	precise_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (philo->data->nb_meals != -1)
	{
		pthread_mutex_lock(&philo->data->meal_mutex);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->data->meal_mutex);
	}
}

void	*routine(void *arg)
{
	t_id_philo	*philo;

	philo = (t_id_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		case_one(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		precise_usleep(1);
	while (1)
	{
		eat_routine(philo);
		print_state(philo, "is sleeping");
		precise_usleep(philo->data->time_to_sleep);
		print_state(philo, "is thinking");
	}
	return (NULL);
}
