#include "philo.h"

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
	size_t	fork_id;
	bool	locked;
}	t_fork;

typedef struct s_philo
{
	size_t	philo_id;
	bool	dead;
	bool	philo_ate;
	size_t	own_fork;
	size_t	fork_side;
}	t_philo;

typedef struct s_philo_info
{
	size_t number_of_philo_has_eaten;
	t_rules rules;
	/*gobal info philo should know*/
}t_philo_info;

typedef struct s_time
{
	time_t	start_time;
	time_t	current_time;
} t_time;

time_t	ft_stoms(time_t sec)
{
	return (sec * 1000);
}

time_t ft_ustoms(suseconds_t usec)
{
	return (usec / 1000);
}

time_t ft_timevaltoms(struct timeval tv)
{
	return (ft_stoms(tv.tv_sec) + ft_ustoms(tv.tv_usec));
}

time_t ft_get_time(time_t start_time, time_t current_time)
{
	return (current_time - start_time);
}

int	main(int ac, char *av[])
{
	struct timeval tv;
	t_time time;

	if (gettimeofday(&tv, NULL))
		return (ft_message_error(error_message[2], 123));
	time.start_time =  ft_timevaltoms(tv);
	printf("start time : %ld\n", time.start_time);
	while (1)
	{
		usleep(1000);
		gettimeofday(&tv, NULL);
		time.current_time = ft_get_time(time.start_time, ft_timevaltoms(tv));
		printf("curr time : %ld ms\n", time.current_time);
	}
	//if (ac != 5 && ac != 6)
	//	return (ft_message_error(error_message[ARG_LEN_ERR], 257));
	
	//printf("%s\n", av[1]);
	(void)ac;(void)av;
	return (0);
}
