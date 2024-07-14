/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/14 04:17:11 by ialdidi          ###   ########.fr       */
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

typedef struct s_object
{
	t_settings		settings;
	t_list			*philos;
	pthread_mutex_t	obj_lock;
	long			start_time;
	long			finished;
	long			ended;
}	t_object;

typedef struct s_philo
{
	int				id;
	int				eaten_meals;
	long			last_eating_time;
	pthread_t		thrd;
	pthread_mutex_t	lock;
	pthread_mutex_t	fork;
	t_object		*_parent;
}	t_philo;

#endif