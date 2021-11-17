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

void	*routine(void *i)
{
	int		*j;

	j = (int *)i;
	printf("I'm in thread: %d\n", *j + 1);
	return (NULL);
}

int	create_join_threads(t_args *args)
{
	pthread_t	*th;
	int			i;

	i = -1;
	th = (pthread_t *)malloc(sizeof(pthread_t) * args->num_philos);
	while (++i < args->num_philos)
	{
		pthread_create(&th[i - 1], NULL, routine, &i);
		usleep(10);
	}
	i = 0;
	while (i < args->num_philos)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args		*args;
	int			ret;

	ret = parsing(&args, argc, argv);
	if (ret == 0)
	{
		ret = create_join_threads(args);
	}
	return (ret);
}
