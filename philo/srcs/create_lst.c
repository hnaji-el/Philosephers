
#include "../includes/philo.h"

int	create_mutexes(pthread_mutex_t	**mutex, int nb)
{
	int		i;

	i = 0;
	*mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb);
	if (*mutex == NULL)
		return (-1);
	while (i < nb)
	{
		if (pthread_mutex_init(*mutex + i, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	create_lst(t_list **lst, t_args *args)
{
	pthread_mutex_t	*mutex;
	int				i;
	int				ret;

	i = args->nb_philo;
	ret = create_mutexes(&mutex, args->nb_philo);
	while (ret == 0 && --i >= 0)
		ret = lstadd_front(lst, args, i + 1, mutex[i]);
	free(mutex);
	if (ret == -1)
		put_error(3);
	return (ret);
}
