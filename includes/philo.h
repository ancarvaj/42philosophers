#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "err.h"
#include <sys/time.h>

size_t	ft_strlen(const char *s);
unsigned int	ft_message_error(const char *err, unsigned int exit_status);

#endif
