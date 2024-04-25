/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:07 by ialdidi           #+#    #+#             */
/*   Updated: 2024/04/25 16:49:53 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include "utils.h"

# define FORMAT_ERROR "Invalid format provided!\nSyntax : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

# define THINK "\033[0;33m%ld\t%d is thinking\033[1;0m 💭\n"
# define EAT "\033[1;32m%ld\t%d is eating\033[1;0m 🍝\n"
# define SLEEP "\033[0;36m%ld\t%d is sleeping\033[1;0m 💤\n"
# define DIE "\033[1;31m%ld\t%d dead\033[1;0m 💀\n"
# define TAKE_FORK "\033[0;0m%ld\t%d is has taken a fork\033[1;0m 🍽️\n"

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
	pthread_mutex_t	end_locker;
	pthread_mutex_t	print_locker;
	pthread_mutex_t	philo_locker;
	pthread_mutex_t	obj_locker;
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

/*		Parsing			*/
int		settings_init(t_settings *settings, char **param);

/*		Initializer		*/
int		philos_init(t_object *obj);

/*		Monitoring		*/
void	monitoring(t_object *obj);

/*		Action			*/
void	*action(void *param);
int		eat(t_philo *philo);
int		bedtime(t_philo *philo);
int		think(t_philo *philo);

/*		Utils			*/
bool	is_ended(t_object *obj);
t_philo	*get_next_philo(t_philo *philo);
void	print_action(t_philo *philo, char *action);

/*		Time			*/
void	sleeper(long time);
long	get_current_time(void);

#endif
