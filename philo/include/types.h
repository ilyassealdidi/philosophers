/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/05/02 12:11:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include "utils.h"

typedef struct s_settings
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				num_of_meals;
}	t_settings;

typedef struct s_tools
{
	pthread_mutex_t	philo_locker;
	pthread_mutex_t	obj_locker;
	pthread_mutex_t	print_locker;
	pthread_mutex_t	extra_locker;
}	t_tools;

typedef struct s_object
{
	t_settings		settings;
	t_list			*philos;
	t_tools			tools;
	long			start_time;
	int				finished;
	bool			ended;
}	t_object;

typedef struct s_philo
{
	int				id;
	int				eating_counter;
	long			last_eating_time;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	t_object		*_parent;
}	t_philo;

#endif