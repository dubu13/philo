/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:18 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/05 17:53:11 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	creat_threads(t_data *data)
{
	int		i;
	t_philo	*c_philo;

	i = 0;
	while (i < data->num_philo)
	{
		c_philo = &data->philo[i];
		if (pthread_create(&c_philo->thread, NULL, &philo, &c_philo))
			return (mtx_destroy(data), free_data(data), error("thread"));
		i++;
	}
	i = 0;
	while (i < data->num_philo)
	{
		c_philo = &data->philo[i];
		if (pthread_join(c_philo->thread, NULL))
			return (mtx_destroy(data), free_data(data), error("thread"));
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philo)
		return (1);
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eating = 0;
		data->philo[i].num_meals = 0;
		data->philo[i].dead = false;
		data->philo[i].dead_lock = &data->dead_lock;
		data->philo[i].right_f = &data->forks[data->philo[i].id - 1];
		if (data->philo[i].id == data->num_philo)
			data->philo[i].left_f = &data->forks[0];
		else
			data->philo[i].left_f = &data->forks[data->philo[i].id];
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
	if (argc == 6)
		data->num_times_to_eat = ft_atoi(argv[5]);
	else
		data->num_times_to_eat = -1;
	if (pthread_mutex_init(&data->dead_lock, NULL))
		return (1);
	if (!init_philo(data) || !init_forks(data))
		return (1);
	return (0);
}
