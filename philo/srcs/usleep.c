
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

long	timer_us(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000000) + cur_time.tv_usec);
}

int	ft_usleep(useconds_t usec)
{
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (1)
	{
		if ((timer_us() - start_time) >= usec)
			break ;
		usleep(1000);
	}
	return (0);
}

int	main(void)
{
	long	start_time;

	start_time = timer_us();
	ft_usleep(1000000);
	printf("taken time by useconds:%ld\n", (timer_us() - start_time));
	return (0);
}
