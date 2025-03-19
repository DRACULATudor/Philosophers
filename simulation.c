/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:00:04 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 17:00:59 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_threads(t_philo_thrds *philosphers)
{
	int	i;

	i = 0;
	while (i < philosphers->data->philo_number)
	{
		if (pthread_create(&philosphers[i].philo_thread, NULL, routine,
				(void *)&philosphers[i]) != 0)
		{
			printf("Error creating threads\n");
			return ;
		}
		i++;
	}
}

void	monitor(t_philo_thrds *philosophers)
{
	while (1)
	{
		if (check_death(philosophers) || meal_time(philosophers))
			break ;
	}
}

void	join_phil_thrd(t_philo_thrds *philosophers)
{
	int	i;

	i = 0;
	while (philosophers->data->philo_number > i)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
		{
			printf("Error joining thread\n");
			exit(1);
		}
		i++;
	}
}

void	start_simulation(t_philo_thrds *philosophers)
{
	create_threads(philosophers);
	monitor(philosophers);
	join_phil_thrd(philosophers);
}
