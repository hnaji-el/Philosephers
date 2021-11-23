/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 04:10:12 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/23 04:10:15 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_death_status(t_list *lst, char *str)
{
	pthread_mutex_lock(&(lst->args->display));
	printf("%ld %d %s\n",
		timer_ms() - lst->t_start_sim,
		lst->philo_id,
		str
		);
}

void	print_status(t_list *lst, char *str)
{
	pthread_mutex_lock(&(lst->args->display));
	printf("%ld %d %s\n",
		timer_ms() - lst->t_start_sim,
		lst->philo_id,
		str
		);
	pthread_mutex_unlock(&(lst->args->display));
}

void	take_forks(t_list *lst)
{
	pthread_mutex_lock(&(lst->fork));
	print_status(lst, "has taken a fork");
	pthread_mutex_lock(&(lst->next->fork));
	print_status(lst, "has taken a fork");
}

void	eating(t_list *lst)
{
	pthread_mutex_lock(&(lst->eat));
	lst->t_last_meal = timer_ms();
	print_status(lst, "is eating");
	correct_usleep(lst->args->time_eat * 1000);
	lst->count_eat += 1;
	pthread_mutex_unlock(&(lst->eat));
	pthread_mutex_unlock(&(lst->fork));
	pthread_mutex_unlock(&(lst->next->fork));
}

void	*start_routine(void *ptr)
{
	t_list	*lst;

	lst = (t_list *)ptr;
	while (1)
	{
		take_forks(lst);
		eating(lst);
		print_status(lst, "is sleeping");
		correct_usleep(lst->args->time_sleep * 1000);
		print_status(lst, "is thinking");
	}
	return (NULL);
}
