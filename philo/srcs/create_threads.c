/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 04:08:01 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/23 04:08:08 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	launch_threads_pair(t_list *lst, pthread_t *th, long t_start_sim)
{
	int		i;

	i = 1;
	lst = lst->next->next;
	while (i < lst->args->nb_philo)
	{
		lst->t_start_sim = t_start_sim;
		lst->t_last_meal = t_start_sim;
		if (pthread_create(&th[i], NULL, start_routine, lst) != 0)
		{
			free(th);
			return (-1);
		}
		lst = lst->next->next;
		i += 2;
	}
	return (0);
}

int	launch_threads_unpair(t_list *lst, pthread_t *th, long t_start_sim)
{
	int		i;

	i = 0;
	lst = lst->next;
	while (i < lst->args->nb_philo)
	{
		lst->t_start_sim = t_start_sim;
		lst->t_last_meal = t_start_sim;
		if (pthread_create(&th[i], NULL, start_routine, lst) != 0)
		{
			free(th);
			return (-1);
		}
		lst = lst->next->next;
		i += 2;
	}
	return (0);
}

int	create_threads(t_list *lst)
{
	pthread_t	*th;
	long		t_start_sim;

	th = (pthread_t *)malloc(sizeof(pthread_t) * lst->args->nb_philo);
	if (th == NULL)
		return (put_error(3));
	t_start_sim = timer_ms();
	if (launch_threads_unpair(lst, th, t_start_sim) == -1)
		return (put_error(5));
	usleep(100);
	if (launch_threads_pair(lst, th, t_start_sim) == -1)
		return (put_error(5));
	controller_of_threads(lst);
	free(th);
	return (0);
}
