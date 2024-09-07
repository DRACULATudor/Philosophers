#include "philosophers.h"

void	check_philosophers(char **argv)
{
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
	{
		printf("Error: Invalid time or philosophers number (the time must be greater than 60 and the philo number greater than 0)\n");
		exit(1);
	}
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

//Assign i - 1 (the left of the cur philo) + philo numb (ensuring the numb is positive)
//% the philo numb it will wrap arounfd in a circular manner (ex:0 - 1 + 5) % 5 = 4(which will be last for 5 philos)

void	setup_forks(t_philo_thrds *philosophers, t_data_philosopher *data)
{
	for (int i = 0; i < data->philo_number; i++)
	{
		philosophers[i].fork_right = philosophers[(i - 1 + data->philo_number)
			% data->philo_number].fork_left;
	}
}
