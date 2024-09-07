#include "philosophers.h"

//if numb is even we lock from the right first
int	check_fork_order(t_philo_thrds *philo)
{
	if (has_died(philo))
		return (0);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		message(philo, FIRST_FORK);
		pthread_mutex_lock(philo->fork_left);
		message(philo, SECOND_FORK);
		return (1);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		message(philo, FIRST_FORK);
		pthread_mutex_lock(philo->fork_right);
		message(philo, SECOND_FORK);
		return (1);
	}
	return (0);
}
//than unlock here
void	release_forks(t_philo_thrds *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->fork_right);
		pthread_mutex_unlock(philo->fork_left);
	}
	else
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
	}
}

//update the meal time for each philo who just ate
void	update_meal_time(t_philo_thrds *philo)
{
	pthread_mutex_lock(&philo->data->time_mtex);
	philo->last_time_ate = ft_time();
	pthread_mutex_unlock(&philo->data->time_mtex);
	if (philo->data->num_of_times_each_must_eat != -1)
	{
		pthread_mutex_lock(&philo->data->meals_eaten_mtex);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->data->meals_eaten_mtex);
	}
}