/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 04:05:24 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/23 04:05:28 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		pthread_mutex_lock(&(lst->eat));
		if ((timer_ms() - lst->t_last_meal >= lst->args->time_die))
		{
			print_death_status(lst, "died");
			break ;
		}
		pthread_mutex_lock(&(lst->eat));
		if (lst->args->nb_eat != -1 && check_nb_eat(lst))
			break ;
	}
}
