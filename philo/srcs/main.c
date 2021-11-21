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

long	timer_us(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000000) + cur_time.tv_usec);
}

int	usleep_(useconds_t usec)
{
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (1)
	{
		if ((timer_us() - start_time) >= usec)
			break ;
		usleep(1000);
	}
	return (0);
}

void	usleep_(useconds_t usec)
{
	struct timeval	start;
	struct timeval	end;
	long			us;

	gettimeofday(&start, NULL);
	usleep(usec - 10000);
	while (1)
	{
		gettimeofday(&end, NULL);
		us = (end.tv_sec - start.tv_sec) * 1000000;
		if ((us + end.tv_usec - start.tv_usec) >= usec)
			break ; 
		usleep(1000);
	}
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
		ft_usleep(lst->args->time_eat * 1000);
		pthread_mutex_unlock(&(lst->mutex));
		pthread_mutex_unlock(&(lst->next->mutex));
		printf("time %d is sleeping\n", lst->philo_id);
		ft_usleep(lst->args->time_sleep * 1000);
		printf("time %d is thinking\n", lst->philo_id);
	}
	return (ptr);
}

int	free_memory(t_list *lst, t_args *args, int ret)
{
	if (args != NULL)
		free(args);
	while (lst != NULL)
		lstclear_front(&lst);
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_list		*lst;
	t_args		*args;
	int			ret;
	int			exit_status;

	ret = -1;
	lst = (void *)0;
	args = (void *)0;
	if (!parsing(&args, argc, argv) && !create_lst(&lst, args))
		ret = create_threads(lst);
	exit_status = free_memory(lst, args, ret);
	return (exit_status);
}
