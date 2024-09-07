#include "philosophers.h"

int	meal_time(t_philo_thrds *philo)
{
	int	i;
	int	all_meals_eaten;

	i = 0;
	all_meals_eaten = 1;
	if (philo->data->num_of_times_each_must_eat == -1)
		return (0);
	pthread_mutex_lock(&philo->data->meals_eaten_mtex);
	while (i < philo->data->philo_number)
	{
		if (philo[i].meals_eaten < philo->data->num_of_times_each_must_eat)
		{
			all_meals_eaten = 0;
			break ;
		}
		i++;
	}
	if (all_meals_eaten)
	{
		pthread_mutex_lock(&philo->data->full_mtex);
		philo->data->full_flag = 1;
		pthread_mutex_unlock(&philo->data->full_mtex);
	}
	pthread_mutex_unlock(&philo->data->meals_eaten_mtex);
	return (all_meals_eaten);
}


//if curr time - last meal time > than time of death -> death
int	check_death(t_philo_thrds *philo)
{
	long	current_time;
	int		i;

	i = 0;
	pthread_mutex_lock(&philo->data->time_mtex);
	current_time = ft_time();
	while (i < philo->data->philo_number)
	{
		if (current_time - philo[i].last_time_ate > philo->data->time_to_die)
		{
			pthread_mutex_unlock(&philo->data->time_mtex);
			message(&philo[i], DIED);
			pthread_mutex_lock(&philo->data->death_mtex);
			philo->data->death_flag = 1;
			pthread_mutex_unlock(&philo->data->death_mtex);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data->time_mtex);
	return (0);
}

t_philo_thrds	*init_philosophers(int argc, char **argv)
{
	t_data_philosopher	*data;
	t_philo_thrds		*philosophers;

	data = init_data(argc, argv);
	if (!data)
		return (NULL);
	if (init_mutexes(data))
	{
		free(data);
		return (NULL);
	}
	philosophers = init_philosophers_array(data);
	if (!philosophers)
	{
		free(data);
		return (NULL);
	}
	setup_forks(philosophers, data);
	data->philosophers = malloc(data->philo_number * sizeof(t_philo_thrds));
	if (data->philosophers == NULL)
	{
		free(data->philosophers);
		return (NULL);
	}
	return (philosophers);
}
