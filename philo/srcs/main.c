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

int	put_error(int errnum)
{
	if (errnum == 1)
		write(2, "Error\nNumber of arguments should be only 4 or 5 args\n", 53);
	if (errnum == 2)
		write(2, "Error\nCannot allocate memory\n", 29);
	return (-1);
}

void	initialize_args(t_args *args, int number, int argc)
{
	if (argc == 1)
		args->num_philos = number;
	else if (argc == 2)
		args->time_die = number;
	else if (argc == 3)
		args->time_eat = number;
	else if (argc == 4)
		args->time_sleep = number;
	else
		args->num_eat = number;
}

bool	all_elements_isvalid(char *str, int *i)
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

	if (!all_elements_isvalid(str, &index) || index > 11)
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
		return (put_error(2));
	*args = (t_args *)malloc(sizeof(t_args));
	(*args)->num_eat = -1;
	while (argc-- > 1)
	{
		if (!argument_isvalid(argv[argc], &number))
			return (put_error(1));
		initialize_args(*args, number, argc);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	*args;
	int		ret;

	ret = parsing(&args, argc, argv);
	return (ret);
}
