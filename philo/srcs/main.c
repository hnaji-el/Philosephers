/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:48:31 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/17 13:16:34 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*start_routine(void *ptr)
{
	printf("Hello world from thread\n");
	return (ptr);
}

t_node	*get_new_node(int nb_philos, int philo_id, pthread_mutex_t mutex)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->nb_philos = nb_philos;
	node->philo_id = philo_id;
	node->mutex = mutex;
	node->next = (void *)0;
	return (node);
}

void	insert_at_beg(int nb_philos, int philo_id, pthread_mutex_t mutex, t_node **tail)
{
	t_node	*node;

	node = get_new_node(nb_philos, philo_id, mutex);
	if (*tail == NULL)
	{
		node->next = node;
		*tail = node;
		return ;
	}
	node->next = (*tail)->next;
	(*tail)->next = node;
}

pthread_mutex_t	*create_mutexes(t_args *args)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->nb_philos);
	while (i < args->nb_philos)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

int	join_threads(pthread_t *th, t_args *args)
{
	int		i;

	i = 0;
	while (i < args->nb_philos)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	return (0);
}

int	create_threads(t_args *args)
{
	pthread_t	*th;
	int			i;

	i = 0;
	:
	th = (pthread_t *)malloc(sizeof(pthread_t) * args->nb_philos);
	while (i < args->nb_philos)
	{
		pthread_create(&th[i], NULL, start_routine, NULL);
		i++;
	}
	join_threads(th, args);
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
