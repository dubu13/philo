/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:18 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/09 21:13:57 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (1);
	while (i < data->num_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eating = 0;
		data->philo[i].num_meals = 0;
		data->philo[i].start_time = get_time();
		data->philo[i].last_meal = get_time();
		data->philo[i].right_f = &data->forks[data->philo[i].id - 1];
		if (data->philo[i].id == data->num_philo)
			data->philo[i].left_f = &data->forks[0];
		else
			data->philo[i].left_f = &data->forks[data->philo[i].id];
		i++;
	}
	return (0);
}

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (1);
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_args(int argc, char **argv, t_data *data)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = false;
	data->num_times_to_eat = -1;
	if (argc == 6)
		data->num_times_to_eat = ft_atoi(argv[5]);
	if (pthread_mutex_init(&data->dead_lock, NULL)
		|| pthread_mutex_init(&data->print_lock, NULL)
		|| pthread_mutex_init(&data->eating_lock, NULL))
		return (1);
	if (init_forks(data) || init_philo(data))
		return (1);
	return (0);
}
