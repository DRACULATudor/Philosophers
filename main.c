#include "philosophers.h"

//monitor is using the main thread of the program to ewatch over all the philos

void	create_threads(t_philo_thrds *philosophers)
{
	create_philosopher_threads(philosophers);
	monitor(philosophers);
	join_philosopher_threads(philosophers);
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
	clear_philos(philosophers);
	return (0);
}
