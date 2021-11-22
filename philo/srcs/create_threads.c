
#include "../includes/philo.h"

int	join_threads(pthread_t *th, int nb)
{
	int		i;

	i = -1;
	while (++i < nb)
	{
		if (pthread_join(th[i], NULL) != 0)
			return (-1);
	}
	return (0);
}

int	create_threads(t_list *lst)
{
	pthread_t	*th;
	int			nb;
	int			i;

	i = 0;
	nb = lst->args->nb_philo;
	th = (pthread_t *)malloc(sizeof(pthread_t) * nb);
	if (th == NULL)
		return (put_error(3));
	while (i < nb)
	{
		lst = lst->next;
		pthread_create(&th[i], NULL, start_routine, lst);
		usleep(50);
		i++;
	}
	/*
	 * supervisor
	 */
	while (1)
	{
		lst = lst->next;
		if (timer_ms() - lst->t_last_meal >= lst->args->time_die)
		{
			print_status(lst, "died", lst->start_time);
			lst->args->die = 1;
			break ;
		}
	}
	join_threads(th, nb);
	return (0);
}
