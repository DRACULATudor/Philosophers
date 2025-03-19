/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:22:53 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 16:46:31 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_forks(t_philo_thrds *philo)
{
	if (has_died(philo))
		return (1);
	if (philo->data->philo_number == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		message(philo, FIRST_FORK);
		return (0);
	}
	else if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		message(philo, FIRST_FORK);
		pthread_mutex_lock(philo->right_fork);
		message(philo, SECOND_FORK);
		return (0);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		message(philo, FIRST_FORK);
		pthread_mutex_lock(philo->left_fork);
		message(philo, SECOND_FORK);
		return (0);
	}
	return (1);
}

void	release_forks(t_philo_thrds *philo)
{
	if (philo->data->philo_number == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
	}
	else if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
