/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:46:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/07 18:51:44 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_digit(argv[i]))
			error("Invalid arguments");
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		error("Invalid arguments");
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		error("Invalid arguments");
	if (argc == 6 && ft_atoi(argv[5]) < 1)
		error("Invalid arguments");
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (write(2, "Error: wrong number of arguments\n", 33), 1);
	if (check_args(argc, argv))
		return (1);
	if (init_args(argc, argv, &data))
		return (free_data(&data), error("init_args"), 1);
	 creat_threads(&data);
	// check_simulation(&data);
	mtx_destroy(&data);
	free_data(&data);
	return (0);
}
