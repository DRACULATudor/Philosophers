/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_full_checks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:08:16 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 17:56:39 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	has_died(t_philo_thrds *philo)
{
	bool	death_check;

	pthread_mutex_lock(&philo->data->death_mtex);
	death_check = philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->death_mtex);
	return (death_check);
}

bool	has_eaten_all_meals(t_philo_thrds *philo)
{
	bool	meal_check;

	pthread_mutex_lock(&philo->data->meals_mtex);
	meal_check = philo->data->full_flag;
	pthread_mutex_unlock(&philo->data->meals_mtex);
	return (meal_check);
}

int	meal_time(t_philo_thrds *philo)
{
	int		i;
	bool	all_meals_eaten;

	i = 0;
	all_meals_eaten = true;
	if (philo->data->number_of_meals == -1)
		return (0);
	pthread_mutex_lock(&philo->data->meals_mtex);
	while (i < philo->data->philo_number)
	{
		if (philo[i].meals_eaten < philo->data->number_of_meals)
		{
			all_meals_eaten = false;
			break ;
		}
		i++;
	}
	if (all_meals_eaten == true)
	{
		pthread_mutex_lock(&philo->data->full_mtex);
		philo->data->full_flag = true;
		pthread_mutex_unlock(&philo->data->full_mtex);
	}
	pthread_mutex_unlock(&philo->data->meals_mtex);
	return (all_meals_eaten);
}

int	check_death(t_philo_thrds *philo)
{
	int		i;
	long	current_time;
	long	time_since_last_meal;

	i = 0;
	while (i < philo->data->philo_number)
	{
		pthread_mutex_lock(&philo->data->time_mtex);
		current_time = ft_time();
		time_since_last_meal = current_time - philo[i].last_time_ate;
		pthread_mutex_unlock(&philo->data->time_mtex);
		if (time_since_last_meal > philo->data->time_to_die
			|| (time_since_last_meal >= philo->data->time_to_die
				&& (philo->data->time_to_eat
					+ philo->data->time_to_sleep) >= philo->data->time_to_die))
		{
			message(&philo[i], DIED);
			pthread_mutex_lock(&philo->data->death_mtex);
			philo->data->death_flag = true;
			pthread_mutex_unlock(&philo->data->death_mtex);
			return (1);
		}
		i++;
	}
	return (0);
}
