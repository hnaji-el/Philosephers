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

	ret = -1;
	lst = (void *)0;
	args = (void *)0;
	if (!parsing(&args, argc, argv) && !create_lst(&lst, args))
		ret = create_threads(lst);
	system("leaks philo");
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
