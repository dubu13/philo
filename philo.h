/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:39:44 by dhasan            #+#    #+#             */
/*   Updated: 2024/04/30 17:54:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				id;
	long			num_meals;
	bool			dead;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
}							t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_times_to_eat;
	pthread_mutex_t	*forks; //arry for forks(mutex)
	t_philo			*philo; //arry for philos(thread)
}							t_data;

//utils.c
int	is_digit(const char *str);
int	ft_atoi(const char *str);

//init
int	init_args(int argc, char **argv, t_data *data);

#endif
