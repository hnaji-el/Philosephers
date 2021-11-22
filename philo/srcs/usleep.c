
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

long	timer_ms(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000) + cur_time.tv_usec / 1000);
}

long	timer_us(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000000) + cur_time.tv_usec);
}

int	ms_usleep(useconds_t usec)
{
	int		i;
	long	start_time;

	start_time = timer_ms() * 1000;
	usleep(usec - 10000);
	while ((timer_ms() * 1000) - start_time < usec);
	return (0);
}

int	us_usleep(useconds_t usec)
{
	int		i;
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (timer_us() - start_time < usec);
	return (0);
}

int	main(void)
{
	long	start_time;
	int		i;

	i = 0;
	start_time = timer_us();
	us_usleep(60000);
	printf("time taken by microseconds: %ld\n", (timer_us() - start_time));
	return (0);
}
