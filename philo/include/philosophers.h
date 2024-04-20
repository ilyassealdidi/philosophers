/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:07 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 19:21:06 by ialdidi          ###   ########.fr       */
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
	pthread_mutex_t	end_locker;
	pthread_mutex_t	print_locker;
	pthread_mutex_t	die_locker;
	pthread_mutex_t	eat_locker;
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

/*		Utils			*/
void	sleeper(long time);
long	get_current_time(void);
void	set_value(pthread_mutex_t *mtx, long *target, long value);
long	get_value(pthread_mutex_t *mtx, long *target);
bool	is_ended(t_object *obj);
t_philo	*get_next_philo(t_philo *philo);
void	print_action(t_philo *philo, char *action);

/*		Parsing			*/
int		settings_init(t_settings *settings, char **param);

/*		Initializer		*/
int		philos_init(t_object *obj);

/*		Program			*/
void	*routine(void *param);

/*		Monitoring		*/
void	monitoring(t_object *obj);

#endif
