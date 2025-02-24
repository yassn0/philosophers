/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:12:55 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/24 11:28:59 by yfradj           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data_philo
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_meals;

	unsigned long		start_time;
	int					stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		meal2_mutex;

	pthread_t			*tab_th;
	struct s_id_philo	*philos;
}						t_data_philo;

typedef struct s_id_philo
{
	int					id;
	int					meals_eaten;
	unsigned long		last_meal;

	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data_philo		*data;
}						t_id_philo;

int						ft_atoi(const char *str);
int						check_arg(int ac, char **av);
t_data_philo			*init_data(int ac, char **av);
unsigned long			get_ms(void);
void					*routine(void *arg);
int						check_death(t_id_philo *philos);
void					join_destroy(t_data_philo *data,
							pthread_t monitor_thread);
void					free_all(t_data_philo *data);
int						case_one(t_id_philo *philos);
int						take_right_forks(t_id_philo *philo);
int						take_left_forks(t_id_philo *philo);
void					free_return(t_data_philo *data);

#endif