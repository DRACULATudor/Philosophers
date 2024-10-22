/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock_death_full_check.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:12:02 by tlupu             #+#    #+#             */
/*   Updated: 2024/10/22 16:17:47 by tlupu            ###   ########.fr       */
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
	long			current_time;
	static long		start_time = 0;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error getting time\n");
		exit(1);
	}
	current_time = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	if (start_time == 0)
		start_time = current_time;
	return (current_time - start_time);
}

// calc the end time by adding sleep duration to the cur time
// loop const checks while sleeping for 100 sec
// until curr time is greater/equal than end time
void	ft_usleep(int time)
{
	long	start;
	long	end;

	start = ft_time();
	end = start + time;
	if (ft_time() < end)
	{
		while (ft_time() < end)
		{
			usleep(100);
		}
	}
}

// used by the threads of the philos to check the death/num of meals

int	has_died(t_philo_thrds *philo)
{
	int	death_check;

	pthread_mutex_lock(&philo->data->death_mtex);
	death_check = philo->data->death_flag;
	pthread_mutex_unlock(&philo->data->death_mtex);
	return (death_check);
}

int	check_full(t_philo_thrds *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->meals_eaten_mtex);
	result = philo->data->full_flag;
	pthread_mutex_unlock(&philo->data->meals_eaten_mtex);
	return (result);
}

void	message(t_philo_thrds *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->data->mssg);
	timestamp = ft_time();
	if (!has_died(philo))
		printf("%ld %d %s\n", timestamp, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->data->mssg);
}
