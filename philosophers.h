/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:30:10 by tlupu             #+#    #+#             */
/*   Updated: 2024/11/08 16:13:55 by tlupu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define FIRST_FORK "has taken a fork"
# define SECOND_FORK "has taken a fork"
# define EATIN "is eating"
# define SLEEPIN "is sleeping"
# define THINKIN "is thinking"
# define DIED "died"

// t_philo_data
//   ├── time_to_die
//   ├── time_to_eat
//   ├── time_to_think
//   ├── death_flag
//   ├── full_flag
//   ├── philo_number
//   └── philosophers (array of t_philo_thrds)
//         ├── philo_thread
//         ├── philo_id
//         ├── last_time_ate
//         ├── meals_eaten
//         ├── left_fork
//         ├── right_fork
//         └── data (pointer to t_philo_data)

typedef struct s_data_philo	t_philo_data;

typedef struct s_philo_thrds
{
	pthread_t				philo_thread;
	int						philo_id;
	long					last_time_ate;
	int						meals_eaten;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_philo_data			*data;
}							t_philo_thrds;

typedef struct s_data_philo
{
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					start_time;
	bool					death_flag;
	bool					full_flag;
	int						philo_number;
	int						number_of_meals;
	pthread_mutex_t			mesage;
	pthread_mutex_t			time_mtex;
	pthread_mutex_t			table_mtex;
	pthread_mutex_t			meals_mtex;
	pthread_mutex_t			death_mtex;
	pthread_mutex_t			full_mtex;
	pthread_mutex_t			died_mtex;
	t_philo_thrds			*philosophers;
}							t_philo_data;

//--------UTILS------------

int							f_isdigit(int c);
int							is_digit_string(const char *str);
int							ft_atoi(const char *str);

//-------ERROR_HANDLING----
int							check_philosophers(char **argv);

//-------PHILO_STARTING----
t_philo_thrds				*init_philo(int agrc, char **argv);
void						handle_start(t_philo_thrds *philo);

//-------SIMULATION--------
void						start_simulation(t_philo_thrds *philosophers);

//-------ROUTINE-----------
void						*routine(void *arg);

//-------TIME--------------
void						ft_usleep(int time);
long						ft_time(void);
void						update_meal_time(t_philo_thrds *philo);

//-------MESSAGE-----------
void						message(t_philo_thrds *philos, char *msg);

//-------DEATH_FULL_CHECKS-

bool						has_died(t_philo_thrds *philo);
bool						has_eaten_all_meals(t_philo_thrds *philo);
int							check_death(t_philo_thrds *philo);
int							meal_time(t_philo_thrds *philo);

//------FORKS-------------
void						release_forks(t_philo_thrds *philo);
int							check_forks(t_philo_thrds *philo);

#endif