#include "philosophers.h"

void	create_philosopher_threads(t_philo_thrds *philosophers)
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
}

void 	monitor(t_philo_thrds *philosophers)
{
	while (1)
	{
		if (check_death(philosophers) || meal_time(philosophers))
			break ;
		ft_usleep(100); // Sleep for a short period to avoid busy-waiting
	}
}

void join_philosopher_threads(t_philo_thrds *philosophers)
{
	int i;

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