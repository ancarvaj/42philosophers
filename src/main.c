#include "philo.h"
/*
int	ft_init_philo();

int	ft_init_fork();

int	ft_init_rules();
*/

void *ft_time_stamp_routine(void *p)
{
	t_time *t = p;

	while (1)
	{
		usleep(1000);
		printf("%ld\n", t->current_time);
	}
}
int	main(int ac, char *av[])
{
	t_time		time;
	pthread_t	time_stamp;
	pthread_t	time_thread;
	//pthread_t	dead_checker_thread;

	if (ac != 1 && ac != 2)
		return (1);
	if (ft_check_args(av + 1))
		return (1);
	pthread_create(&time_thread, NULL, ft_time_routine, &time);
	pthread_create(&time_stamp, NULL, ft_time_stamp_routine, &time);
	pthread_join(time_stamp, NULL);
	pthread_join(time_thread, NULL);
	return (0);
}
