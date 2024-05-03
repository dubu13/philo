/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:33:21 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/03 18:45:07 by dhasan           ###   ########.fr       */
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

void	mtx_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	free_data(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philo)
		free(data->philo);
}

void	philo_msg(char *msg, t_philo *philo, int id)
{
	if (philo->dead == false)
		printf("%u %d %s ", get_time(), id, msg);
}