/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfradj <yfradj@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:12:55 by yfradj            #+#    #+#             */
/*   Updated: 2025/02/26 16:00:39 by yfradj           ###   ########.fr       */
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
	int					dead_flag;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		dead_lock;

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
	pthread_mutex_t		meal_mutex;
	t_data_philo		*data;
}						t_id_philo;

int						ft_atoi(const char *str);
int						check_arg(int ac, char **av);
t_data_philo			*init_data(int ac, char **av);
unsigned long			get_ms(void);
void					*routine(void *arg);
void					join_destroy(t_data_philo *data,
							pthread_t monitor_thread);
void					free_all(t_data_philo *data);
void					*case_one(t_id_philo *philo);
void					monitor_and_destroy(t_data_philo *data,
							pthread_t monitor_thread);
void					free_and_quit(t_data_philo *data);
void					init_forks(t_data_philo *data, int i);
void					*monitor_routine(void *arg);
void					precise_usleep(time_t milliseconds, t_data_philo *data);
void					print_status(t_id_philo *philo, char *status);
int						simulation_ended(t_data_philo *data);

#endif