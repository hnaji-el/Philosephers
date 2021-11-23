
#include "../includes/philo.h"

bool	check_nb_eat(t_list *lst)
{
	int		i;

	i = 0;
	while (i++ < lst->args->nb_philo)
	{
		if (lst->count_eat < lst->args->nb_eat)
			return (false);
		lst = lst->next;
	}
	return (true);
}

void	controller_of_threads(t_list *lst)
{
	while (1)
	{
		lst = lst->next;
		if ((timer_ms() - lst->t_last_meal >= lst->args->time_die)
			|| (lst->args->nb_eat != -1 && check_nb_eat(lst)))
		{
		//	pthread_mutex_lock(&(lst->eat));
			lst->args->die = 1;
			print_status(lst, "died");
			break ;
		//	pthread_mutex_unlock(&(lst->eat));
		}
	}
}
