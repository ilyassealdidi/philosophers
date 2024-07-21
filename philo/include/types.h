/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/21 03:30:05 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>
# include "utils.h"

typedef struct s_settings
{
	unsigned int	num_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_think;
	unsigned int	time_to_sleep;
	int				num_of_meals;
}	t_settings;

typedef struct s_object
{
	t_settings		settings;
	t_list			*philos;
	pthread_mutex_t	obj_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meals_lock;
	long			start_time;
	long			full_philos;
	long			ended;
}	t_object;

typedef struct s_philo
{
	unsigned int	id;
	int				eaten_meals;
	long			last_eating_time;
	pthread_t		thrd;
	pthread_mutex_t	lock;
	pthread_mutex_t	fork;
	t_object		*_parent;
}	t_philo;

#endif