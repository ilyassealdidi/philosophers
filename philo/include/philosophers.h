/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:07 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/20 12:59:37 by ialdidi          ###   ########.fr       */
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
	pthread_mutex_t	die_locker;
	pthread_mutex_t	eat_locker;
}	t_tools;

typedef struct s_object
{
	t_settings		settings;
	t_list			*philos;
	t_tools			tools;
	size_t			start_time;
	int				finished;
	bool			ended;
}	t_object;

typedef struct s_philosopher
{
	int				id;
	int				eating_counter;
	size_t			last_eating_time;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	t_object		*_parent;
}	t_philosopher;

/*		Utils			*/
void    sleeper(long time);
size_t	get_current_time(void);
void	set_value(pthread_mutex_t *mtx, long *target, long value);
long	get_value(pthread_mutex_t *mtx, long *target);
bool	is_ended(t_object *obj);
void	end_action(t_object *obj);
bool	is_dead(t_philosopher *philo);
t_philosopher	*get_next_philo(t_philosopher *philo);
void	print_action(t_philosopher *philo, char *action);

/*		Parsing			*/
int		settings_init(t_settings *settings, char **param);

/*		Initializer		*/
int		philos_init(t_object *obj);

/*		Program			*/
void	*routine(void *param);

/*		Monitoring		*/
void	monitoring(t_object *obj);

#endif
