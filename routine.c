#include "philosophers.h"

int	handle_one_philo(t_philo_thrds *philo)
{
	while (!has_died(philo))
	{
		is_thinking(philo);
		message(philo, FIRST_FORK);
		is_sleeping(philo);
	}
	return (0);
}

int	is_sleeping(t_philo_thrds *philo)
{
	if (has_died(philo) || check_full(philo))
		return (0);
	message(philo, SLEEPIN);
	ft_usleep(philo->data->time_to_sleep);
	return (1);
}

int	is_eating(t_philo_thrds *philo)
{
	if (has_died(philo))
		return (0);
	if (!check_fork_order(philo))
		return (0);
	update_meal_time(philo);
	ft_usleep(philo->data->time_to_eat);
	message(philo, EATIN);
	release_forks(philo);
	return (1);
}

int	is_thinking(t_philo_thrds *philo)
{
	if (has_died(philo) || check_full(philo))
		return (0);
	message(philo, THINKIN);
	return (1);
}

void	*routine(void *arg)
{
	t_philo_thrds	*philo;

	philo = (t_philo_thrds *)arg;
	if (philo->data->philo_number == 1)
	{
		if (!handle_one_philo(philo))
			return (NULL);
	}
	else
	{
		pthread_mutex_lock(&philo->data->time_mtex);
		philo->last_time_ate = ft_time();
		pthread_mutex_unlock(&philo->data->time_mtex);
		while (1)
		{
			if (!is_eating(philo))
				break ;
			if (!is_sleeping(philo))
				break ;
			if (!is_thinking(philo))
				break ;
		}
	}
	return (NULL);
}