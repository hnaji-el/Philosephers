/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:47:12 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/19 02:09:56 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define INT_MAX 2147483647

typedef struct s_args
{
	int		nb_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		nb_eat;
}				t_args;

typedef	struct s_list
{
	int				philo_id;
	pthread_mutex_t	mutex;
	t_args			*args;
	struct s_list	*next;
}				t_list;

/*			parsing.c			*/
int		parsing(t_args **args, int argc, char **argv);
bool	argument_isvalid(char *str, int *num);
bool	elements_isvalid(char *str, int *i);
void	initialize_args(t_args *args, int number, int argc);
int		put_error(int errnum);

/*			philo_utils.c		*/
long	ft_atoi_l(const char *str);
int		ft_isdigit(int c);

/*			circular_lst.c		*/
int		lstadd_front(t_list **lst, t_args *args, int ph_id, pthread_mutex_t mutex);
int		lstadd_back(t_list **lst, t_args *args, int ph_id, pthread_mutex_t mutex);
void	lstclear_front(t_list **lst);
void	lstclear(t_list **lst);

#endif
