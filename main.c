/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:10:08 by tlupu             #+#    #+#             */
/*   Updated: 2024/10/21 14:34:43 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//monitor is using the main thread of the program to ewatch over all the philos

void	create_threads(t_philo_thrds *philosophers)
{
	cret_phil_thrd(philosophers);
	monitor(philosophers);
	join_phil_thrd(philosophers);
}

int	main(int argc, char **argv)
{
	t_philo_thrds	*philosophers;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	check_philosophers(argv);
	philosophers = init_philosophers(argc, argv);
	create_threads(philosophers);
	clear_philos(philosophers);
	return (0);
}
