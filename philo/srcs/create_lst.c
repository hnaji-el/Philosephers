/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 04:06:49 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/23 04:07:53 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_mutexs(pthread_mutex_t **mutex, int nb)
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
	ret = create_mutexs(&mutex, args->nb_philo * 2 + 1);
	if (ret == 0)
		args->display = mutex[0];
	while (ret == 0 && --i >= 0)
		ret = lstadd_back(lst, args, mutex);
	free(mutex);
	if (ret == -1)
		put_error(3);
	return (ret);
}
