/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:33:21 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/09 21:18:03 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

void	finish(t_data *data, bool all)
{
	int	i;

	i = 0;
	if (all)
	{
		while (i < data->num_philo)
		{
			pthread_mutex_destroy(&(data->forks[i]));
			i++;
		}
		pthread_mutex_destroy(&data->dead_lock);
		pthread_mutex_destroy(&data->print_lock);
		pthread_mutex_destroy(&data->eating_lock);
	}
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

void	philo_msg(char *msg, t_philo *philo, int id)
{
	if (philo->data->dead == false)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d %s\n", get_time() - philo->start_time, id, msg);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
}
