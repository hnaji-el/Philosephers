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

long	timer_ms(void)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return ((cur_time.tv_sec * 1000) + cur_time.tv_usec / 1000);
}

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

void	print_status(t_list *lst, char *str)
{
	if (!lst->args->die)
	{
		pthread_mutex_lock(&(lst->args->display));
		printf("%ld %d %s\n",
			timer_ms() - lst->t_start_sim,
			lst->philo_id,
			str
			);
		pthread_mutex_unlock(&(lst->args->display));
	}
}

void	*start_routine(void *ptr)
{
	t_list	*lst;

	lst = (t_list *)ptr;
	if (lst->philo_id % 2 == 0)
		usleep(100);
	while (!lst->args->die)
	{
		pthread_mutex_lock(&(lst->fork));
		print_status(lst, "has taken a fork");
		pthread_mutex_lock(&(lst->next->fork));
		print_status(lst, "has taken a fork");
		lst->t_last_meal = timer_ms();
		print_status(lst, "is eating");
		correct_usleep(lst->args->time_eat * 1000);
		pthread_mutex_unlock(&(lst->fork));
		pthread_mutex_unlock(&(lst->next->fork));
		print_status(lst, "is sleeping");
		correct_usleep(lst->args->time_sleep * 1000);
		print_status(lst, "is thinking");
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
