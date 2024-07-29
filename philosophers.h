#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define FIRST_FORK "has taken a fork"
#define SECOND_FORK "has taken a fork"
#define EATIN "is eating"
#define SLEEPIN "is sleeping"
#define THINKIN "is thinking"
#define DIED "died"




//----------------UTILS----------------//

//utils1
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

typedef struct s_data_philosopher t_data_philosopher;

typedef struct s_philo_thrds //my struct to hold the necessary data for each philosopher regaring functionality
{
    pthread_t   philosophers_thrd;
    int        philo_id;
    int       last_time_eaten;
    pthread_mutex_t        *fork_left;
    pthread_mutex_t        *fork_right;
    t_data_philosopher *data;

}  t_philo_thrds;


//struct to hold the data for the philosopher

typedef struct s_data_philosopher
{
    int philo_number;
    int time_to_die;
    int time_to_eat;
    int time;
    int time_to_think;
    int time_to_sleep;
    int num_of_times_each_must_eat;
    int start_time;
    pthread_mutex_t death;
    pthread_mutex_t eating;
    pthread_mutex_t thinkin;
    pthread_mutex_t sleeping;
    pthread_mutex_t mssg;
    pthread_mutex_t time_mtex;
    t_philo_thrds *philosophers;

}   t_data_philosopher;


#endif 