/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_usleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaji-el <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 04:05:48 by hnaji-el          #+#    #+#             */
/*   Updated: 2021/11/23 04:06:25 by hnaji-el         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	correct_usleep(useconds_t usec)
{
	long	start_time;

	start_time = timer_us();
	usleep(usec - 10000);
	while (timer_us() - start_time < usec)
		;
	return (0);
}
