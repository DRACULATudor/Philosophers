/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlupu <tlupu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:10:32 by tlupu             #+#    #+#             */
/*   Updated: 2024/10/21 14:47:53 by tlupu            ###   ########.fr       */
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

//----------------UTILS----------------//

// utils1
int									ft_atoi(const char *str);
int									ft_isdigit(int c);

typedef struct s_data_philosopher	t_data_philosopher;

typedef struct s_philo_thrds
// my struct to hold the necessary data
// for each philosopher regaring functionality
{
	pthread_t						philosophers_thrd;
	int								philo_id;
	long							last_time_ate;
	int								meals_eaten;
	pthread_mutex_t					*fork_left;
	pthread_mutex_t					*fork_right;
	t_data_philosopher				*data;

}									t_philo_thrds;

// struct to hold the data for the philosopher

typedef struct s_data_philosopher
{
	int								philo_number;
	long							time_to_die;
	int								stop_flag;
	long							time_to_eat;
	long							time;
	long							time_to_think;
	int								time_to_sleep;
	int								death_flag;
	int								full_flag;
	int								num_of_times_each_must_eat;
	int								start_time;
	int								*individual_meals_eaten;
	int								all_ate_flag;
	pthread_mutex_t					death;
	pthread_mutex_t					eating;
	pthread_mutex_t					thinkin;
	pthread_mutex_t					sleeping;
	pthread_mutex_t					mssg;
	pthread_mutex_t					time_mtex;
	pthread_mutex_t					meals_eaten_mtex;
	pthread_mutex_t					routine_mtex;
	pthread_mutex_t					death_mtex;
	pthread_mutex_t					death2_mtex;
	pthread_mutex_t					full_mtex;
	t_philo_thrds					*philosophers;

}									t_data_philosopher;

//---------------FUNCTIONS----------------//
int									meal_time(t_philo_thrds *philo);

// ROUTINE.C//
void								*routine(void *arg);
int									is_eating(t_philo_thrds *philo);
int									is_thinking(t_philo_thrds *philo);
int									is_sleeping(t_philo_thrds *philo);
int									handle_one_philo(t_philo_thrds *philo);

// FORKS_EATING_UPDATES//
void								release_forks(t_philo_thrds *philo);
int									check_fork_order(t_philo_thrds *philo);
void								update_meal_time(t_philo_thrds *philo);

// CLOCK.C //
long								ft_time(void);
void								ft_usleep(int time);
int									has_died(t_philo_thrds *philo);
int									check_full(t_philo_thrds *philo);
void								message(t_philo_thrds *philo, char *msg);

// CLEAN.C//

void								clear_philos(t_philo_thrds *philosop);

// ERRORS AND STARTING.C//
void								check_philosophers(char **argv);
t_data_philosopher					*init_data(int argc, char **argv);
int									init_mutexes(t_data_philosopher *data);
t_philo_thrds						*init_philo_array(t_data_philosopher *data);
void								setup_forks(t_philo_thrds *philosophers,
										t_data_philosopher *data);

// CREAT JOIN AND MONITOR.C//

void								cret_phil_thrd(t_philo_thrds *philosophers);
void								monitor(t_philo_thrds *philosophers);
void								join_phil_thrd(t_philo_thrds *philosophers);

// INIT AND DEATH FULL CHECHK //

t_philo_thrds						*init_philosophers(int argc, char **argv);
int									check_death(t_philo_thrds *philo);
int									meal_time(t_philo_thrds *philo);

#endif