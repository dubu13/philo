/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:46:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/04/28 13:42:04 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(int argc, char **argv, t_philo *philo)
{
	philo->number_of_philo = ft_atoi(argv[1]);
	philo->time_to_diet = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			return (write(2, "Error: arguments must be digits\n", 33));
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1] > 200))
		return (write(2, "Error: number of philo\n", 24));
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (write(2, "Error: time to die, eat or sleep\n", 33));
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		return (write(2, "Error: number of times to eat\n", 30));
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 33));
	check_args(argc, argv);
	init_args(argc, argv, philo);
}
//creat threads as many of philos and have to join threads
//need to make a loop that a philo'll eat, sleep, or think until he is dead->need flag to stop the loop
//also need to print msg "x thinking/sleeping/eating"
//for sleeping from the input we need make him sleep by using usleep
//for eating : creat mutex for left and right fork, and lock them while eating