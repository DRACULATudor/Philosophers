/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_join_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:11:53 by tlupu             #+#    #+#             */
/*   Updated: 2024/10/22 18:04:42 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// create thrds
void	cret_phil_thrd(t_philo_thrds *philosophers)
{
	int	i;

	i = 0;
	while (philosophers->data->philo_number > i)
	{
		if (pthread_create(&philosophers[i].philosophers_thrd, NULL, routine,
				(void *)&philosophers[i]) != 0)
		{
			printf("Error creating thread\n");
			exit(1);
		}
		i++;
	}
}

// monitors for death/full numbers of meals
// sleep to avoid busy-waiting(helps for same
// time actions allowing the cpu to work efficently)
void	monitor(t_philo_thrds *philosophers)
{
	while (1)
	{
		if (check_death(philosophers) || meal_time(philosophers))
			break ;
		ft_usleep(100);
	}
}

// join the thrds
void	join_phil_thrd(t_philo_thrds *philosophers)
{
	int	i;

	i = 0;
	while (philosophers->data->philo_number > i)
	{
		if (pthread_join(philosophers[i].philosophers_thrd, NULL) != 0)
		{
			printf("Error joining thread\n");
			exit(1);
		}
		i++;
	}
}
