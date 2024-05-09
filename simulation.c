/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:07:58 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/09 21:21:28 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ate(t_data *data)
{
	t_philo	*philo_d;
	int		i;
	int		all_ate;

	i = 0;
	all_ate = 0;
	philo_d = data->philo;
	if (data->num_times_to_eat == -1)
		return (0);
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->eating_lock);
		if (philo_d[i].num_meals >= data->num_times_to_eat)
			all_ate++;
		pthread_mutex_unlock(&data->eating_lock);
		i++;
	}
	if (all_ate == data->num_philo)
		return (1);
	return (0);
}

int	check_meal_time(t_data *data)
{
	t_philo			*philo_d;
	int				i;
	unsigned int	now;

	i = 0;
	philo_d = data->philo;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&data->eating_lock);
		now = get_time();
		if (now - philo_d[i].last_meal
			>= data->time_to_die && philo_d[i].eating == false)
		{
			pthread_mutex_unlock(&data->eating_lock);
			philo_msg("died", &philo_d[i], philo_d[i].id);
			return (1);
		}
		pthread_mutex_unlock(&data->eating_lock);
		i++;
	}
	return (0);
}

void	dead_check(t_data *data)
{
	while (data->dead == false)
	{
		if (check_meal_time(data) || check_all_ate(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead = true;
			pthread_mutex_unlock(&data->dead_lock);
			break ;
		}
	}
}

int	simulation(t_data *data)
{
	int		i;
	t_philo	*philo_data;

	i = 0;
	while (i < data->num_philo)
	{
		philo_data = &data->philo[i];
		if (pthread_create(&philo_data->thread, NULL, &philo, philo_data))
			return (finish(data, true), error("in threads"));
		i++;
	}
	dead_check(data);
	i = 0;
	while (i < data->num_philo)
	{
		philo_data = &data->philo[i];
		if (pthread_join(philo_data->thread, NULL))
			return (finish(data, true), error("in threads"));
		i++;
	}
	finish(data, true);
	return (0);
}
