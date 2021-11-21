/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:48:31 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/21 15:23:01 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	timer_us(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000000) + cur_time.tv_usec);
}

int	correct_usleep(useconds_t usec)
{
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (timer_us() - start_time < usec);
	return (0);
}

void	print_status(t_list *lst, char *str, long start_time)
{
	pthread_mutex_lock();
	printf("%ld %d %s\n",
			(timer_us() - start_time) / 1000,
			lst->philo_id,
			str
			);
	pthread_mutex_unlock();
}

void	*start_routine(void *ptr)
{
	long	start_time;
	t_list	*lst;

	start_time = timer_us();
	lst = (t_list *)ptr;
	while (1)
	{
		pthread_mutex_lock(&(lst->mutex));
		print_status(lst, "has taken a fork", start_time);
		pthread_mutex_lock(&(lst->next->mutex));
		print_status(lst, "has taken a fork", start_time);
		print_status(lst, "is eating", start_time);
		correct_usleep(lst->args->time_eat * 1000);
		pthread_mutex_unlock(&(lst->mutex));
		pthread_mutex_unlock(&(lst->next->mutex));
		print_status(lst, "is sleeping", start_time);
		correct_usleep(lst->args->time_sleep * 1000);
		print_status(lst, "is thinking", start_time);
	}
	return (NULL);
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
