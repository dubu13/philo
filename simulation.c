/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:07:58 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/05 17:56:41 by dhasan           ###   ########.fr       */
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

	if (data->num_times_to_eat != -1)
	{
		while (i < data->num_philo)
		{
			if (philo_d[i].num_meals >= data->num_times_to_eat)
				all_ate++;
			i++;
		}
	}
	if (all_ate == data->num_philo)
	{
		pthread_mutex_lock(&philo_d->dead_lock);
		philo_d->dead = true;
		pthread_mutex_unlock(&philo_d->dead_lock);
		return (1);
	}
	return (0);
}

int	check_meal_time(t_data *data)
{
	t_philo	*philo_d;
	int		i;

	i = 0;
	philo_d = data->philo;
	while (i < data->num_philo)
	{
		if (get_time() - philo_d[i].last_meal
			>= data->time_to_die && !philo_d[i].eating)
		{
			philo_msg("died", &philo_d[i], philo_d[i].id);
			philo_d->dead = true;
		}
	}
}

void	check_simulation(t_data *data)
{
	while (1)
	{
		if (check_meal_time(data) || check_all_ate(data))
			break ;
	}
}
