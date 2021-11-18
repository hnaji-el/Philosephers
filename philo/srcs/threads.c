
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int		g_i;

void	*start_routine(void *ptr)
{
	int		i;

	i = 0;
	while (i++ < 1000000)
	{
		pthread_mutex_lock(ptr);
		g_i++;
		pthread_mutex_unlock(ptr);
	}
	return (ptr);
}

int	main(void)
{
	pthread_t		t1;
	pthread_t		t2;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&t1, NULL, start_routine, &mutex);
	pthread_create(&t2, NULL, start_routine, &mutex);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("%d\n", g_i);
	return (0);
}
