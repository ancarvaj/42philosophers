#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "err.h"
#include <sys/time.h>
#include <limits.h>
typedef struct s_rules
{
	size_t nb_of_philos;
	size_t time_to_die;
	size_t time_to_eat;
	size_t time_to_sleep;
	size_t n_times_must_eat;
}	t_rules;

typedef struct s_fork
{
	size_t		fork_id;
	bool		locked;
	pthread_mutex_t	fork[250];
}	t_fork;

typedef struct s_philo
{
	size_t	philo_id;
	bool	dead;
	bool	philo_ate;
	size_t	own_fork;
	size_t	side_fork;
}	t_philo;

typedef struct s_time
{
	time_t	start_time;
	time_t	current_time;
}	t_time;

typedef struct s_philo_info
{
	size_t	number_of_philo_has_eaten;
	t_rules rules;
	t_time	time;
	t_philo	philo[255];
	t_fork	fork[255];
}	t_table_info;

size_t		ft_strlen(const char *s);
unsigned int	ft_message_error(const char *err, unsigned int exit_status);
time_t		ft_stoms(time_t sec);
time_t		ft_ustoms(suseconds_t usec);
time_t		ft_timevaltoms(struct timeval tv);
time_t		ft_get_time(time_t start_time, time_t current_time);
void		*ft_time_routine(void *global_time);
int		ft_atoi(const char *s);
int	ft_check_args(char **av);

#endif
