/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:29:07 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 16:12:56 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philosophers(char **argv)
{
	if (!is_digit_string(argv[1]) || ft_atoi(argv[1]) > 200)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (1);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60
		|| ft_atoi(argv[4]) < 60)
		return (1);
	return (0);
}
