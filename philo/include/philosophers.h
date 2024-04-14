/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:07 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/14 16:06:25 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include "utils.h"

# define FORMAT_ERROR "Invalid format provided!\nSyntax : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_settings
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int 			num_of_meals;
}	t_settings;

typedef struct s_object
{
	t_settings		settings;
	t_list			*philos;
	int				zombie;
	unsigned long	start_time;
}	t_object;

typedef struct s_philosopher
{
	int				id;
	int				eaten_meals;
	long			last_meal_time;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	t_object		*_parent;
}	t_philosopher;


void	*routine(void *param);
int		philos_init(t_object *obj);
int		settings_init(t_settings *settings, char **param);

#endif