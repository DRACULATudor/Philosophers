/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:02:29 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 16:12:08 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// remember to check for how assigni the right fork so nothing ruins
int	is_thinking(t_philo_thrds *philo)
{
	if (has_died(philo) == true || has_eaten_all_meals(philo) == true)
		return (1);
	message(philo, THINKIN);
	return (0);
}

int	is_sleeping(t_philo_thrds *philo)
{
	if (has_died(philo) == true || has_eaten_all_meals(philo) == true)
		return (1);
	message(philo, SLEEPIN);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	is_eating(t_philo_thrds *philo)
{
	if (has_died(philo) == true)
		return (1);
	if (check_forks(philo))
		return (1);
	update_meal_time(philo);
	message(philo, EATIN);
	ft_usleep(philo->data->time_to_eat);
	release_forks(philo);
	return (0);
}

void	handle_one_philo(t_philo_thrds *philo)
{
	if (check_forks(philo))
		return ;
	release_forks(philo);
	if (!has_died(philo))
		return ;
}

void	*routine(void *arg)
{
	t_philo_thrds	*philos;

	philos = (t_philo_thrds *)arg;
	pthread_mutex_lock(&philos->data->time_mtex);
	philos->last_time_ate = ft_time();
	pthread_mutex_unlock(&philos->data->time_mtex);
	if (philos->philo_id % 2 != 0 && philos->data->philo_number != 1)
		handle_start(philos);
	if (philos->data->philo_number == 1)
	{
		handle_one_philo(philos);
	}
	else
	{
		while (1)
		{
			if (is_eating(philos))
				break ;
			if (is_sleeping(philos))
				break ;
			if (is_thinking(philos))
				break ;
		}
	}
	return (NULL);
}
