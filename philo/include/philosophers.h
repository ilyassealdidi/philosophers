/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:21:07 by ialdidi           #+#    #+#             */
/*   Updated: 2024/07/14 02:27:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include "types.h"

# define FORMAT_ERROR "Invalid format provided!\nSyntax : ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

# define THINK "\033[0;33m%ld\t%d is thinking\033[1;0m 💭\n"
# define EAT "\033[1;32m%ld\t%d is eating\033[1;0m 🍝\n"
# define SLEEP "\033[0;36m%ld\t%d is sleeping\033[1;0m 💤\n"
# define DIE "\033[1;31m%ld\t%d dead\033[1;0m 💀\n"
# define TAKE_FORK "\033[0;0m%ld\t%d has taken a fork\033[1;0m 🍽️\n"

/*		tbn				*/
long	read_value(pthread_mutex_t *mutex, long *var);
long	write_value(pthread_mutex_t *mutex, long *var, long new_value);


/*		Parsing			*/
int		settings_init(t_settings *settings, char **param);

/*		Initializer		*/
int		philos_init(t_object *obj);

/*		Monitoring		*/
void	monitoring(t_object *obj);

/*		Action			*/
void	*action(void *param);
int		eat(t_list *node);
int		bedtime(t_philo *philo);
int		think(t_philo *philo);

/*		Utils			*/
bool	is_ended(t_object *obj);
t_philo	*get_next_philo(t_philo *philo);
void	print_action(t_philo *philo, char *action);

/*		Time			*/
void	sleeper(t_object *obj, long time);
long	get_current_time(void);


#endif
