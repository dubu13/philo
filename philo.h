/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:39:44 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/05 17:49:58 by dhasan           ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	bool			eating;
	long			num_meals;
	long			last_meal;
	bool			dead;
	t_data			*data;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*dead_lock;
}							t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	long			start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
}							t_data;

//utils.c
int				ft_strlen(const char *str);
void			ft_sleep(t_philo *philo, unsigned int time);
unsigned int	get_time(void);
int				is_digit(const char *str);
int				ft_atoi(const char *str);

//init
int				creat_threads(t_data *data);
int				init_args(int argc, char **argv, t_data *data);

//philo.c
void			*philo(void *philo);

//error.c
int				error(char *msg);
void			mtx_destroy(t_data *data);
void			free_data(t_data *data);
void			philo_msg(char *msg, t_philo *philo, int id);

#endif
