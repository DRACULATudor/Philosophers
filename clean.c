#include "philosophers.h"

//Destroy all threads to a oid data racse

void    destroy_mutexes(t_philo_thrds *philosop)
{
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
}


//clean all the alloced mem
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
		i++;
	}
    destroy_mutexes(philosop);
	if (philosop->data->philosophers)
		free(philosop->data->philosophers);
	if (philosop->data)
		free(philosop->data);
	if (philosop)
		free(philosop);
}