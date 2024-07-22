/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:10:03 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/23 00:20:16 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <pthread.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct s_thread
{
	pthread_t		thread;
	bool			is_initialized;
}	t_thread;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	bool			is_initialized;
}	t_mutex;

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
	t_mutex			obj_lock;
	t_mutex			print_lock;
	t_mutex			meals_lock;
	long			start_time;
	long			ended;
}	t_object;

typedef struct s_philo
{
	unsigned int	id;
	long			eaten_meals;
	long			last_eating_time;
	t_thread		thread;
	t_mutex			lock;
	t_mutex			fork;
	t_object		*_parent;
}	t_philo;

#endif