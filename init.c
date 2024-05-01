/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:34:18 by dhasan            #+#    #+#             */
/*   Updated: 2024/04/30 18:45:44 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//need function for simulation
//idea-> to avoid dead_lock,  philos w odd num'll sleep (time to eat / 2)
//w even num'll eat
int	creat_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_creat(&data->philo[i], NULL, (func), (arg if func have one else NULL)));
			return (write(2, "Error: creating thread\n", 24), 1);
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
		return (write(2, "Error: at malloc\n", 18), 1);
	while (i < data->num_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].num_meals = 0;
		data->philo[i].dead = false;
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
		return (free(data->philo), 1);
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (write(2, "Error: mutex_init\n", 19), 1);
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
	init_philo(data);
	init_forks(data);
	return (0);
}
