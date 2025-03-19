/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:05:52 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 18:11:43 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// timeval is a struct specially used for getting the time
// curr time will get the current time
// return the current time - the start time so we
// will allways acyratly get the time of each function call
long	ft_time(void)
{
	struct timeval	time;
	long			time_long;

	if (gettimeofday(&time, NULL))
	{
		printf("Error getting start time");
		return (1);
	}
	time_long = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_long);
}

// calc the end time by adding sleep duration to the cur time
// loop const checks while sleeping for 100 sec
// until curr time is greater/equal than end time
void	ft_usleep(int time)
{
	long	start;

	start = ft_time();
	while ((ft_time() - start) < time)
		usleep(100);
}

void	update_meal_time(t_philo_thrds *philo)
{
	pthread_mutex_lock(&philo->data->time_mtex);
	philo->last_time_ate = ft_time();
	pthread_mutex_unlock(&philo->data->time_mtex);
	pthread_mutex_lock(&philo->data->meals_mtex);
	if (philo->data->number_of_meals != -1)
		philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->data->meals_mtex);
}
