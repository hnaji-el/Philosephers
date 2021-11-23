/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:16:41 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/23 04:09:44 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	put_error(int errnum)
{
	if (errnum == 1)
		write(2, "Error\nWrong number of arguments\n", 32);
	if (errnum == 2)
		write(2, "Error\nInvalid argument\n", 23);
	if (errnum == 3)
		write(2, "Error\nCannot allocate memory\n", 29);
	if (errnum == 4)
		write(2, "Error\nThe pthread_join() function failed\n", 41);
	if (errnum == 5)
		write(2, "Error\nThe pthread_create() function failed\n", 43);
	return (-1);
}

void	initialize_args(t_args *args, int number, int argc)
{
	if (argc == 2)
		args->nb_philo = number;
	else if (argc == 3)
		args->time_die = number;
	else if (argc == 4)
		args->time_eat = number;
	else if (argc == 5)
		args->time_sleep = number;
	else
		args->nb_eat = number;
}

bool	elements_isvalid(char *str, int *i)
{
	*i = 0;
	if ((*str == '+' || *str == '-') && str[1] != '\0')
		*i += 1;
	while (str[*i] != '\0')
	{
		if (!ft_isdigit(str[*i]))
			return (false);
		*i += 1;
	}
	return (true);
}

bool	argument_isvalid(char *str, int *num)
{
	int		index;
	long	data;

	if (!elements_isvalid(str, &index) || index > 11)
		return (false);
	data = ft_atoi_l(str);
	if (data < 0 || data > INT_MAX)
		return (false);
	*num = data;
	return (true);
}

int	parsing(t_args **args, int argc, char **argv)
{
	int		number;

	if (argc > 6 || argc < 5)
		return (put_error(1));
	*args = (t_args *)malloc(sizeof(t_args));
	if (*args == NULL)
		return (put_error(3));
	(*args)->nb_eat = -1;
	(*args)->die = 0;
	while (argc-- > 1)
	{
		if (!argument_isvalid(argv[argc], &number))
			return (put_error(2));
		initialize_args(*args, number, argc + 1);
	}
	return (0);
}
