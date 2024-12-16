/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:43:25 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/12/14 21:06:22 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include "err.h"
# include <sys/time.h>
# include <limits.h>
# include <string.h>

# define INVALID_ARG "\nInvalid number of arguments\n\n"

# define USAGE " Usage: ./philo [number of philos] [time to die] \
[time to eat] [time to sleep] [number of times each philo must eat] \
\n\n Last argument is optional\n\n"

# define NOT_NUMBER " Is not a valid number, do no use simbols, \
permited character from 0 to 9\n\n"

# define ZERO_LARGE " Is 0 or too large\n\n"

# define PHILO_AMOUNT " 200 philos or less, Please\n\n"

# define NEGATIVE " Negative number\n\n"

typedef struct s_rules
{
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		n_times_must_eat;
}	t_rules;

typedef struct s_mutex_control
{
	pthread_mutex_t	time_ready;
	pthread_mutex_t	dead;
	pthread_mutex_t	have_eaten;
}	t_mutex_control;

typedef struct s_time
{
	time_t	start_time;
	time_t	current_time;
}	t_time;

typedef struct s_philo_info
{
	t_mutex_control		*control;
	size_t			philo_id;
	t_time			time;
	t_rules			rules;
	int				*philo_have_eaten;
	int				*dead;
	size_t				*time_ready;
	pthread_mutex_t			fork;
	int				fork_took;
	pthread_mutex_t			*n_fork;
	int				*n_fork_took;
}	t_philo_info;

typedef struct s_simulation
{
	t_mutex_control		control;
	size_t			time_ready;
	int				dead;
	int				philo_have_eaten;
	t_rules			rules;
	size_t			nb_of_philos;
	pthread_t		philo_thread[200];
	t_philo_info	info[200];
}	t_simulation;

size_t			ft_strlen(const char *s);
unsigned int	ft_message_error(const char *custom,
					const char *err, unsigned int status);
time_t			ft_stoms(time_t sec);
time_t			ft_ustoms(suseconds_t usec);
time_t			ft_timevaltoms(struct timeval tv);
time_t			ft_current_time(time_t start_time, time_t current_time);
int				ft_atoi(const char *s);
int				ft_check_args(const char **av);
void			*ft_philo_routine(void	*p);
int				ft_init_rules(char **argv, t_rules *rules,
					size_t *nb_of_philos);
int				ft_init_info(t_philo_info *info, size_t nb_of_philos,
					t_simulation *sim);
int				ft_init_philo(pthread_t *info, t_philo_info *p,
					size_t nb_of_philo);
int				ft_init_rules(char **argv, t_rules *rules,
					size_t *nb_of_philos);
int				ft_init_info(t_philo_info *info, size_t nb_of_philos,
					t_simulation *sim);
int				ft_init_philo(pthread_t *philo, t_philo_info *info,
					size_t nb_of_philo);
int				ft_init_sim(t_simulation *sim, char **av);
int				ft_calculate_dead(t_philo_info *info, time_t last_meal, time_t current_time);
int			ft_check_dead(t_philo_info *info, time_t last_meal);
int			verify_dead(t_philo_info *info);
time_t			ft_get_time();
void			ft_set_time(t_time *time);
#endif
