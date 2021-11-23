/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 09:47:12 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/21 19:14:05 by hnaji-el         ###   ########.fr       */
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
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				die;
	pthread_mutex_t	display;
}				t_args;

typedef	struct s_list
{
	int				philo_id;
	long			t_start_sim;
	long			t_last_meal;
	int				count_eat;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat;
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
int		lstadd_back(t_list **lst, t_args *args, pthread_mutex_t *mutex);
void	lstclear_front(t_list **lst);

/*		   create_lst.c	    	*/
int		create_lst(t_list **lst, t_args *args);
int		create_mutexs(pthread_mutex_t **mutex, int nb);

/*	     create_threads.c	  	*/
int		create_threads(t_list *lst);
int		join_threads(pthread_t *th, int nb);

/*	     correct_usleep.c	  	*/
int		correct_usleep(useconds_t usec);

/*	     		main.c		  	*/
int		free_memory(t_list *lst, t_args *args, int ret);

/*			start_routine.c		*/
void	*start_routine(void *ptr);
void	print_status(t_list *lst, char *str);

/*				timer.c			*/
long	timer_ms(void);
long	timer_us(void);

/*			controller.c		*/
void	controller_of_threads(t_list *lst);

#endif
