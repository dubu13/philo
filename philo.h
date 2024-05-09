/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:39:44 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/09 21:21:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	bool			dead;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
}							t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			eating;
	long			num_meals;
	long			last_meal;
	long			start_time;
	t_data			*data;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
}							t_philo;

int				ft_strlen(const char *str);
void			ft_sleep(unsigned int time);
unsigned int	get_time(void);
int				is_digit(const char *str);
int				ft_atoi(const char *str);

int				init_args(int argc, char **argv, t_data *data);

void			*philo(void *philo);

int				simulation(t_data *data);

int				error(char *msg);
void			finish(t_data *data, bool all);
void			philo_msg(char *msg, t_philo *philo, int id);

#endif
