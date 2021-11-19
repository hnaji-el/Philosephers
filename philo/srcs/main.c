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

void	*start_routine(void *ptr)
{
	t_node	*data;

	data = (t_node *)ptr;
	printf("%p\n", ptr);
	printf("--------Philosopher number: %d---------\n", data->philo_id);
	printf("%d|%d|%p\n",
			data->nb_philos,
			data->philo_id,
			data->next
		  );
	return (ptr);
}

void	print_list(t_node *tail)
{
	t_node	*head;

	if (tail == NULL)
	{
		printf("the list is empty ...\n");
		return ;
	}
	head = tail->next;
	while (head != tail)
	{
		printf("%d\n", head->philo_id);
		head = head->next;
	}
	printf("%d\n", head->nb_philos);
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

void	insert_at_end(int nb_philos, int philo_id, pthread_mutex_t mutex, t_node **tail)
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
	*tail = node;
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

int	create_data(t_args *args, t_node **data)
{
	int				i;
	pthread_mutex_t	*mutex;

	i = 0;
	mutex = create_mutexes(args);
	while (i < args->nb_philos)
	{
		insert_at_end(args->nb_philos, i + 1, mutex[i], data);
		i++;
	}
	free(mutex);
	return (0);
}

int	create_threads(t_args *args)
{
	int			i;
	t_node		*data;
	pthread_t	*th;

	i = 0;
	create_data(args, &data);
	th = (pthread_t *)malloc(sizeof(pthread_t) * args->nb_philos);
	while (i < args->nb_philos)
	{
		data = data->next;
		pthread_create(&th[i], NULL, start_routine, data);
		sleep(3);
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
