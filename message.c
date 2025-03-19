/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:27:19 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 17:03:28 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(t_philo_thrds *philos, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philos->data->mesage);
	timestamp = ft_time() - philos->data->start_time;
	if (!has_died(philos))
		printf("%ld %d %s\n", timestamp, philos->philo_id, msg);
	pthread_mutex_unlock(&philos->data->mesage);
}
