
#include "../includes/philo.h"

int	correct_usleep(useconds_t usec)
{
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (timer_us() - start_time < usec);
	return (0);
}
