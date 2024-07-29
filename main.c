#include "philosophers.h"

// if philo number odd, time to die = time to eat*2 + time to sleep + 10
// odd -> time to sleep = time to eat / 2
// odd numbers take from left first
// even numbers take from right first

// if philo number even, time to die = time to eat + time to sleep + 10

// int philo_death(t_philo_thrds *philo)
// {
//     if (monitor(philo) == -1)
//     {
//         pthread_mutex_lock(&philo->data->death);
//         message(philo, DIED);
//         pthread_mutex_unlock(&philo->data->death);
//     }
// 	return(0);
// }


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

void	message(t_philo_thrds *philo, char *msg)
{
	long	timestamp;

	// pthread_mutex_lock(&philo->data->mssg);
	timestamp = ft_time();
	printf("%ld %d %s\n", timestamp, philo->philo_id, msg); // Use philo_id
	// pthread_mutex_unlock(&philo->data->mssg);					//+ 1 to match philosopher numbering
}

void	ft_usleep(int time)
{
	long	start;
	long	end;

	start = ft_time();
	end = start + time;
	while (ft_time() < end)
		usleep(100); // Adjust dynamically if necessary
}

void	check_fork_order(t_philo_thrds *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_right);
		message(philo, FIRST_FORK);
		pthread_mutex_lock(philo->fork_left);
		message(philo, SECOND_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->fork_left);
		message(philo, FIRST_FORK);
		pthread_mutex_lock(philo->fork_right);
		message(philo, SECOND_FORK);
	}
}

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

void	is_eating(t_philo_thrds *philo)
{
	check_fork_order(philo);
	message(philo, EATIN);
	// pthread_mutex_lock(&philo->data->eating);
	ft_usleep(philo->data->time_to_eat);
	// pthread_mutex_unlock(&philo->data->eating);
	release_forks(philo);
}

void	is_thinking(t_philo_thrds *philo)
{
	// int copy = philo->data->time_to_sleep / 2;
	message(philo, THINKIN);
	// pthread_mutex_lock(&philo->data->thinkin);
	// ft_usleep(copy);
	// pthread_mutex_unlock(&philo->data->thinkin);
}

void	is_sleeping(t_philo_thrds *philo)
{
	message(philo, SLEEPIN);
	// pthread_mutex_lock(&philo->data->sleeping);
	ft_usleep(philo->data->time_to_sleep);
	// pthread_mutex_unlock(&philo->data->sleeping);
}

void	*routine(void *arg)
{
	t_philo_thrds	*philo;

	philo = (t_philo_thrds *)arg;
	while (1)
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (NULL);
}
void	check_philosophers(char **argv)
{
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
	{
		printf("Error: Invalid time or philosophers number (the time must be greater than 60 and the philo number greater than 0)\n");
		exit(1);
	}
}

t_philo_thrds	*init_philosophers(int argc, char **argv)
{
	t_philo_thrds		*philosophers;
	t_data_philosopher	*data;
	int					i;

	data = malloc(sizeof(t_data_philosopher));
	if (!data)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	data->philo_number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = ft_time();
	data->time_to_think = data->time_to_sleep / 2;
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
	philosophers = malloc(sizeof(t_philo_thrds) * atoi(argv[1]));
	if (!philosophers)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	if ((pthread_mutex_init(&data->thinkin, NULL) != 0)
		|| (pthread_mutex_init(&data->eating, NULL) != 0)
		|| (pthread_mutex_init(&data->death, NULL) != 0)
		|| (pthread_mutex_init(&data->sleeping, NULL) != 0)
		|| (pthread_mutex_init(&data->mssg, NULL) != 0)
		|| (pthread_mutex_init(&data->time_mtex, NULL) != 0))
	{
		printf("Error initialising mutexes\n");
		exit(1);
	}
	i = 0;
	while (data->philo_number > i)
	{
		philosophers[i].philo_id = i;
		philosophers[i].last_time_eaten = 0;
		philosophers[i].data = data;
		philosophers[i].fork_left = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philosophers[i].fork_left, NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data->philo_number)
	{
		philosophers[i].fork_right = philosophers[(i - 1 + data->philo_number)
			% data->philo_number].fork_left;
		i++;
	}
	return (philosophers);
}

void	create_threads(t_philo_thrds *philosophers)
{
	int	i;

	i = 0;
	philosophers->data->time = ft_time();
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
	i = 0;
	while (philosophers->data->philo_number > i)
	{
		if (pthread_join(philosophers[i].philosophers_thrd, NULL) != 0)
		{
			printf("Error joining thread\n");
			exit(1);
		}
		// printf("Thread by philo %d joined\n", philosophers[i].philo_id);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo_thrds	*philosophers;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		exit(1);
	}
	check_philosophers(argv);
	philosophers = init_philosophers(argc, argv);
	create_threads(philosophers);
	return (0);
}
// death and monitor function
// death function done
// monitor function needed