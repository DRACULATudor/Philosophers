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

