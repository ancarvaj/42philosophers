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
#include <string.h>

typedef struct s_rules
{
	size_t time_to_die;
	size_t time_to_eat;
	size_t time_to_sleep;
	size_t n_times_must_eat;
}	t_rules;

typedef struct s_time
{
	time_t	start_time;
	time_t	current_time;
	size_t	*ready;
	size_t	*philo_has_eaten;
}	t_time;

typedef struct s_philo_info
{	
	size_t		philo_id;
	bool		philo_ate;
	size_t		own_fork;
	size_t		side_fork;
	time_t		*current_time;
	t_rules		rules;
	size_t		*philo_has_eaten;
	bool		*dead;
	size_t		*ready;
	pthread_mutex_t	*fork;
}	t_philo_info;

typedef struct s_simulation
{
	bool		dead;
	t_rules		rules;
	size_t		nb_of_philos;
	size_t		philo_has_eaten;
	size_t		ready;
	t_time		time;
	pthread_t	time_thread;
	pthread_mutex_t	fork[250];
	pthread_t	philo_thread[250];
	t_philo_info	info[250];
}	t_simulation;

size_t		ft_strlen(const char *s);
unsigned int	ft_message_error(const char *err, unsigned int exit_status);
time_t		ft_stoms(time_t sec);
time_t		ft_ustoms(suseconds_t usec);
time_t		ft_timevaltoms(struct timeval tv);
time_t		ft_get_time(time_t start_time, time_t current_time);
void		*ft_time_routine(void *global_time);
int		ft_atoi(const char *s);
int		ft_check_args(char **av);
void		*ft_philo_routine(void	*p);
int		ft_init_rules(char **argv, t_rules *rules, size_t *nb_of_philos);
int		ft_init_fork(pthread_mutex_t *fork, size_t nb_of_philos);
int		ft_init_info(t_philo_info *info, size_t nb_of_philos, t_simulation *sim);
int		ft_init_philo(pthread_t *info, t_philo_info *p, size_t nb_of_philo);

#endif
