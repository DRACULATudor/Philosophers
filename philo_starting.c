/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_starting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:37:26 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 16:14:13 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_start(t_philo_thrds *philo)
{
	message(philo, THINKIN);
	ft_usleep(1);
}

// remember to add to init mutexes all newly used mutexes
// Each philosopher's left fork is a unique mutex.
// Each philosopher's right fork is the next philosopher's
// left fork. This creates a circular arrangement of forks.
int	init_philo_fields(t_philo_thrds *philo, t_philo_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_number)
	{
		philo[i].philo_id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_time_ate = ft_time();
		philo[i].left_fork = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo[i].left_fork, NULL) != 0)
			return (1);
		philo[i].data = data;
		i++;
	}
	i = 0;
	while (i < data->philo_number)
	{
		philo[i].right_fork = philo[(i + 1) % data->philo_number].left_fork;
		data->philosophers = philo;
		i++;
	}
	return (0);
}

int	init_mutexes(t_philo_data *data)
{
	if (pthread_mutex_init(&data->mesage, NULL) != 0
		|| pthread_mutex_init(&data->time_mtex, NULL) != 0
		|| pthread_mutex_init(&data->death_mtex, NULL) != 0
		|| pthread_mutex_init(&data->table_mtex, NULL) != 0
		|| pthread_mutex_init(&data->meals_mtex, NULL) != 0
		|| pthread_mutex_init(&data->died_mtex, NULL) != 0
		|| pthread_mutex_init(&data->full_mtex, NULL) != 0)
	{
		printf("Error initalising mutex\n");
		return (1);
	}
	return (0);
}

t_philo_data	*init_philo_data(int argc, char **argv)
{
	t_philo_data	*data;

	data = malloc(sizeof(t_philo_data));
	if (!data)
	{
		printf("Error allocating memory\n");
		return (NULL);
	}
	data->philo_number = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->death_flag = false;
	data->full_flag = false;
	data->start_time = ft_time();
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	else
		data->number_of_meals = -1;
	return (data);
}

t_philo_thrds	*init_philo(int agrc, char **argv)
{
	t_philo_data	*data;
	t_philo_thrds	*philosophers;

	data = init_philo_data(agrc, argv);
	if (!data)
		return (NULL);
	philosophers = malloc(sizeof(t_philo_thrds) * data->philo_number);
	if (!philosophers)
	{
		free(data);
		return (NULL);
	}
	if (init_philo_fields(philosophers, data))
	{
		free(data);
		free(philosophers);
		return (NULL);
	}
	if (init_mutexes(data))
		return (NULL);
	return (philosophers);
}
