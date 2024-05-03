/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:23:26 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/03 18:40:51 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	philo_msg("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	philo_msg("is sleeping", philo, philo->id);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	philo_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->right_f);
	philo_msg("has taken a fork", philo, philo->id);
	philo->eating = 1;
	philo_msg("is eating", philo, philo->id);
	philo->num_meals += 1;
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	philo(void *philo)
{
	t_philo	*philo_data;

	philo_data = philo;
	if (philo_data->id % 2)
		usleep(1);
	while (philo_data->dead == false)
	{
		philo_eat(philo_data);
		philo_sleep(philo_data);
		philo_think(philo_data);
	}
}

