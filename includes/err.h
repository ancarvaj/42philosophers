#ifndef ERR_H
#define ERR_H

#define ERR_LEN 3

enum err
{
	ARG_LEN_ERR = 0,
	ARG_NO_NUMBER_ERR = 1,
	TYPE_NOT_DEFINED_ERR = 2
};

static const char error_message[ERR_LEN][255] =
{
	{"Please, use the right number of arguments.\nUsage : ./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]\n"},
	{"The argument doesn`t look like numbers\n"},
	{"It's an erro but dont know what type\n"},
};

#endif
