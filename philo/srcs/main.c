/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:48:31 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/16 13:01:57 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_args	*initialize_args(int argc, char **argv)
{
	t_args	*args;

	(void)argc;
	args = (t_args *)malloc(sizeof(t_args));
	args->num_philos = atoi(argv[1]);
	args->time_die = atoi(argv[2]);
	args->time_eat = atoi(argv[3]);
	args->time_sleep = atoi(argv[4]);
	//args->num_eat = atoi(argv[5]);
	return (args);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	args = initialize_args(argc, argv);
	return (0);
}
