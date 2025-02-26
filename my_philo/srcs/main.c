/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:02 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 13:05:46 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
		init_forks(data, i);
		data->philos[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(data->tab_th[i]), NULL, &routine,
				&(data->philos[i])) != 0)
			return (free_and_quit(data));
		i++;
	}
	monitor_and_destroy(data, monitor_thread);
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
