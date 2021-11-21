
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

long	timer_us(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000000) + cur_time.tv_usec);
}

int	_usleep_(useconds_t usec)
{
	int		i;
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (timer_us() - start_time < usec);
	return (0);
}

int	ft_usleep(useconds_t usec)
{
	long	start_time;

	start_time = timer_us();
	if (usleep(usec - 10000) == -1)
		return (-1);
	while ((timer_us() - start_time) <= usec)
	{
		if (usleep(1000) == -1)
			return (-1);
	}
	return (0);
}

int	main(void)
{
	long	start_time;
	int		i;

	i = 0;
	start_time = timer_us();
	_usleep_(60000);
	printf("time taken by microseconds: %ld\n", timer_us() - start_time);
	return (0);
}
