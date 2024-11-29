#include "philo.h"

unsigned int	ft_message_error(const char *err, unsigned int exit_status)
{
	write(STDERR_FILENO, err, ft_strlen(err));
	return (exit_status & 0xff);
}
