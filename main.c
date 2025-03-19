/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:31:06 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 15:17:19 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_philo_thrds *philosop)
{
	pthread_mutex_destroy(&philosop->data->mesage);
	pthread_mutex_destroy(&philosop->data->time_mtex);
	pthread_mutex_destroy(&philosop->data->table_mtex);
	pthread_mutex_destroy(&philosop->data->death_mtex);
	pthread_mutex_destroy(&philosop->data->meals_mtex);
	pthread_mutex_destroy(&philosop->data->full_mtex);
}

// clean all the alloced mem
void	destroy_philos(t_philo_thrds *philosop)
{
	int	i;

	i = 0;
	while (i < philosop->data->philo_number)
	{
		if (philosop[i].left_fork)
		{
			pthread_mutex_destroy(philosop[i].left_fork);
			free(philosop[i].left_fork);
		}
		i++;
	}
	destroy_mutexes(philosop);
	if (philosop->data)
		free(philosop->data);
	if (philosop)
		free(philosop);
}

int	main(int argc, char *argv[])
{
	t_philo_thrds	*philosphers;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of philosophers\n");
		return (1);
	}
	if (check_philosophers(argv))
	{
		printf("Error: wrong argument given for philosoph"
			"ers number/time/numbers of meals\n");
		return (1);
	}
	philosphers = init_philo(argc, argv);
	start_simulation(philosphers);
	destroy_philos(philosphers);
	return (0);
}
