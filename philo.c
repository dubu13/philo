/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:23:26 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/10 16:34:27 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	long	tt_think;

	if (philo->data->num_philo % 2)
	{
		tt_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
		if (tt_think < 0)
			tt_think = 0;
		ft_sleep(tt_think, philo->data);
	}
	philo_msg("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	philo_msg("is sleeping", philo, philo->id);
	ft_sleep(philo->data->time_to_sleep, philo->data);
}

int	dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead == true)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	philo_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->right_f);
	philo_msg("has taken a fork", philo, philo->id);
	philo->eating = true;
	philo_msg("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->data->eating_lock);
	philo->last_meal = get_time();
	philo->num_meals += 1;
	pthread_mutex_unlock(&philo->data->eating_lock);
	ft_sleep(philo->data->time_to_eat, philo->data);
	philo->eating = false;
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	*philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = philo;
	philo_data->start_time = get_time();
	if (philo_data->data->num_philo == 1)
	{
		pthread_mutex_lock(philo_data->left_f);
		philo_msg("has taken a fork", philo_data, philo_data->id);
		ft_sleep(philo_data->data->time_to_die, philo_data->data);
		pthread_mutex_unlock(philo_data->left_f);
		return (0);
	}
	if (philo_data->id % 2)
		ft_sleep(philo_data->data->time_to_eat, philo_data->data);
	while (philo_data->data->dead == false)
	{
		philo_eat(philo_data);
		philo_sleep(philo_data);
		philo_think(philo_data);
	}
	return (NULL);
}
