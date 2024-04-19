/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:07 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/18 11:07:23 by ialdidi          ###   ########.fr       */
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
	int				num_of_meals;
}	t_settings;

typedef struct s_tools
{
	pthread_mutex_t	printing_mtx;
	pthread_mutex_t	philo_mtx;
	pthread_mutex_t	mtx;
}	t_tools;

typedef struct s_object
{
	t_settings		settings;
	t_list			*philos;
	t_tools			tools;
	bool			is_ended;
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

/*		Utils			*/
void    sleeper(long time);
long	get_current_time(void);
void	set_value(pthread_mutex_t *mtx, long *target, long value);
long	get_value(pthread_mutex_t *mtx, long *target);

/*		Parsing			*/
int		settings_init(t_settings *settings, char **param);

/*		Initializer		*/
int		philos_init(t_object *obj);

/*		Program			*/
void	*routine(void *param);

#endif