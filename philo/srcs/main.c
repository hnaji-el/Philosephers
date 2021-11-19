/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:48:31 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/19 02:09:53 by hnaji-el         ###   ########.fr       */
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

	*lst = NULL;
	i = args->nb_philo;
	ret = create_mutexes(&mutex, args->nb_philo);
	while (ret == 0 && --i >= 0)
		ret = lstadd_front(lst, args, i + 1, mutex[i]);
	free(mutex);
	return (ret);
}

void	*start_routine(void *ptr)
{
	t_list	*lst;

	lst = (t_list *)ptr;
	while (1)
	{
		pthread_mutex_lock(&(lst->mutex));
		printf("time %d has taken a fork\n", lst->philo_id);
		pthread_mutex_lock(&(lst->next->mutex));
		printf("time %d has taken a fork\n", lst->philo_id);
		printf("time %d is eating\n", lst->philo_id);
		usleep(lst->args->time_eat * 1000);
		pthread_mutex_unlock(&(lst->mutex));
		pthread_mutex_unlock(&(lst->next->mutex));
		printf("time %d is sleeping\n", lst->philo_id);
		usleep(lst->args->time_sleep * 1000);
		printf("time %d is thinking\n", lst->philo_id);
	}
	return (ptr);
}

int	create_threads(t_args *args)
{
	pthread_t	*th;
	t_list		*lst;
	int			i;

	i = 0;
	if (create_lst(&lst, args) == -1)
	{
		lstclear(&lst);
		return (put_error(3));
	}
	th = (pthread_t *)malloc(sizeof(pthread_t) * args->nb_philo);
	if (th == NULL)
	{
		lstclear(&lst);
		return (put_error(3));
	}
	while (i < args->nb_philo)
	{
		lst = lst->next;
		pthread_create(&th[i], NULL, start_routine, lst);
		usleep(50);
		i++;
	}
	join_threads(th, args->nb_philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		*args;
	int			ret;

	ret = parsing(&args, argc, argv);
	if (ret == 0)
	{
		ret = create_threads(args);
	}
	return (ret);
}
