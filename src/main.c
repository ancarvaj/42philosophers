#include "philo.h"

int	ft_init_time(t_time *time, int *philo_has_eaten, size_t *ready, int *dead)
{
	time->dead = dead;
	time->ready = ready;
	time->philo_has_eaten = philo_has_eaten;
	return (0);
}

int	ft_init_sim(t_simulation *sim, char **av)
{
	memset(sim->fork, 0, sizeof(sim->fork));
	memset(sim->philo_thread, 0, sizeof(sim->philo_thread));
	memset(sim->info, 0, sizeof(sim->info));
	if (ft_init_rules(av, &sim->rules, &sim->nb_of_philos))
		return (1);
	sim->philo_has_eaten = sim->nb_of_philos;
	sim->ready = sim->nb_of_philos;
	sim->dead = 0;
	if (ft_init_time(&sim->time, &sim->philo_has_eaten, &sim->ready, &sim->dead))
		return (1);
	if (pthread_create(&sim->time_thread, NULL, ft_time_routine, &sim->time))
		return (1);
	if (ft_init_fork(sim->fork, sim->nb_of_philos))
		return (1);
	if (ft_init_info(sim->info, sim->nb_of_philos, sim))
		return (1);
	if (ft_init_philo(sim->philo_thread, sim->info, sim->nb_of_philos))
		return (1);
	pthread_join(sim->time_thread, NULL);
	return (0);
}

int	main(int ac, char *av[])
{
	t_simulation	sim;
	
	if (ac != 5 && ac != 6)
		return (1);
	if (ft_check_args(av + 1))
		return (1);
	if (ft_init_sim(&sim, av))
		return (1);
	return (0);
}
