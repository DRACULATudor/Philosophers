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

t_data_philosopher	*init_data(int argc, char **argv)
{
	t_data_philosopher	*data;

	data = malloc(1 * sizeof(t_data_philosopher));
	if (!data)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	data->philo_number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->death_flag = 0;
	if (argc == 6)
		data->num_of_times_each_must_eat = ft_atoi(argv[5]);
	else if (argc == 5)
		data->num_of_times_each_must_eat = -1;
	else
	{
		printf("Error: Invalid number of arguments\n");
		free(data);
		return (NULL);
	}
	return (data);
}

int	init_mutexes(t_data_philosopher *data)
{
	if ((pthread_mutex_init(&data->thinkin, NULL) != 0)
		|| (pthread_mutex_init(&data->eating, NULL) != 0)
		|| (pthread_mutex_init(&data->death, NULL) != 0)
		|| (pthread_mutex_init(&data->sleeping, NULL) != 0)
		|| (pthread_mutex_init(&data->mssg, NULL) != 0)
		|| (pthread_mutex_init(&data->time_mtex, NULL) != 0)
		|| (pthread_mutex_init(&data->meals_eaten_mtex, NULL) != 0)
		|| (pthread_mutex_init(&data->full_mtex, NULL) != 0)
		|| (pthread_mutex_init(&data->routine_mtex, NULL) != 0)
		|| (pthread_mutex_init(&data->death_mtex, NULL) != 0)
		|| (pthread_mutex_init(&data->death2_mtex, NULL) != 0))
	{
		printf("Error initialising mutexes\n");
		return (1);
	}
	return (0);
}

t_philo_thrds	*init_philosophers_array(t_data_philosopher *data)
{
	t_philo_thrds	*philosophers;

	philosophers = malloc(data->philo_number * sizeof(t_philo_thrds));
	if (!philosophers)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	data->time = ft_time();
	data->full_flag = 0;
	for (int i = 0; i < data->philo_number; i++)
	{
		philosophers[i].philo_id = i;
		philosophers[i].data = data;
		philosophers[i].last_time_ate = data->time;
		philosophers[i].meals_eaten = 0;
		philosophers[i].fork_left = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philosophers[i].fork_left, NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			exit(1);
		}
	}
	return (philosophers);
}

void	setup_forks(t_philo_thrds *philosophers, t_data_philosopher *data)
{
	for (int i = 0; i < data->philo_number; i++)
	{
		philosophers[i].fork_right = philosophers[(i - 1 + data->philo_number)
			% data->philo_number].fork_left;
	}
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

void	create_threads(t_philo_thrds *philosophers)
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
	while (1)
	{
		if (check_death(philosophers) || meal_time(philosophers))
			break ;
		ft_usleep(100); // Sleep for a short period to avoid busy-waiting
	}
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

void	clear_philos(t_philo_thrds *philosop)
{
	int	i;

	i = 0;
	while (i < philosop->data->philo_number)
	{
		if (philosop[i].fork_left)
		{
			pthread_mutex_destroy(philosop[i].fork_left);
			free(philosop[i].fork_left);
		}
		// if (philosop[i].fork_right)
		// {
		// 	pthread_mutex_destroy(philosop[i].fork_right);
		// }
		i++;
	}
	// Destroy data mutexes
	pthread_mutex_destroy(&philosop->data->thinkin);
	pthread_mutex_destroy(&philosop->data->eating);
	pthread_mutex_destroy(&philosop->data->death);
	pthread_mutex_destroy(&philosop->data->sleeping);
	pthread_mutex_destroy(&philosop->data->mssg);
	pthread_mutex_destroy(&philosop->data->time_mtex);
	pthread_mutex_destroy(&philosop->data->meals_eaten_mtex);
	pthread_mutex_destroy(&philosop->data->full_mtex);
	pthread_mutex_destroy(&philosop->data->routine_mtex);
	pthread_mutex_destroy(&philosop->data->death2_mtex);
	pthread_mutex_destroy(&philosop->data->death_mtex);
	if (philosop->data->philosophers)
	{
		free(philosop->data->philosophers);
	}
	if (philosop->data)
	{
		free(philosop->data);
	}
	if (philosop)
	{
		free(philosop);
	}
}

int	main(int argc, char **argv)
{
	t_philo_thrds	*philosophers;

	// int death;
	// death = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	check_philosophers(argv);
	philosophers = init_philosophers(argc, argv);
	create_threads(philosophers);
	clear_philos(philosophers);
	return (0);
}
// death and monitor function
// death function done
// monitor function needed
