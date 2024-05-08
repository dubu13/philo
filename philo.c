/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:23:26 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/08 23:11:58 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	dead(t_philo *philo)
// {
// 	printf("philo->dead: %d\n", philo->dead);
// 	pthread_mutex_lock(&philo->data->dead_lock);
// 	if (philo->dead == true)
// 		return (pthread_mutex_unlock(&philo->data->dead_lock), 1);
// 	pthread_mutex_unlock(&philo->data->dead_lock);
// 	return (0);
// }

void	philo_think(t_philo *philo)
{
	philo_msg("is thinking", philo, philo->id);
}

void	philo_sleep(t_philo *philo)
{
	philo_msg("is sleeping", philo, philo->id);
	ft_sleep(philo->data->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_f);
	philo_msg("has taken a fork", philo, philo->id);
	pthread_mutex_lock(philo->right_f);
	philo_msg("has taken a fork", philo, philo->id);
	philo->eating = true;
	philo_msg("is eating", philo, philo->id);
	philo->num_meals += 1;
	ft_sleep(philo->data->time_to_eat);
	philo->last_meal = get_time();
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
		ft_sleep(philo_data->data->time_to_die);
		pthread_mutex_unlock(philo_data->left_f);
		return (0);
	}
	if (philo_data->id % 2)
		ft_sleep(philo_data->data->time_to_eat);
	while (philo_data->dead == false)
	{
		philo_eat(philo_data);
		philo_sleep(philo_data);
		philo_think(philo_data);
	}
	return (NULL);
}
